#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define ASCII_LOW_START 97
#define ASCII_UP_START 65

char ciphertext[1000];
char key[1000];

int main(int argc, string argv[])
{
    // Validates argc, then makes a key array from argv[1] //
    if (argc < 2 || argc > 2)
    {
        printf("Error: invalid number of arguments. Please re-try.\n");
        return 1;
    }
    else 
    {
        for (int i = 0, j = strlen(argv[1]); i < j; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Error: invalid character in key. Please re-try.\n");
                return 1;
            }
            else if (isupper(argv[1][i]))
            {
                key[i] = tolower(argv[1][i]);
            }
            else
            {
                key[i] = argv[1][i];
            }
        }
    }
    
    // Gets plaintext //
    printf("plaintext: ");
    string plaintext = get_string();
    
    // Enciphers and prints, keeping case and ignoring non-alpha characters //
    for (int i = 0, j = strlen(plaintext), k = 0; i < j; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                int l = k % strlen(argv[1]);
                ciphertext[i] = ((plaintext[i] - ASCII_UP_START) + (key[l] - ASCII_LOW_START)) % ALPHABET_SIZE + ASCII_UP_START;
                k ++;
            }
            else if (islower(plaintext[i]))
            {
                int l = k % strlen(argv[1]);
                ciphertext[i] = ((plaintext[i] - ASCII_LOW_START) + (key[l] - ASCII_LOW_START)) % ALPHABET_SIZE + ASCII_LOW_START;
                k ++;
            }
            }
            else
            {
                ciphertext[i] = plaintext[i];
            }
    }
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}