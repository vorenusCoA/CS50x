#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    // Ask the user for a positive price
    float price;
    do
    {
        price = get_float("Change owed: ");
    }
    while (price < 0);

    // Converting dollars into cents
    int cents = round(price * 100);

    // Coins used
    int qCoins = 0;
    while (cents > 0)
    {
        if (cents >= 25)
        {
            cents = cents - 25;
        }
        else if (cents >= 10)
        {
            cents = cents - 10;
        }
        else if (cents >= 5)
        {
            cents = cents - 5;
        }
        else
        {
            cents--;
        }
        qCoins++;
    }

    printf("%i\n", qCoins);
}