from cs50 import get_string
from math import floor


def main():
    text = get_string("Text: ")
    verify(text)


def verify(input):
    l = count_letters(input)
    s = count_sentences(input)
    w = count_words(input)
    get_level(l, w, s)


def count_letters(input):
    letters = 0
    for i in range(len(input)):
        if input[i].isalpha():
            letters += 1
    return letters


def count_sentences(input):
    sentences = 0
    for i in range(len(input)):
        if input[i] == "." or input[i] == "?" or input[i] == "!":
            sentences += 1
    return sentences


def count_words(input):
    words = 1
    for i in range(len(input)):
        if input[i].isspace():
            words += 1
    return words


def get_level(l, w, s):
    L = (l / w) * 100
    S = (s / w) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)
    if index < 1:
        print("Before Grade 1\n")
    elif index > 16:
        print("Grade 16+\n")
    else:
        print(f"Grade {index}\n")


main()