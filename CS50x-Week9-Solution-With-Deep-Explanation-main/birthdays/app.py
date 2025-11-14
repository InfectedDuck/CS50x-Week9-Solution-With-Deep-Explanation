import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.after_request
def after_request(response):
    """
    Ensure responses aren't cached. This is crucial for dynamic web applications
    where the content of the pages might change based on user interactions.
    """
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"  # Directs browsers not to cache the response
    response.headers["Expires"] = 0  # Sets expiration date of the response to a past date, so it isn't cached
    response.headers["Pragma"] = "no-cache"  # Ensures older HTTP/1.0 caches also do not cache the response
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    """
    Handles both GET and POST requests to the root URL ("/").
    For GET requests, renders the index page with birthday entries from the database.
    For POST requests, processes form data to add a new birthday entry to the database.
    """
    if request.method == "POST":
        # Process the form submission for adding a new birthday entry
        name = request.form.get('name')  # Retrieve the name from the form
        if not name:
            return redirect("/")  # Redirect to the index page if no name is provided
        
        month = request.form.get('month')  # Retrieve the month from the form
        if not month:
            return redirect("/")  # Redirect to the index page if no month is provided
        try:
            month = int(month)  # Convert month to an integer
        except ValueError:
            return redirect("/")  # Redirect to the index page if conversion fails
        
        day = request.form.get('day')  # Retrieve the day from the form
        if not day:
            return redirect("/")  # Redirect to the index page if no day is provided
        try:
            day = int(day)  # Convert day to an integer
        except ValueError:
            return redirect("/")  # Redirect to the index page if conversion fails
        
        # Insert the new birthday entry into the database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/")  # Redirect to the index page after adding the entry

    else:
        # Handle GET requests to display the list of birthdays
        birthdays = db.execute("SELECT name, month, day FROM birthdays")  # Query the database for all birthday entries
        # Render the index.html template with the list of birthdays
        return render_template("index.html", birthdays=birthdays)
