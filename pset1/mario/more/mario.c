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

    // Print the piramids
    for (int i = 0; i < n; i++)
    {
        // Print the left spaces
        for (int j = 0; j < n - 1 - i; j++)
        {
            printf(" ");
        }
        // Print the left hashes
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        // Print the gap
        for (int j = 0; j < 2; j++)
        {
            printf(" ");
        }
        // Print right hashes
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        // Change of line
        printf("\n");
    }
}