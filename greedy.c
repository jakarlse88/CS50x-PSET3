#include <stdio.h>
#include <cs50.h>
#include <math.h>

float change_owed;
int coins;

int main(void)
{   
    printf("Please input a non-negative number: ");
    change_owed = get_float();
    
    while (change_owed <= 0)
    {
        printf("Please input a non-negative number: ");
        change_owed = get_float();
    }
    
    int change_rounded = round(change_owed*100);
    
    while (change_rounded > 0) {
        if (change_rounded - 25 >= 0) {change_rounded = change_rounded - 25; coins ++;}
        else if (change_rounded - 10 >= 0) {change_rounded = change_rounded - 10; coins ++;}
        else if (change_rounded - 5 >= 0) {change_rounded = change_rounded -5; coins ++;}
        else if (change_rounded - 1 >= 0) {change_rounded = change_rounded - 1; coins ++;}
        }
    
    printf("%i\n", coins);
}    
    
