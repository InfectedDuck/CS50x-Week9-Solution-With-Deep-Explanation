import csv  # For reading and parsing CSV data
import datetime  # For working with dates and times
import pytz  # For timezone calculations
import requests  # For making HTTP requests
import urllib  # For URL encoding
import uuid  # For generating unique session identifiers

from flask import redirect, render_template, request, session  # Flask functions for routing, rendering, and session management
from functools import wraps  # For function decorators

def apology(message, code=400):
    """
    Render a message as an apology to the user.
    This function is used to display error messages in a consistent format.
    
    Parameters:
        message (str): The error message to display.
        code (int): The HTTP status code to return (default is 400 for Bad Request).
        
    Returns:
        A tuple containing the rendered apology template and the status code.
    """

    def escape(s):
        """
        Escape special characters in the message to prevent issues with HTML and URLs.
        
        Parameters:
            s (str): The string to escape.
            
        Returns:
            str: The escaped string.
            
        Notes:
            Replaces special characters with their URL-encoded equivalents.
        """
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    # Render the apology template with the provided message and status code
    return render_template("apology.html", top=code, bottom=escape(message)), code

def login_required(f):
    """
    Decorator to require login for a route.
    This function wraps around a view function to check if the user is logged in.
    
    Parameters:
        f (function): The view function to decorate.
        
    Returns:
        function: The wrapped view function.
        
    Notes:
        Redirects to the login page if the user is not logged in.
    """

    @wraps(f)
    def decorated_function(*args, **kwargs):
        # Check if user_id is in the session; if not, redirect to login
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)

    return decorated_function

def lookup(symbol):
    """
    Look up the latest stock price for a given symbol using Yahoo Finance API.
    
    Parameters:
        symbol (str): The stock symbol to look up (e.g., "AAPL").
        
    Returns:
        dict: A dictionary containing the stock price and symbol, or None if an error occurs.
        
    Notes:
        Queries historical stock data for the past week and retrieves the latest adjusted closing price.
    """
    
    # Convert symbol to uppercase
    symbol = symbol.upper()
    
    # Define the time range for the query: the past week
    end = datetime.datetime.now(pytz.timezone("US/Eastern"))
    start = end - datetime.timedelta(days=7)
    
    # Prepare the URL for the Yahoo Finance API request
    url = (
        f"https://query1.finance.yahoo.com/v7/finance/download/{urllib.parse.quote_plus(symbol)}"
        f"?period1={int(start.timestamp())}"
        f"&period2={int(end.timestamp())}"
        f"&interval=1d&events=history&includeAdjustedClose=true"
    )
    
    # Query the API
    try:
        response = requests.get(
            url,
            cookies={"session": str(uuid.uuid4())},  # Generate a unique session cookie
            headers={"Accept": "*/*", "User-Agent": request.headers.get("User-Agent")},  # Mimic a browser request
        )
        response.raise_for_status()  # Raise an exception for HTTP error responses

        # Parse the CSV data from the response
        quotes = list(csv.DictReader(response.content.decode("utf-8").splitlines()))
        # Extract and round the adjusted closing price from the latest record
        price = round(float(quotes[-1]["Adj Close"]), 2)
        return {"price": price, "symbol": symbol}
    except (KeyError, IndexError, requests.RequestException, ValueError):
        # Handle potential errors, such as missing data or failed requests
        return None

def usd(value):
    """
    Format a value as USD currency.
    
    Parameters:
        value (float): The numeric value to format.
        
    Returns:
        str: The formatted currency string.
        
    Notes:
        Formats the value with a dollar sign, comma as thousands separator, and two decimal places.
    """
    return f"${value:,.2f}"
