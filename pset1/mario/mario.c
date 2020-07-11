#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask the user for a height between 1-8
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Print the piramid
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        // Change of line
        printf("\n");
    }
}