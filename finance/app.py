import os
import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session.get("user_id")
    stocks = db.execute("SELECT * FROM stocks WHERE user_id=?", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]['cash']
    net_worth_stock = sum(stock['total_cost'] for stock in stocks)
    total_net_worth = cash + net_worth_stock

    return render_template("index.html", stocks=stocks, total_net_worth=total_net_worth, cash=cash)


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    if request.method == "POST":
        current_password = request.form.get("current_password")
        new_password = request.form.get("new_password")
        new_password_confirmation = request.form.get("new_password_confirmation")

        if not current_password:
            return apology("must provide current password",400)
        elif not new_password:
            return apology("must provide new_password",400)
        elif not new_password_confirmation:
            return apology("must provide password_confirmation",400)
        if new_password != new_password_confirmation:
            return apology("new password and confirmation must match", 400)

        user_id = session.get("user_id")
        user = db.execute("SELECT * from users WHERE id=?", user_id)[0]
        if not check_password_hash(user["hash"], current_password):
            return apology("old password is incorrect", 400)

        new_password_hash = generate_password_hash(new_password)
        db.execute("UPDATE users SET hash=? WHERE id=?", new_password_hash, user_id)
        flash("Password changed successfully!")
        return redirect("/")
    else:
        return render_template("change_password.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol", 400)

        stock = lookup(symbol)
        if not stock:
            return apology("there is no stock with that name", 400)

        if not shares:
            return apology("must provide number of shares", 400)

        try:
            shares = int(shares)
        except ValueError:
            return apology("number of shares must be a number", 400)

        if shares <= 0:
            return apology("number of shares should be positive", 400)

        price = stock['price']
        user_id = session.get("user_id")
        total_cost = price * shares
        current_money = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]['cash']

        if current_money < total_cost:
            return apology("not enough money to buy the stock", 400)

        now = datetime.datetime.now()
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, date, shares, price, total_cost, action) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   user_id, symbol, now, shares, price, total_cost, 'buy')

        is_stock = db.execute("SELECT COUNT(*) FROM stocks WHERE symbol=? AND user_id=?", symbol, user_id)
        count = is_stock[0]['COUNT(*)']

        if count > 0:
            db.execute("UPDATE stocks SET shares = shares + ?, price = ?, total_cost = total_cost + ? WHERE symbol = ? AND user_id = ?",
                       shares, price, total_cost, symbol, user_id)
        else:
            db.execute("INSERT INTO stocks (user_id, symbol, shares, price, total_cost) VALUES (?, ?, ?, ?, ?)",
                       user_id, symbol, shares, price, total_cost)

        flash(f"Bought! Total Cost: {usd(total_cost)}")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session.get("user_id")
    transactions = db.execute("SELECT * FROM transactions WHERE user_id=?", user_id)
    for transaction in transactions:
        transaction['total_cost'] = usd(transaction['total_cost'])
        transaction['price'] = usd(transaction['price'])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    session.clear()

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 403)
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        session["user_id"] = rows[0]["id"]
        return redirect("/")
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    session.clear()
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        stock = lookup(symbol)
        if not stock:
            return apology("there is no stock with that name", 400)
        price = stock['price']
        return render_template("quoted.html", symbol=symbol, price=usd(price))
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get('username')
        password = request.form.get('password')
        confirmation = request.form.get('confirmation')

        if not username:
            return apology('must provide username', 400)
        elif not password:
            return apology('must provide password', 400)
        elif not confirmation:
            return apology('must provide password confirmation', 400)
        elif password != confirmation:
            return apology('two passwords should be equal!', 400)

        existing_user = db.execute("SELECT * FROM users WHERE username= ?", username)
        if existing_user:
            return apology('username already exists, please use another username', 400)

        hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

        user = db.execute("SELECT * FROM users WHERE username= ?", username)
        user_id = user[0]['id']
        session['user_id'] = user_id

        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol", 400)
        stock = lookup(symbol)
        if not stock:
            return apology("there is no stock with that name", 400)
        if not shares:
            return apology("must provide number of shares", 400)
        try:
            shares = int(shares)
        except ValueError:
            return apology("number of shares must be a number", 400)
        if shares <= 0:
            return apology("number of shares should be positive", 400)

        user_id = session.get("user_id")
        user_stock_row = db.execute("SELECT shares, price FROM stocks WHERE symbol = ? AND user_id = ?", symbol, user_id)
        if not user_stock_row:
            return apology("stock symbol not found", 400)
        user_shares = user_stock_row[0]['shares']
        stock_price = user_stock_row[0]['price']
        if user_shares < shares:
            return apology("not enough shares to sell", 400)
        price = float(stock['price'])
        now = datetime.datetime.now()
        total_cost = price * shares
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_cost, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, date, shares, price, total_cost, action) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   user_id, symbol, now, shares, price, total_cost, 'sell')
        if user_shares == shares:
            db.execute("DELETE FROM stocks WHERE symbol = ? AND user_id = ?", symbol, user_id)
        else:
            new_total_cost = (user_shares - shares) * stock_price
            db.execute("UPDATE stocks SET shares = shares - ?, total_cost = ? WHERE symbol = ? AND user_id = ?",
                       shares, new_total_cost, symbol, user_id)

        flash(f"Sold! Total Revenue: {usd(total_cost)}")
        return redirect("/")
    else:
        stocks = db.execute("SELECT symbol FROM stocks WHERE user_id = ?", session.get("user_id"))
        return render_template("sell.html", stocks=[stock['symbol'] for stock in stocks])
