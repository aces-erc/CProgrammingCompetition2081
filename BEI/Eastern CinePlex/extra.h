#include <stdio.h>
#include <string.h>

// Details of movies

void pattern()
{
    for (int i = 0; i < 3; i++)
    {
        printf("\n");
    }
    for (int i = 0;  i < 50; i++)
    {
        printf(".");
    }
    for (int i = 0; i < 3; i++)
    {
        printf("\n");
    }
}

// Choice of authentication: interface generation
int first_choice(void)
{
    pattern();
    printf("\tWELCOME TO Eastern CinePlex\n\tPLEASE SELECT...\n\t1) ADMIN LOGIN\n\t2) USER REGISTRATION\n\t3) USER LOGIN\n\t4) EXIT SYSTEM");
    pattern();
    printf("Enter your choice : ");
    int a; 
    scanf("%d", &a);
    return a;
}