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
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        // The argument must be 26 chars long
        string key = argv[1];
        if (strlen(key) != 26)
        {
            printf("Key must contain 26 characters\n");
            return 1;
        }
        else
        {

        }
        // Only alphabetic characters
        for (int i = 0; i < strlen(key); i++)
        {
            if (!isalpha(key[i]))
            {
                printf("Key must contain alphabetic characters only\n");
                return 1;
            }
        }

        // The characters must be unique
        string abc = "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < 26; i++)
        {
            int quantity = 0;
            for (int j = 0; j < 26; j++)
            {
                if (abc[i] == tolower(key[j]))
                {
                    quantity++;
                }
            }
            if (quantity != 1)
            {
                printf("The characters must be unique\n");
                return 1;
            }
        }

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
                newChar = key[letterASCII]; // change the letter
                newChar = toupper(newChar); // back to upper-case
            }

            // a-z (mins)
            if (letterASCII >= 97 && letterASCII <= 122)
            {
                letterASCII -= 97;
                newChar = key[letterASCII]; // change the letter
                newChar = tolower(newChar); // back to lower-case
            }

            // Append the new char
            printf("%c", newChar);

        }

        printf("\n");
        return 0;
    }

}