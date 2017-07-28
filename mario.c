#include <stdio.h>
#include <cs50.h>

void pyramid(int head);

int rows;
int spaces;
int hash_left;
int hash_right;

int main(void)
{
    printf("Please input a height for the pyramid, using a number between 0-23: ");
    int head = get_int();
    if (head < 0 || head > 23) 
    {
        printf("Please use a number between 0-23: ");
        head = get_int();
    }
    else if (head == 0)
    {
        printf("");
    }
    else 
    {
        pyramid(head);
    }
}

void pyramid(int head)
{
    for (rows = 0; rows < head; rows++)
    {
        for (spaces = 1; spaces < head - rows; spaces++)
        {
            printf(" ");
        }
        for (hash_left = head - rows; hash_left < head + 1; hash_left++)
        {
            printf("#");
        }
        printf("  ");
        for (hash_right = head - rows; hash_right < head + 1; hash_right++)
        {
            printf("#");
        }
        printf("\n");
    }
}