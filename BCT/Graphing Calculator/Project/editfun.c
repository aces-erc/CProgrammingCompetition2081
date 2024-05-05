

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define BUFFER_SIZE 1000


int main()
{
    FILE * fPtr;
    FILE * fTemp;
    rename("prototype.c","prototype.txt");
    char path[100]="prototype.txt";   
    char buffer[BUFFER_SIZE];
    char newline[BUFFER_SIZE];
    char modline[BUFFER_SIZE]="double r = ";
    int line=6, count;

    fflush(stdin);

    printf("Enter the Function: ", line);
    fgets(newline, BUFFER_SIZE, stdin);
    strcat(modline,newline);

    fPtr  = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w"); 

    if (fPtr == NULL || fTemp == NULL)
    {
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }


    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        count++;

        if (count == line)
            fputs(modline, fTemp);
        else
            fputs(buffer, fTemp);
    }



    fclose(fPtr);
    fclose(fTemp);



    remove(path);

    rename("replace.tmp", path);

    printf("\nSuccessfully replaced '%d' line with '%s'.", line, newline);

    rename("prototype.txt","prototype.c");

    system("gcc prototype.c -o prototype.exe -mwindows");
    system("prototype.exe") ;
    return 0;
}