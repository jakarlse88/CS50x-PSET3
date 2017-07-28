#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("In minutes, how long was your shower? ");
    int y = get_int();
    
    printf("Your shower consumed the equivalent of %.0f bottles of water.\n", (y * 1.5) * 128 / 16);
}