from cs50 import get_string
import re


amex_pattern = r'^3[47]\d{13}$'
mastercard_pattern = r'^5[12345]\d{14}$'
visa_pattern = r'^4(\d{12}|\d{15})$'


def main():
    number = get_string("Number: ")
    if validate(number):
        if re.match(amex_pattern, number):
            print("AMEX")
        elif re.match(mastercard_pattern, number):
            print("MASTERCARD")
        elif re.match(visa_pattern, number):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


def validate(number):
    # Convert the pattern into a list and reverse it
    digits = to_list(number)
    digits.reverse()

    # Add every second digit starting from end
    section_one = []
    for c in range(1, len(digits), 2):
        section_one.append(digits[c])

    # Add all of the numbers multiplied by 2
    sums_str = ""
    for digit in section_one:
        sums_str += str(int(digit) * 2)

    sums_list = to_list(sums_str)
    sums = sum([int(i) for i in sums_list])

    section_two = [sums]
    for c in range(0, len(digits), 2):
        section_two.append(int(digits[c]))

    total = sum(section_two)

    if total % 10 == 0:
        return True
    else:
        return False


def to_list(number):
    list = []
    for c in number:
        list.append(c)
    return list


main()
