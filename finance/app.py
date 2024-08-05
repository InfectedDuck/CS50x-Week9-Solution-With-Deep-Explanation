# Import necessary libraries and modules

import os  # Provides a way of using operating system-dependent functionality
import datetime  # Provides classes for manipulating dates and times
from cs50 import SQL  # CS50 library for interacting with SQLite databases
from flask import Flask, flash, redirect, render_template, request, session  # Importing Flask components for web app functionality
from flask_session import Session  # Flask-Session for handling sessions with filesystem
from werkzeug.security import check_password_hash, generate_password_hash  # Werkzeug functions for password hashing

# Import custom helper functions defined in helpers.py
from helpers import apology, login_required, lookup, usd


# Configure the Flask application
app = Flask(__name__)  # Create a new Flask web application instance

# Register a custom filter with Jinja2, the templating engine used by Flask
app.jinja_env.filters["usd"] = usd  # Add a custom filter for formatting currency in templates

# Configure session management to use filesystem storage instead of cookies
app.config["SESSION_PERMANENT"] = False  # Sessions will be temporary and expire when the browser is closed
app.config["SESSION_TYPE"] = "filesystem"  # Store session data on the server's filesystem
Session(app)  # Initialize the session management system with the Flask app configuration

# Set up the CS50 Library to interact with an SQLite database
db = SQL("sqlite:///finance.db")  # Connect to the SQLite database named 'finance.db' using the CS50 library


@app.after_request
def after_request(response):
    """This function is executed after each request to ensure responses are not cached."""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"  # Prevent caching of responses
    response.headers["Expires"] = 0  # Set expiration date to 0 (past) to ensure freshness
    response.headers["Pragma"] = "no-cache"  # Ensure that HTTP/1.0 caches also do not cache the response
    return response  # Return the modified response object


@app.route("/")
@login_required
def index():
    """Render the portfolio page showing user's stocks and cash balance."""
    user_id = session.get("user_id")  # Retrieve the logged-in user's ID from the session
    # Query the database to get all stocks owned by the user
    stocks = db.execute("SELECT * FROM stocks WHERE user_id=?", user_id)
    # Query the database to get the user's cash balance
    cash = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]['cash']
    # Calculate the total value of the stocks the user owns
    net_worth_stock = sum(stock['total_cost'] for stock in stocks)
    # Calculate the total net worth by adding the cash balance to the stock value
    total_net_worth = cash + net_worth_stock

    # Render the portfolio page template with stock and financial data
    return render_template("index.html", stocks=stocks, total_net_worth=total_net_worth, cash=cash)


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Handle requests for changing the user's password."""
    if request.method == "POST":
        # Retrieve the form data for the current and new passwords
        current_password = request.form.get("current_password")
        new_password = request.form.get("new_password")
        new_password_confirmation = request.form.get("new_password_confirmation")

        # Validate that all required fields are filled in
        if not current_password:
            return apology("must provide current password", 400)  # Error if no current password provided
        elif not new_password:
            return apology("must provide new password", 400)  # Error if no new password provided
        elif not new_password_confirmation:
            return apology("must provide password confirmation", 400)  # Error if no confirmation provided
        if new_password != new_password_confirmation:
            return apology("new password and confirmation must match", 400)  # Error if new passwords do not match

        # Verify the current password and update it if correct
        user_id = session.get("user_id")
        user = db.execute("SELECT * from users WHERE id=?", user_id)[0]
        if not check_password_hash(user["hash"], current_password):
            return apology("old password is incorrect", 400)  # Error if current password is incorrect

        # Hash the new password and update it in the database
        new_password_hash = generate_password_hash(new_password)
        db.execute("UPDATE users SET hash=? WHERE id=?", new_password_hash, user_id)
        flash("Password changed successfully!")  # Notify the user that the password was changed successfully
        return redirect("/")  # Redirect to the home page
    else:
        # Render the password change form
        return render_template("change_password.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Handle buying shares of stock."""
    if request.method == "POST":
        # Retrieve form data for stock purchase
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validate the input data
        if not symbol:
            return apology("must provide symbol", 400)  # Error if no stock symbol provided

        # Look up the stock information using the provided symbol
        stock = lookup(symbol)
        if not stock:
            return apology("there is no stock with that name", 400)  # Error if stock is not found

        if not shares:
            return apology("must provide number of shares", 400)  # Error if no number of shares provided

        try:
            shares = int(shares)  # Convert shares to an integer
        except ValueError:
            return apology("number of shares must be a number", 400)  # Error if shares are not a number

        if shares <= 0:
            return apology("number of shares should be positive", 400)  # Error if shares are not positive

        # Calculate the total cost of the purchase and check if the user has enough funds
        price = stock['price']
        user_id = session.get("user_id")
        total_cost = price * shares
        current_money = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]['cash']

        if current_money < total_cost:
            return apology("not enough money to buy the stock", 400)  # Error if user does not have enough money

        # Update the user's cash balance and record the transaction in the database
        now = datetime.datetime.now()
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, date, shares, price, total_cost, action) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   user_id, symbol, now, shares, price, total_cost, 'buy')

        # Update or insert stock information for the user in the database
        is_stock = db.execute("SELECT COUNT(*) FROM stocks WHERE symbol=? AND user_id=?", symbol, user_id)
        count = is_stock[0]['COUNT(*)']

        if count > 0:
            db.execute("UPDATE stocks SET shares = shares + ?, price = ?, total_cost = total_cost + ? WHERE symbol = ? AND user_id = ?",
                       shares, price, total_cost, symbol, user_id)
        else:
            db.execute("INSERT INTO stocks (user_id, symbol, shares, price, total_cost) VALUES (?, ?, ?, ?, ?)",
                       user_id, symbol, shares, price, total_cost)

        flash(f"Bought! Total Cost: {usd(total_cost)}")  # Notify the user of the successful purchase
        return redirect("/")  # Redirect to the home page
    else:
        # Render the buy stock form
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show the user's transaction history."""
    user_id = session.get("user_id")
    # Retrieve all transactions for the user from the database
    transactions = db.execute("SELECT * FROM transactions WHERE user_id=?", user_id)
    # Format transaction amounts as currency for display
    for transaction in transactions:
        transaction['total_cost'] = usd(transaction['total_cost'])
        transaction['price'] = usd(transaction['price'])
    # Render the history page with the formatted transaction data
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Handle user login."""
    session.clear()  # Clear any existing session data to start a new login session

    if request.method == "POST":
        # Retrieve login form data
        if not request.form.get("username"):
            return apology("must provide username", 403)  # Error if no username provided
        elif not request.form.get("password"):
            return apology("must provide password", 403)  # Error if no password provided

        # Query the database for a user with the provided username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)  # Error if username/password is incorrect

        # Set the user's ID in the session and redirect to the home page
        session["user_id"] = rows[0]["id"]
        return redirect("/")
    else:
        # Render the login form
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Handle user logout."""
    session.clear()  # Clear the user's session data to log them out
    return redirect("/")  # Redirect to the home page
