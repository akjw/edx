# TODO
from sys import argv, exit
import cs50
import csv

open("students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")
db.execute("CREATE TABLE students(first TEXT, middle TEXT, last TEXT, house TEXT, birth INT)")


if len(argv) != 2:
    print("Missing argument")
    exit(1)


with open(argv[1], "r") as students:
    students.readline()
    reader = csv.reader(students)
    for row in reader:
        fullname = row[0]
        first = ""
        middle = ""
        last = ""
        names = fullname.split()
        if len(names) == 2:
            first = names[0]
            middle = None
            last = names[1]
        if len(names) == 3:
            first = names[0]
            middle = names[1]
            last = names[2]
        house = row[1]
        birth = row[2]
        db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)