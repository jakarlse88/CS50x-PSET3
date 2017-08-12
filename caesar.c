#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define ASCII_LOWER_START 97
#define ASCII_LOWER_END 122
#define ASCII_UPPER_START 65
#define ASCII_UPPER_END 90

char ciphertext;

int main(int argc, string argv[])
{
    // argc is insufficient; exit and return 1 //
    if (argc < 2)
    {
        printf("Error: missing cipher key.\n");
        return 1;
    }
    
    // Program proceeds with assumed non-negative integer command line argument present //
    else
    {
        // Convert key to int //
        int key = atoi(argv[1]);
        
        // Get plaintext from user //
        printf("plaintext: ");
        string plaintext = get_string();
        
        // Print "ciphertext: " to comply with check50 //
        printf("ciphertext: ");
        
        // Iterate through each letter in plaintext //
        for (int i = 0, j = strlen(plaintext); i < j; i++)
        {
            // Is plaintext[i] uppercase? Rotate while preserving case, then print //
            if (plaintext[i] >= ASCII_UPPER_START && plaintext[i] <= ASCII_UPPER_END)
            {
                ciphertext = ((plaintext[i] - ASCII_UPPER_START) + key) % ALPHABET_SIZE;
                printf("%c", ciphertext + ASCII_UPPER_START);
            }
            // Is plaintext[i] lowercase? Rotate while preserving case, then print //
            else if (plaintext[i] >= ASCII_LOWER_START && plaintext[i] <= ASCII_LOWER_END)
            {
                ciphertext = ((plaintext[i] - ASCII_LOWER_START) + key) % ALPHABET_SIZE;
                printf("%c", ciphertext + ASCII_LOWER_START);
            }
            // plaintext[i] is not alphabetical, so just print it //
            else
            {
                ciphertext = plaintext[i];
                printf("%c", ciphertext);
            }
        }
        // Print newline and return 0 to wrap up //
        printf("\n");
        return 0;
    }
}