from cs50 import get_float


def main():
    while True:
        cash = get_float("Change owed: ")
        if cash >= 0:
            break
    cash *= 100

    quarters = calculate_quarters(cash)
    cash = cash - (quarters * 25)

    dimes = calculate_dimes(cash)
    cash = cash - (dimes * 10)

    nickels = calculate_nickels(cash)
    cash = cash - (nickels * 5)

    pennies = calculate_pennies(cash)
    cash = cash - (pennies * 1)

    print(quarters + dimes + nickels + pennies)


def calculate_quarters(cents):
    return int(cents / 25)


def calculate_dimes(cents):
    return int(cents / 10)


def calculate_nickels(cents):
    return int(cents / 5)


def calculate_pennies(cents):
    return int(cents / 1)


main()
