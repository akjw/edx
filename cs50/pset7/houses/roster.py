# TODO

from sys import argv, exit
import cs50

if len(argv) != 2:
    print("Missing argument")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

for row in db.execute("SELECT first, middle, last, birth FROM students WHERE house=? ORDER BY last, first", argv[1]):
    first = row.get('first')
    middle = row.get('middle')
    last = row.get('last')
    birth = row.get('birth')
    if middle == None:
        print(f"{first} {last}, born {birth}")
    else:
        print(f"{first} {middle} {last}, born {birth}")

