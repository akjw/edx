
def main():
    while True:
        try:
            h = int(input("Height: "))
            if h >= 1 and h <= 8:
                break
        except:
            print("Invalid input.")
    for r in range(h):
        print(" " * (h - r - 1) + "#" * (r + 1) + " " * 2 + "#" * (r + 1))


main()