import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT symbol, SUM(shares) as shares FROM transactions WHERE user_id=:user_id GROUP BY symbol;", user_id=session["user_id"])
    portfolio = []
    for row in rows:
        stock = lookup(row["symbol"])
        portfolio.append({
            "name": stock["name"],
            "symbol": row["symbol"],
            "shares": row["shares"],
            "price": usd(stock["price"]),
            "total_value": usd(stock["price"] * row["shares"])
        })
    rows = db.execute("SELECT cash FROM users WHERE id=:id;", id=session["user_id"])
    cash = rows[0]["cash"]
    grand_total = int(cash) + stock["price"] * row["shares"]
    return render_template("index.html", portfolio=portfolio, cash=usd(cash), grand_total=usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("must provide symbol", 403)
        elif not request.form.get("shares").isdigit:
            return apology("number of shares must be positive integer", 403)
        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))
        result = lookup(symbol)
        if not result:
            return apology("no quote found", 403)
        rows = db.execute("SELECT cash FROM users WHERE id =:id", id=session["user_id"])
        balance = rows[0]["cash"] - shares * result["price"]
        if balance < 0:
            return apology("insufficient funds", 403)
        db.execute("UPDATE users SET cash=:balance WHERE id=:id", balance=balance, id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
        user_id=session["user_id"],
        symbol=symbol,
        shares=shares,
        price=shares * result["price"])
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id=:user_id;", user_id=session["user_id"])
    for row in rows:
        row["price"] = usd(row["price"])
    print(rows)
    return render_template("history.html", rows=rows)


@app.route("/password", methods=["GET", "POST"])
def password():
    """Change password"""
    if request.method == "GET":
        return render_template("password.html")
    else:
        if not request.form.get("password") or not request.form.get("new_password"):
            return apology("fields cannot be empty", 403)
        # Get current password in database
        rows = db.execute("SELECT * FROM users WHERE id=:id",
                          id=session["user_id"])
        if not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("incorrect password", 403)
        # Update password
        db.execute("UPDATE users SET hash=:hash WHERE id=:id", hash=generate_password_hash(request.form.get("new_password")), id=session["user_id"])
        return redirect("/")




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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)
        query = request.form.get("symbol").upper()
        result = lookup(query)
        if not result:
            return apology("no quote found", 403)
        return render_template("quoted.html", result={
               "name": result["name"],
               "symbol": result["symbol"],
               "price": usd(result["price"])
            })


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)
        else:
            rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
            # Ensure username is unique
            if len(rows) != 0:
                return apology("username taken", 403)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password was confirmed
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 403)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 403)

        # Insert user info
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
            username=request.form.get("username"),
            hash=generate_password_hash(request.form.get("password")))

        if not result:
            return apology("registration error", 403)
        session["user_id"] = result
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
         rows = db.execute("SELECT symbol FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING shares > 0;", user_id=session["user_id"])
         return render_template("sell.html", stocks=[ row["symbol"] for row in rows ])
    else:
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("must provide symbol", 403)
        elif not request.form.get("shares").isdigit:
            return apology("number of shares must be positive integer", 403)
        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))
        result = lookup(symbol)
        if not result:
            return apology("no quote found", 403)
        rows = db.execute("SELECT symbol, SUM(shares) as shares FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING shares > 0;", user_id=session["user_id"])
        for row in rows:
            if row["symbol"] == symbol:
                if row["shares"] < shares:
                    return apology("insufficient shares")
        rows = db.execute("SELECT cash FROM users WHERE id =:id", id=session["user_id"])
        balance = rows[0]["cash"] + shares * result["price"]
        db.execute("UPDATE users SET cash=:balance WHERE id=:id", balance=balance, id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
        user_id=session["user_id"],
        symbol=symbol,
        shares= -1 * shares,
        price=shares * result["price"])
        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)

# def validate(field):
#     if not field:
#         return apology(f"must have {field}", 403)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
