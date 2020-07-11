#include <stdio.h>
#include <cs50.h>

bool checkSumOK(long creditCard);

int main(void)
{
    // Ask the user for a credit card number to check
    long creditCard = get_long("Number: ");

    if (checkSumOK(creditCard))
    {
        long copy = creditCard;
        // Check the number of digits
        int qDigits = 0;
        while (creditCard)
        {
            creditCard /= 10;
            qDigits++;
        }

        int ccArray[qDigits];
        int index = 0;
        while (copy)
        {
            ccArray[index] = copy % 10;
            copy /= 10;
            index++;
        }

        // The first digit is the last element
        int firstDigit = ccArray[qDigits - 1];
        int secondDigit = ccArray[qDigits - 2];

        // Check for American Express (34 or 37)
        if (qDigits == 15 && firstDigit == 3 && (secondDigit == 4 || secondDigit == 7))
        {
            printf("AMEX\n");
        }
        // Check for Visa (4)
        else if (firstDigit == 4 && (qDigits == 13 || qDigits == 16))
        {
            printf("VISA\n");
        }
        // Check for Master Card (51, 52, 53, 54, or 55)
        else if (qDigits == 16 && firstDigit == 5 && (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 || secondDigit == 4
                 || secondDigit == 5))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else
    {
        printf("INVALID\n");
    }

}

bool checkSumOK(long creditCard)
{
    // A copy for not loosing the original value
    long creditCardCopy = creditCard;

    // First we count the digits of the credit card having in mind the position of each element
    int capacityForEven = 0;
    int capacityForOdd = 0;
    int index = 0;
    while (creditCard)
    {
        int digit = creditCard % 10;
        if (index % 2 == 0)
        {
            capacityForEven++;
        }
        else
        {
            capacityForOdd++;
        }
        creditCard /= 10;
        index++;
    }

    // Now that we know the capacity of each array we can create them
    int evenArray[capacityForEven];
    int oddArray[capacityForOdd];

    // We have to use the copy since we have lost de value o creditCard
    // We put each element in its corresponding array
    index = 0;
    int evenIndex = 0;
    int oddIndex = 0;
    while (creditCardCopy)
    {
        int digit = creditCardCopy % 10;

        if (index % 2 == 0)
        {
            evenArray[evenIndex] = digit;
            evenIndex++;
        }
        else
        {
            oddArray[oddIndex] = digit;
            oddIndex++;
        }
        creditCardCopy /= 10;
        index++;
    }

    // Multiply by 2 each element of the odd array
    for (int i = 0; i < capacityForOdd; i++)
    {
        oddArray[i] *= 2;
    }

    // Sum the digits of all the elements in the odd array
    int oddSum = 0;
    for (int i = 0; i < capacityForOdd; i++)
    {
        // if the element has 2 digits we have to sum both
        if (oddArray[i] >= 10)
        {
            oddSum += oddArray[i] % 10; // second digit
            oddSum++; //first digit is alway 1
        }
        else
        {
            oddSum += oddArray[i];
        }
    }

    // Sum the digits of all the elements in the even array
    int evenSum = 0;
    for (int i = 0; i < capacityForEven; i++)
    {
        evenSum += evenArray[i];
    }

    // Now we sum both totals and if the last digit is 0 we are OK
    int total = oddSum + evenSum;
    if (total % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}