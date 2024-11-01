#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_valid_arg_count(int argc);
bool is_all_digits(string arg);
bool is_positive_num(string arg);
int caesar_algo(int index, int key);
char rotate_char(char c, int key);

const int UPPERCASE_A = 65;
const int LOWERCASE_A = 97;

int main(int argc, string argv[])
{
    // Error checking for wrong command line input
    if (!is_valid_arg_count(argc) || !is_all_digits(argv[1]) || !is_positive_num(argv[1]))
    {
        printf("Usage: ./caesar KEY\n");
        return 1;
    }

    // Converts the second command line argument into an integer
    const int key = atoi(argv[1]);

    string text = get_string("plaintext:  ");
    printf("ciphertext: ");

    // Print each rotated character one by one
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        printf("%c", rotate_char(text[i], key));
    }

    printf("\n");
}

// Function for checking if there are less than or more than 2 commands
bool is_valid_arg_count(int argc)
{
    if (argc != 2)
    {
        return false;
    }

    return true;
}

// Function for checking if the input is an integer
bool is_all_digits(string arg)
{
    for (int i = 0, length = strlen(arg); i < length; i++)
    {
        if (!isdigit(arg[i]))
        {
            return false;
        }
    }

    return true;
}

// Function to check if the input is not a negative number
bool is_positive_num(string arg)
{
    int num = atoi(arg);
    if (num < 0)
    {
        return false;
    }

    return true;
}

// Caesar's algorithm function
int caesar_algo(int index, int key)
{
    return (index + key) % 26;
}

char rotate_char(char c, int key)
{
    int index;

    // Do operations if character is in the alphabet
    if (isalpha(c))
    {
        if (isupper(c))
        {
            // Converts character into an index
            index = c % UPPERCASE_A;
            c = caesar_algo(index, key);
            // Adds 65 since the first uppercase letter of the alphabet's value is 65
            c = c + UPPERCASE_A;
        }
        else if (islower(c))
        {
            // Converts character into an index
            index = c % LOWERCASE_A;
            c = caesar_algo(index, key);
            // Adds 97 since the first lowercase letter of the alphabet's value is 97
            c = c + LOWERCASE_A;
        }
    }

    return c;
}
