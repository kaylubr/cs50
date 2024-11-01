#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool is_argc_valid(int argc);
bool is_length_valid(string arg);
bool contains_digit(string arg);
bool has_duplicate(string arg);
bool validate_args(int argc, string argv[]);
void validate_key(string key);
int get_text_idx(char letter);
char rotate_char(string key, char c);
void print_ciphered(string key, string text);

int main(int argc, string argv[])
{
    if (!validate_args(argc, argv))
    {
        return 1;
    }

    string key = argv[1]; // Stores the argument into a var called key
    validate_key(key);    // Makes sure that the key's format is correct

    string text = get_string("plaintext:  ");
    print_ciphered(key, text);
    return 0;
}

bool is_argc_valid(int argc)
{
    // False if argument count is not equal to 2
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return false;
    }

    return true;
}

bool is_length_valid(string arg)
{
    int length = strlen(arg);
    // Return false if argv[1]'s length is greater or less than 26
    if (length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }
    return true;
}

bool contains_digit(string arg)
{
    for (int i = 0, length = strlen(arg); i < length; i++)
    {
        // Returns true if argv[1] has a non alphabetical character
        if (!isalpha(arg[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return true;
        }
    }

    return false;
}

bool has_duplicate(string arg)
{
    int length = strlen(arg);
    int counter = 1;
    for (int i = 0; i < length; i++)
    {
        for (int j = counter; j < length; j++)
        {
            // Returns true if there are duplicate value in the key
            if (arg[i] == arg[j])
            {
                printf("Key must not contain repeated characters.\n");
                return true;
            }
        }

        counter++;
    }

    return false;
}

int get_text_idx(char letter)
{
    return isupper(letter) ? letter - 'A' : letter - 'a';
}

char rotate_char(string key, char c)
{
    // A constant of the difference between the upper and lowercase value in the ASCII
    const int DIFFERENCE = 32;
    if (isalpha(c))
    {
        if (isupper(c))
        {
            return key[get_text_idx(c)];
        }
        else if (islower(c))
        {
            return key[get_text_idx(c)] + DIFFERENCE;
        }
    }

    return c;
}

void print_ciphered(string key, string text)
{
    printf("ciphertext: ");
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        printf("%c", rotate_char(key, text[i]));
    }
    printf("\n");
}

bool validate_args(int argc, string argv[])
{
    if (!is_argc_valid(argc))
        return false; // If the amount of arguments is incorrect
    if (!is_length_valid(argv[1]))
        return false; // If the key's length isn't 26
    if (contains_digit(argv[1]))
        return false; // If the key contains a digit
    if (has_duplicate(argv[1]))
        return false; // If the key has a duplicate character

    return true;
}

void validate_key(string key)
{
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        key[i] = toupper(key[i]);
    }
}
