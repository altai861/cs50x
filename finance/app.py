import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)
#api key= pk_d1ebe6b57b2d40939a9e6d3a2f5dbae3

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

current_time = datetime.now()

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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
    if request.method == "GET":
        cash = db.execute("SELECT cash from users where id = ?", session["user_id"])
        username = db.execute("SELECT username from users where id = ?", session["user_id"])
        portfolio = db.execute("SELECT * from ?", username[0]["username"])
        portfolio_asset = 0
        for i in portfolio:
            portfolio_asset = portfolio_asset + i["shares"] * lookup(i["stocks"])["price"]

        the_total_asset = usd(cash[0]["cash"] + portfolio_asset)
        return render_template("index.html", cash=usd(cash[0]["cash"]), username=username, portfolio=portfolio, total=the_total_asset)



    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("you have to type in symbol and shares' number", 400)
        the_symbol = lookup(request.form.get("symbol"))
        number_of_shares = request.form.get("shares")
        if not the_symbol:
            return apology("provide a valid stock symbol", 400)
        if int(number_of_shares) <= 0 or number_of_shares is float or number_of_shares is not int:
            return apology("provide a valid number of shares you want to buy", 400)
        the_ready_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        #return render_template("one.html", one=the_ready_cash)
        if int(the_symbol["price"]) * int(number_of_shares) > the_ready_cash[0]["cash"]:
            return apology("You cannot afford this amount of shares", 400)
        final_cost = the_symbol["price"] * int(number_of_shares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", the_ready_cash[0]["cash"] - int(final_cost), session["user_id"])
        db.execute("INSERT INTO transactions (id, stock_symbol, number_shares, action, time) VALUES(?,?,?,?,?)", session["user_id"], request.form.get("symbol"), number_of_shares, "BUY", current_time)
        username = db.execute("SELECT username from users where id = ?", session["user_id"])
        stocks_of_that_person = db.execute("SELECT stocks from ?", username[0]["username"])
        counter = 0
        for stock in stocks_of_that_person:
            if the_symbol["symbol"] == stock["stocks"]:
                counter += 1

        if counter > 0:
            already_in_shares = db.execute("SELECT shares from ? where stocks = ?", username[0]["username"], the_symbol["symbol"])
            db.execute("UPDATE ? SET shares = ? WHERE stocks = ?", username[0]["username"], already_in_shares[0]["shares"] + int(number_of_shares), the_symbol["symbol"])
        else:
            db.execute("INSERT INTO ? (stocks, shares) VALUES(?, ?)",username[0]["username"], the_symbol["symbol"], number_of_shares)
        return render_template("successful_purchase.html")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * from transactions where id = ?", session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Must provide a stock quote", 400)
        stock = lookup(request.form.get("symbol"))
        stock_name = stock["name"]
        stock_price = usd(stock["price"])
        if stock is None:
            return apology("Must provide a valid stock quote", 400)
        return render_template("quoted.html", name=stock_name, price=stock_price)


    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()
    if request.method == "POST":
        the_usernames = db.execute("SELECT username from users")
        counter = 0
        for username in the_usernames:
            if request.form.get("username") == username["username"]:
                counter += 1

        if not request.form.get("username"):
            return apology("Must provide a username", 400)
        elif not request.form.get("password"):
            return apology("Must provide password", 400)
        elif counter > 0:
            return apology("Change your username because there is already an account that has the same username as you typed in", 400)
        elif not request.form.get("confirmation"):
            return apology("Must confirm the password", 400)
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Password and confirmation must match")

        username = request.form.get("username")
        hashed_password = generate_password_hash(request.form.get("password"))

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hashed_password)
        db.execute("CREATE TABLE ? (stocks TEXT NOT NULL, shares NUMERIC NOT NULL) ", username)
        return render_template("login.html")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    username = db.execute("SELECT username from users where id = ?", session["user_id"])
    portfolio = db.execute("SELECT * from ?", username[0]["username"])
    if request.method == "GET":
        return render_template("sell.html", stocks = portfolio)
    else:
        the_stock_for_selling = request.form.get("symbol")
        the_shares = request.form.get("shares")
        the_shares_of_that_person = db.execute("SELECT shares from ? where stocks = ?", username[0]["username"], the_stock_for_selling)
        cash = db.execute("SELECT cash from users where id = ?", session["user_id"])
        if int(the_shares) > int(the_shares_of_that_person[0]["shares"]):
            return apology("You don't have that much shares of that stock", 403)
        else:
            db.execute("UPDATE ? SET shares = ? WHERE stocks = ?", username[0]["username"], int(the_shares_of_that_person[0]["shares"]) - int(the_shares), the_stock_for_selling)
            db.execute("UPDATE users SET cash = ? WHERE username = ?", cash[0]["cash"] + lookup(the_stock_for_selling)["price"], username[0]["username"])
            db.execute("INSERT INTO transactions (id, stock_symbol, number_shares, action, time) VALUES(?,?,?,?,?)", session["user_id"], request.form.get("symbol"), the_shares, "SELL", current_time)
            return redirect("/")



