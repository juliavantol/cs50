import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# export API_KEY=pk_5e5a69f8021746deb3cc4d55c3c1ca89
# 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

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        action = request.form.get("action")
        price = request.form.get("price")

        # Buy
        if action == "+":
            print("yes")
        # Sell
        else:
            print("no")


        return redirect("/")

    else:

        inventory = db.execute("SELECT * FROM inventory WHERE user_id = ?;", session["user_id"])
        try:
            # Check to see if the user already has shares, if they do; update their inventory to the latest price
            for item in inventory:
                symbol = item["symbol"]
                shares = item["shares"]
                data = lookup(symbol)
                current_price = data['price']
                current_total = current_price * shares
                db.execute("UPDATE inventory SET price = ?, total = ? WHERE symbol = ?;",
                           current_price, current_total, symbol)
            inventory = db.execute("SELECT * FROM inventory WHERE user_id = ?;",
                                   session["user_id"])
        except:
            pass

        try:
            # Get user's cash balance
            data = db.execute("SELECT cash FROM users WHERE id = ?",
                              session["user_id"])
            cash = data[0]["cash"]
            total = db.execute("SELECT sum(total) FROM inventory WHERE user_id = ?;",
                               session["user_id"])
            total = total[0]["sum(total)"]
            return render_template("index.html", inventory=inventory, cash=cash, total=(cash + total))
        except:
            return render_template("index.html", inventory=inventory, cash=10000, total=10000)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = (request.form.get("symbol")).upper()
        shares = request.form.get("shares")
        user = session["user_id"]

        if shares.isdigit() is False:
            return apology("Provide valid number", 400)

        data = lookup(symbol)
        shares = int(shares)

        if not symbol or not shares or not data or shares < 1:
            return apology("Invalid input", 400)

        price = data["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?",
                          session["user_id"])
        budget = cash[0]["cash"]

        if price > budget:
            return apology("You can't afford this share", 400)

        # Check to see if there's already a history table, otherwise create it
        try:
            check = db.execute("SELECT * FROM history;")
        except:
            db.execute("CREATE TABLE history(user_id INTEGER, action TEXT NOT NULL, symbol TEXT NOT NULL, shares INTEGER NOT NULL,price INTEGER NOT NULL, date TEXT NOT NULL,FOREIGN KEY(user_id) REFERENCES users(id));")

        # Check to see if there's already an inventory table, otherwise create it
        try:
            check = db.execute("SELECT * FROM inventory;")
        except:
            db.execute("CREATE TABLE inventory(user_id INTEGER, symbol TEXT NOT NULL, company TEXT NOT NULL, shares INTEGER NOT NULL,price INTEGER NOT NULL,total INTEGER NOT NULL, FOREIGN KEY(user_id) REFERENCES users(id));")

        # Insert entry into history table
        update_history(user, "buy", symbol, shares)

        # Insert into inventory
        total = budget * price
        cash = budget - round(total, 2)

        try:
            old_shares = db.execute("SELECT shares FROM inventory WHERE user_id = ? AND symbol = ?", user, symbol)
            old_shares = old_shares[0]["shares"]
            shares = old + shares
        except:
            pass

        update_inventory(symbol, user, data["name"], shares, price, cash)

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute("SELECT * FROM history WHERE user_id = ?;",
                         session["user_id"])
    return render_template("history.html", history=history)


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
    """Get stock quote"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        results = lookup(symbol)
        if not symbol:
            return apology("Please fill in all fields")
        if not results:
            return apology("Company not found")
        return render_template("quoted.html", results=results)

    if request.method == "GET":
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        user = db.execute("SELECT * FROM users WHERE username == (?)",
                          username)

        if not username or not password or not confirmation:
            return apology("Please fill in all fields")

        if user:
            return apology("User already exists in database")

        if password == confirmation:
            hash = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",
                       username, hash)
            # Redirect user to home page
            return redirect("/")
        else:
            return apology("Passwords do not match")
    else:

        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        symbol = (request.form.get("symbol")).upper()
        shares = int(request.form.get("shares"))
        user = session["user_id"]
        check_share = db.execute("SELECT shares FROM inventory WHERE symbol = ? AND user_id = ?;",
                                 symbol, user)
        check = check_share[0]["shares"]

        if shares < 1:
            return apology("Please input a positive integer")
        elif shares > check:
            return apology("You don't own that many shares")

        update_history(user, "sell", symbol, shares)
        data = lookup(symbol)
        amount = data["price"] * shares

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user)
        cash = cash[0]["cash"]
        cash = round(cash, 2) + round(amount, 2)

        update_inventory(symbol, user, data["name"], shares, data["price"], cash)


        #update_sell(symbol, user, shares, check)

        return redirect("/")

    else:
        data = db.execute("SELECT * FROM inventory WHERE user_id = ?;", session["user_id"])
        return render_template("sell.html", data=data)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


def update_inventory(symbol, user, company, shares, price, cash):
    inventory = db.execute("SELECT * FROM inventory WHERE user_id = ?", user)
    total = shares * price

    if not inventory:
        db.execute("INSERT INTO inventory (user_id, symbol, company, shares, price, total) VALUES(?, ?, ?, ?, ?, ?)",
                   user, symbol, company, shares, price, total)
    else:
        db.execute("UPDATE inventory SET shares = ?, total = ? WHERE symbol = ? AND user_id = ?;",
                   shares, total, symbol, user)

    db.execute("UPDATE users SET cash = ? WHERE id = ?;",
                   cash, user)


def update_history(user, action, symbol, shares):
    now = datetime.now()
    date = now.strftime("%d/%m/%Y %H:%M:%S")
    results = lookup(symbol)
    price = results["price"]
    company = results["name"]
    db.execute("INSERT INTO history (user_id, action, symbol, shares, price, date) VALUES(?, ?, ?, ?, ?, ?)",
               user, action, symbol, shares, price, date)