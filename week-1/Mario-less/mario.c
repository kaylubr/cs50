#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);

int main(void)
{
    // Prompt the user for the pyramid's height
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    print_row(0, n);
}

void print_row(int spaces, int bricks)
{
    if (bricks < 1)
    {
        return;
    }

    print_row(spaces + 1, bricks - 1);

    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
    return;
}
