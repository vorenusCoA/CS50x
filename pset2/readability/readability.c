#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // Promp the user to enter the text to analize
    string text = get_string("Text: ");

    // Count letters, words and sentences
    // It is important to use float so we don´t loose info in the final division
    float qLetters = 0;
    float qWords = 1; // Since we count spaces we have to add an extra 1 for the last word
    float qSentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        // Letters
        if (isalpha(text[i]))
        {
            qLetters++;
        }
        else if ((int)text[i] == 32) // space (Words)
        {
            qWords++;
        }
        else if ((int)text[i] == 33 || (int)text[i] == 46 || (int)text[i] == 63) // ! . ? (Sentences)
        {
            qSentences++;
        }
    }

    // Calculate de grade with Coleman-Liau formula
    float grade = 0.0588 * (qLetters * 100 / qWords) - 0.296 * (qSentences * 100 / qWords) - 15.8;

    if (round(grade) >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (round(grade) < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", round(grade));
    }

}