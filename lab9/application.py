import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        name = request.form.get("name")
        day = request.form.get("day")
        month = request.form.get("month")
        action = request.form.get("action")

        # Lowercase the name and capitalize it
        name = name.lower()
        name = name.capitalize()
        # Add the user's entry into the database
        if action == "add":
            db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
        # Delete the user's entry into the database

        elif action == "edit":
            db.execute("DELETE FROM birthdays WHERE name == (?)", name)
            db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)

        else:
            db.execute("DELETE FROM birthdays WHERE name == (?)", name)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)

