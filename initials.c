#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // Prompt for name (no written prompt for user -- triggers faulty check50) //
    string name = get_string();

    // Print first letter of name //
    printf("%c", toupper(name[0]));
    
    // Loop through rest of name, printing every letter that is space+1 //
    for (int i = 0, j = strlen(name); i < j; i++)
    {
        if (isblank(name[i]) == true)
        {
            printf("%c", toupper(name[i + 1]));
        }
    }
    // Print newline //
    printf("\n");
}