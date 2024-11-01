#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int get_points(string s, char letters[], int scores[]);

int main(void)
{
    char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int scores[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    string input1 = get_string("Player 1: ");
    string input2 = get_string("Player 2: ");

    int input1_score = get_points(input1, letters, scores);
    int input2_score = get_points(input2, letters, scores);

    if (input1_score > input2_score)
    {
        printf("Player 1 wins!\n");
    }
    else if (input1_score < input2_score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int get_points(string word, char letters[], int scores[])
{
    int points = 0;
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        if (isalpha(word[i]))
        {
            for (int j = 0; j < 26; j++)
            {
                if (toupper(word[i]) == letters[j])
                {
                    points += scores[j];
                }
            }
        }
    }

    return points;
}
