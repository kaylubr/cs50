import sys

while True:
    try:
        height = int(input("Height: "))
        if height > 0 and height < 9:
            break
    except ValueError:
        pass

for i in range(height):
    print(" " * (height - 1 - i), end="")
    print("#" * (1 + i), end="")
    print("  ", end="")
    print("#" * (1 + i))


