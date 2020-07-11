#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // Check the numbers of arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        // The argument must be a non-negative integer
        string s = argv[1];
        for (int i = 0; i < strlen(s); i++)
        {
            if (!isdigit(s[i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        // Convert the argument to int
        int key = atoi(s);

        // Promp the user to input the message
        string message = get_string("plaintext: ");

        printf("ciphertext: ");

        // Iterate over the message
        for (int i = 0; i < strlen(message); i++)
        {
            // Transform each character into ASCII
            int letterASCII = (int) message[i];
            // The letter encripted
            int newChar = letterASCII;

            // A-Z (MAYUS)
            if (letterASCII >= 65 && letterASCII <= 90)
            {
                letterASCII -= 65; // move it to "index 0"
                newChar = (letterASCII + key) % 26; // change the letter
                newChar += 65; // back to the correct ASCII position
            }

            // a-z (mins)
            if (letterASCII >= 97 && letterASCII <= 122)
            {
                letterASCII -= 97;
                newChar = (letterASCII + key) % 26;
                newChar += 97;
            }

            // Append the new char
            printf("%c", newChar);

        }

        printf("\n");
        return 0;
    }

}