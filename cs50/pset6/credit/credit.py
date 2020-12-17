import re
from math import floor


def main():
    while True:
        try:
            credit_number = int(input("Number: "))
            if credit_number > 0:
                break
        except:
            print("")
    if validated(credit_number):
        checkType(credit_number)
    else:
        print("INVALID")


def validated(card):
    # get length of card number
    len = get_length(card)
    return (len == 13 or len == 15 or len == 16) and checksum(card)


def get_length(card):
    length = len(str(card))
    return length


def checksum(card):
    total = 0
    i = 0
    # for (int i = 0; card != 0; i++, card /= 10)
    while not card == 0:
        if i % 2 == 0:
            # add sum to sum of remaining numbers
            total += card % 10
        else:
            # multiply every other number by 2
            digit = 2 * (card % 10)
            # add digits of every product + qdd to sum
            total += digit % 10 + floor(digit / 10)
        i += 1
        card /= 10
        card = floor(card)
    # check final digit = 0
    return (total % 10) == 0


def checkType(card):
    s = str(card)
    if len(s) == 15:
        if re.search("^34*", s) or re.search("^37*", s):
            print("AMEX")
    elif len(s) == 16:
        if re.search("^51*", s) or re.search("^52*", s) or re.search("^53*", s) or re.search("^54*", s) or re.search("^55*", s):
            print("MASTERCARD")
        elif re.search("^4*", s):
            print("VISA")
    elif len(s) == 13:
        if re.search("^4*", s):
            print("VISA")
    else:
        print("INVALID")


main()