// Definition of standard libraries.
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include "extra.h"

#define MAX_SEATS 60
#define MAX_MOVIES 5
#define admin_username "Abhishek"
#define admin_password "pass"
int ticket_price = 500;
int movies_count = MAX_MOVIES;
int reservation_count = 0;

struct movie
{
    char name[30];
    int starting_time;
    int length;
    int screening_day;
    char screening_month[8];
    char genre[40];
    char director[50];
    int seats[MAX_SEATS];
    int num_seats;
};
struct movie film[5];
struct reservation
{
    char movies[30];
    char name[40];
    int seats[MAX_SEATS];
    int num_seats;
    int balance;
};

struct reservation reserve[100];

// For file i/o movies.
void initializeMoviesFile();
int saveMoviesToFile(struct movie[], int);
int loadMoviesFromFile(struct movie[], int *);

int saveReservationToFile(struct reservation[], int);
int loadReservationFromFile(struct reservation[], int *);

// For user side of things.
int user_interface(char[]);
int see_shows(void);
int see_movies(int, char[]);
int display_seats(int[], int);
int book_seats(char[]);
int cineplex_info(void);
int logout(void);

// For admin side of things
int admin_interface();
int view_current_shows();
int edit_movies();
int edit_price();
int view_reservation();
int see_reservation(char[]);
int view_balance();

// Login part
int registerUser();
int loginUser();
int admin_login();

// Main Function
int main()
{
    // Initialize movies file with default data if it doesn't exist
    FILE *file = fopen("movies.txt", "r");
    if (file == NULL) {
        initializeMoviesFile();
        printf("Initialized new file - Default Data.\n");
    } else {
        fclose(file);
    }

    // Load movies data from file.
    int numMovies = 0;
    if (loadMoviesFromFile(film, &numMovies) != 0)
    {
        printf("\tError loading movie data from file.\n\tExitting!!!\n");
        return 1;
    }
    movies_count = numMovies;
    printf("%d", movies_count);
    // Load reservation data from file.
    int reservationCount = 0;
    if(loadReservationFromFile(reserve, &reservationCount) != 0)
    {
        printf("\tThere are not previous reservations.\n");
    }
    reservation_count = reservationCount;

    // Step 1: Authentication
    int n, a;
    while (a != 4)
    {
        n = first_choice();
        switch(n) 
        {
            case 1:
                admin_login();
                a = 4;
                break;
            case 2:
                registerUser();
                a = 4;
                break;
            case 3:
                loginUser();
                a = 4;
                break;
            case 4:
                a = 4;
                break;
            default: 
                printf("INVALID INPUT\n");
                break;
        }
    }
    return 0;
}

// User login part
// Prashan Rai.

#include "login.c"

int admin_login()
{
    pattern();
    char username[10], password[10];
    printf("\tWELCOME TO ADMIN LOGIN PAGE\n\n");
    printf("\tEnter your username: \t");
    scanf("%s", username);
    printf("\n\tEnter your password: \t");
    scanf("%s", password);
    if ((strcmp(username, admin_username) == 0) && (strcmp(password, admin_password)) == 0)
    {
        printf("\n\tYou are logged in successfully!!!\n");
        pattern();
        admin_interface();
    }
    else {
        printf("\n\tIncorrect password and/or username.Please try again");
        pattern();
        admin_login();
    }
}

// For admin's side of things
#include "admin.c"

// For user's part of things
#include "user.c"

// For file handeling operations
#include "file-handeling.c"