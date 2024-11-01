#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int get_index(float LETTERS, float SENTENCES);
void print_readability(int index);

int main(void)
{

    string text = get_string("Text: ");

    // Program will stop if there is no string input
    if (strlen(text) == 0)
    {
        return 1;
    }

    // Calculates the index using The Coleman-Liau index formula
    float LETTERS = ((float) (count_letters(text)) / (float) count_words(text)) * 100.0;
    float SENTENCES = ((float) (count_sentences(text)) / (float) count_words(text)) * 100.0;
    int index = get_index(LETTERS, SENTENCES);

    // A function that prints the readability of a sentence
    print_readability(index);
}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isalpha(text[i]))
        {
            // Add one in letters counter if the text[i] is a alphabet character
            letters++;
        }
    }

    return letters;
}

int count_words(string text)
{
    int words = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isspace(text[i]))
        {
            // Increments word counter if there's a white space after the word
            words++;
        }
    }

    // Return zero if there is no input
    if (words == 0)
    {
        return 0;
    }

    // Adds one since every phrase has atleast one word
    return words + 1;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            // Increments sentences counter if the word is ending with either ".", "?", or "!"
            sentences++;
        }
    }

    return sentences;
}

int get_index(float LETTERS, float SENTENCES)
{
    // Return the index using The Coleman-Liau index formula
    // index = 0.0588 * L - 0.296 * S - 15.8
    return round(0.0588 * LETTERS - 0.296 * SENTENCES - 15.8);
}

void print_readability(int index)
{
    if (index >= 16)
    {
        // Prints 16+ if grade is higher or equal than 16
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        // Prints "Before Grade 1" if grade is lower than 1
        printf("Before Grade 1\n");
    }
    else
    {
        // Prints the grade level based on the index
        printf("Grade %i\n", index);
    }
}
