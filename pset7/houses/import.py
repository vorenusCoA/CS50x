from cs50 import SQL
import sys
import csv

# Check numbers of arguments
if len(sys.argv) != 2:
    print("Usage: python import.py data.csv")
    sys.exit(1)

# Read the file
with open(sys.argv[1]) as file:
    reader = csv.reader(file)
    data = list(reader)

# Connection to the DB
db = SQL("sqlite:///students.db")

dataLength = len(data)
# Avoid the first row (names of columns)
for row in range(1, dataLength):

    # Get the name
    fullName = data[row][0].split(" ")
    firstName = fullName[0]
    if len(fullName) == 3:
        middleName = fullName[1]
        lastName = fullName[2]
    else:
        middleName = None
        lastName = fullName[1]

    # Get the House
    house = data[row][1]

    # Get the birth year
    year = data[row][2]

    # INSERT
    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)",
               firstName, middleName, lastName, house, year)

