import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portfolio = db.execute("SELECT symbol, SUM(quantity) FROM transactions WHERE userid = :u GROUP BY symbol HAVING SUM(quantity)>0", u=session['user_id'])
    if len(portfolio) == 1 and portfolio[0]['symbol'] == None:
        return redirect("/buy")
    else:
        for stock in portfolio:
            info = lookup(stock['symbol'])
            stock['price'] = info['price']
            stock['name'] = info['name']
            stock['value'] = stock['price'] * stock['SUM(quantity)']
        cash = db.execute("SELECT cash FROM users WHERE id = :u", u=session['user_id'])
        return render_template("display.html", stocks=portfolio, cash=cash[0]['cash'])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                return apology("Please enter a valid number of shares.", 400)
            else:
                stock = lookup(request.form.get("symbol"))
                # if stock is null then error
                if not stock:
                    return apology("Please confirm the symbol entered", 400)
                else:
                    cash = db.execute("SELECT cash FROM users WHERE id = :u", u=session['user_id'])
                    if cash[0]["cash"] >= stock["price"] * shares:
                        # insert transaction information
                        db.execute("INSERT INTO transactions (userid, symbol, price, quantity, date) VALUES (:i, :s, :p, :sh, :t)", i=session['user_id'], s=stock["symbol"], p=stock['price'], sh=shares, t=datetime.utcnow())
                        # update user's cash
                        db.execute("UPDATE users SET cash = cash - :p * :s WHERE id = :i", p=stock['price'], s=shares, i=session['user_id'])
                        return redirect("/")
                    else:
                        return apology("Sorry. Not enough cash available.", 400)
        except:
            return apology("Please enter a valid number of shares.", 400)
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT * FROM transactions WHERE userid = :u ORDER BY date", u=session['user_id'])
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
        rows = db.execute("SELECT * FROM users WHERE username = :u", u=request.form.get("username"))

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
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # look up information from the entered symbol
        quote = lookup(request.form.get("symbol"))
        # return apology if invalid quote
        if not quote:
            return apology("Incorrect Symbol Entered.", 400)
        # else diplay quote information
        else:
            return render_template("quoted.html", symbol=quote["symbol"], name=quote["name"], price=quote["price"])

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Missing username!", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("Missing password!", 400)

        # Ensure that passwords match
        elif not (request.form.get("password") == request.form.get("confirmation")):
            return apology("Passwords must match", 400)

        else:
            hash = generate_password_hash(request.form.get("password"))
            result = db.execute("INSERT INTO users (username, hash) VALUES (:u, :h)", u=request.form.get("username"), h=hash)
            if not result:
                return apology("Username already exists!", 400)
            else:
                # Remember which user has logged in
                rows = db.execute("SELECT * FROM users WHERE username = :u", u=request.form.get("username"))
                session["user_id"] = rows[0]["id"]
                # Redirect user to home page
                return redirect("/")
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("registration.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # search for the stock in the user's portfolio
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
            if shares < 0:
                return apology("Please enter a positive integer", 400)
            else:
                portfolio = db.execute("SELECT symbol, SUM(quantity) FROM transactions WHERE userid = :u AND symbol = :s", u=session['user_id'], s=symbol)
                # get the stock's informaton
                stock = lookup(symbol)
                # if the stock does not exist return error
                if not stock:
                    return apology("Please confirm the symbol entered", 400)
                # elseif the user does not have enough shares of the stock return error
                elif portfolio[0]['SUM(quantity)'] == None or portfolio[0]['SUM(quantity)'] < shares:
                    return apology("You do not enough shares of this stock", 400)
                # else record transaction
                else:
                    db.execute("INSERT INTO transactions (userid, symbol, price, quantity, date) VALUES (:u, :s, :p, :sh, :t)", u=(session['user_id']), s=symbol, p=stock['price'], sh=-shares, t=datetime.utcnow())
                    # update user's cash
                    db.execute("UPDATE users SET cash = cash + :p * :sh WHERE id = :u", u=session['user_id'], p=stock['price'], sh=shares)
                    return redirect("/")
        except:
            return apology("Please enter a valid number of shares.", 400)
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
