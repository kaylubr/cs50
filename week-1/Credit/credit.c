#include <cs50.h>
#include <stdio.h>

int length(long number);
int getDigit(long number);
int getOtherDigit(long number);
int getFirstDigit(long number);
int getFirstTwoDigits(long number);
void isValid(long number);
void getCardName(long number);

int main(void)
{
    long number = get_long("Number: ");
    isValid(number);
}

int length(long number)
{
    int counter = 0;
    while (number > 0)
    {
        number = number / 10;
        counter++;
    }

    return counter;
}

int getDigit(long number)
{
    long accumulator = 0;
    long holder = number;
    int counter = 1;
    for (int i = 0; i < length(number); i++)
    {
        if (counter % 2 == 0)
        {
            int last_digit = holder % 10;
            int multiply_by_two = last_digit * 2;

            if (length(multiply_by_two) == 2)
            {
                int f_dig = multiply_by_two / 10;
                int l_dig = multiply_by_two % 10;
                accumulator = accumulator + (f_dig + l_dig);
                holder = holder / 10;
                counter++;
                continue;
            }

            accumulator = accumulator + multiply_by_two;
        }

        holder = holder / 10;
        counter++;
    }

    return accumulator;
}

int getOtherDigit(long number)
{
    long accumulator = 0;
    long holder = number;
    int counter = 1;
    for (int i = 0; i < length(number); i++)
    {
        if (counter % 2 != 0)
        {
            int last_digit = holder % 10;
            accumulator = accumulator + last_digit;
        }

        holder = holder / 10;
        counter++;
    }

    return accumulator;
}

void isValid(long number)
{
    int get_sum = getDigit(number) + getOtherDigit(number);

    if (get_sum % 10 == 0)
    {
        getCardName(number);
    }
    else
    {
        printf("INVALID\n");
    }
}

void getCardName(long number)
{
    if (length(number) == 15 &&
        (getFirstTwoDigits(number) == 34 || getFirstTwoDigits(number) == 37))
    {
        printf("AMEX\n");
    }
    else if (length(number) == 16 &&
             (getFirstTwoDigits(number) == 51 || getFirstTwoDigits(number) == 52 ||
              getFirstTwoDigits(number) == 53 || getFirstTwoDigits(number) == 54 ||
              getFirstTwoDigits(number) == 55))
    {
        printf("MASTERCARD\n");
    }
    else if (length(number) == 13 || (length(number) == 16 && getFirstDigit(number) == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int getFirstTwoDigits(long number)
{
    long holder = number;
    long two_digits;
    for (int i = 0; i < length(number) - 2; i++)
    {
        holder = holder / 10;
    }

    two_digits = holder;

    return two_digits;
}

int getFirstDigit(long number)
{
    long holder = number;
    long digit;
    for (int i = 0; i < length(number) - 1; i++)
    {
        holder = holder / 10;
    }

    digit = holder;

    return digit;
}
