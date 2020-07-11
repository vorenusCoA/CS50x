from cs50 import SQL
import sys
import csv

# Check numbers of arguments
if len(sys.argv) != 2:
    print("Usage: python roster.py houseName")
    sys.exit(1)

# Connection to the DB
db = SQL("sqlite:///students.db")

# Name of the house to look for
house = sys.argv[1]
# Query the DB
rows = db.execute("SELECT * FROM students WHERE house=? ORDER BY last, first", house)

# For each row we print full name and birth
for row in rows:
    print(row["first"]
          + " "
          + (row["middle"] + " " if row["middle"] != None else "")
          + row["last"]
          + ", "
          + "born "
          + str(row["birth"]))
