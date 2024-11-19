
def main():
    text = input("Text: ")
    compute_grade(text)


def letter_count(text):
    count = 0
    for letter in text:
        if letter.isalpha():
            count += 1
    return count


def word_count(text):
    count = 0
    for character in text:
        if character.isspace():
            count += 1
    return count + 1


def sentence_count(text):
    count = 0
    for character in text:
        if ispunct(character):
            count += 1
    return count


def ispunct(character):
    if character == "!":
        return True
    elif character == "?":
        return True
    elif character == ".":
        return True

    return False


# Compute grade using the Coleman-Liau index
def compute_grade(text):
    L = (letter_count(text) / word_count(text)) * 100
    S = (sentence_count(text) / word_count(text)) * 100
    grade = round(0.0588 * L - 0.296 * S - 15.8)

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


main()
