#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct criketers

{
    int run;
    char name[25];
    int ball;
    int four;
    int six;
} cr;

void addrecord(cr **arr, int *n);
void displayrecord(cr *arr, int n);
void deleterecord(cr **arr, int *n);
void updaterecord(cr *arr, int n);

int main()
{
    system("clear");
    int i, n;
    FILE *ptr;
    ptr = fopen("cric.txt", "a");
    if (ptr == NULL)
    {
        printf("error opening the file:");
        fclose(ptr);
        return 1;
    }

    int add, c, choice;

    printf("==================CRICKET SCORE BOARD=================\n");
    printf("Enter the number of players whose details you want to add::");
    scanf("%d", &n);
    cr *arr = malloc(n * sizeof(cr)); // Initialize arr to Null
    if (arr == NULL)
    {
        printf("memory allocation failed:");
        fclose(ptr);
        return 1;
    }

    fprintf(ptr, "Name Runs Balls Fours Sixes\n");
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the details of the player number %d\n", i + 1);
        printf("Name:");
        while (getchar() != '\n')
            ;                          // clear input buffer
        fgets(arr[i].name, 30, stdin); // use of fgets

        printf("Runs:");
        scanf("%d", &arr[i].run);

        printf("Balls:");
        scanf("%d", &arr[i].ball);

        printf("Four: ");
        scanf("%d", &arr[i].four);

        printf("Six:");
        scanf("%d", &arr[i].six);

        fprintf(ptr, "%s\n%d\n%d\n%d\n%d\n", arr[i].name, arr[i].run, arr[i].ball, arr[i].four, arr[i].six);
    }
    fclose(ptr);

    do
    {

        printf("\n1:Add New Players\n2:Score Card\n3:Delete Record \n4:Update:\n5:Exit Program\n");
        scanf("%d", &choice);
        switch (choice)
        {

        case 1:
            addrecord(&arr, &n);
            break;

        case 2:
            displayrecord(arr, n);
            break;

        case 3:
            deleterecord(&arr, &n);

            break;

        case 4:
            updaterecord(arr, n);

            break;

        case 5:
        {
            printf("----------You Have Successfully Exited Form Program----------");
            exit(1);
        }

        default:
            printf("Invlaid Choice::Enter any key to continue:\n  ");

            while (getchar() != '\n')
                ;
            getchar();
            break;
        }

    } while (choice != 5);
    free(arr); // free dynamically allocate  memory
    return 0;
}
void addrecord(cr **arr, int *n)
{
    int add, i;
    printf("\nenter the number of additional players whose data you want to enter::");
    scanf("%d", &add);

    *arr = realloc(*arr, (*n + add) * sizeof(cr)); // Reallocate memory for arr
    for (i = *n; i < (*n + add); i++)
    {
        printf("\nEnter the details of the player number %d\n", i + 1);
        printf("Name:");
        while (getchar() != '\n')
            ;
        // clear input buffer
        fgets((*arr)[i].name, 30, stdin); // use of fgets

        printf("Runs: ");
        scanf("%d", &(*arr)[i].run);
        // while ((c = getchar()) != '\n' && c != EOF) ;

        printf("Balls: ");
        scanf("%d", &(*arr)[i].ball);

        printf("Four: ");
        scanf("%d", &(*arr)[i].four);

        printf("Six: ");
        scanf("%d", &(*arr)[i].six);
    }
    *n += add;
    printf("\n");
    printf("\nPress any key to continue......\n");
    getchar();
    getchar();
}

void displayrecord(cr *arr, int n)
{
    int i;
    if (arr == NULL)
    {
        printf("NO data entered.Please enter the data first.\n");
    }
   printf("\n\n");
    printf("=======================================================================\n");
    printf("| %-15s | %-6s | %-6s | %-6s | %-6s |\n", "Batsman", "RUNS", "Balls", "Four", "Six");
    printf("=======================================================================\n");


    for (i = 0; i < n; i++)
    {
         printf(" %-15s  %23d  %5d  %6d  %6d \n",
               arr[i].name, arr[i].run, arr[i].ball, arr[i].four, arr[i].six);
    }
    printf("\nPress any key to continue......\n");
    getchar();
    getchar();
}

void deleterecord(cr **arr, int *n)
{
    if (arr == NULL || n == 0)
    {
        printf("No data entered. Please enter the data first.\n");
    }

    printf("\nEnter the index of the player you want to delete (1 to %d): ", *n);
    int deleteIndex;
    scanf("%d", &deleteIndex);
    if (deleteIndex < 1 || deleteIndex > *n)
    {
        printf("Invalid index.\n");
        printf("\nPress any key to continue......\n");
        getchar(); // Wait for user to press any key
        getchar(); // Capture the key press
    }
    else
    {
        // Shift elements to fill the gap left by the deleted record
        for (int i = deleteIndex - 1; i < *n - 1; i++)
        {
            (*arr)[i] = (*arr)[i + 1];
        }
        (*n)--; // Decrease the total number of players
        printf("\nRecord deleted successfully.\n");
    }
}

void updaterecord(cr *arr, int n)
{
    if (arr == NULL || n == 0)
    {
        printf("No data entered. Please enter the data first.\n");
    }

    printf("\nEnter the index of the player you want to update (1 to %d): ", n);
    int updateIndex;
    scanf("%d", &updateIndex);
    if (updateIndex < 1 || updateIndex > n)
    {
        printf("Invalid index.\n");
        printf("\nPress any key to continue......\n");
        getchar(); // Wait for user to press any key
        getchar(); // Capture the key press
    }
    else
    {
        printf("Enter the updated details of the player:\n");
        printf("Name:");
        while (getchar() != '\n')
            ; // clear input buffer
        fgets(arr[updateIndex - 1].name, 30, stdin);
        printf("Runs: ");
        scanf("%d", &arr[updateIndex - 1].run);
        printf("Balls: ");
        scanf("%d", &arr[updateIndex - 1].ball);
        printf("Four: ");
        scanf("%d", &arr[updateIndex - 1].four);
        printf("Six: ");
        scanf("%d", &arr[updateIndex - 1].six);
        printf("\nRecord updated successfully.\n");
    }
}
