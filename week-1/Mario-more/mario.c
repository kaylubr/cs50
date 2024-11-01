#include <cs50.h>
#include <stdio.h>

void printrow(int space, int length);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        printrow(height - (i + 1), i + 1);
    }
}

void printrow(int space, int length)
{
    for (int i = 0; i < space; i++)
    {
        printf(" ");
    }

    for (int j = 0; j < length; j++)
    {
        printf("#");
    }

    printf("  ");

    for (int i = 0; i < length; i++)
    {
        printf("#");
    }

    printf("\n");
}
