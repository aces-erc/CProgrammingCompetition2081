// For Dhiraj Bikram Rai and Abhishek Niraula
// User part of things
char username[30];

int user_interface(char name[])
{
    // Interface to select movies and about film hall price of ticket etc is accessible through here.
    pattern();
    strcpy(username, name);
    printf("\tWELCOME --%s--\n\tPLEASE SELECT...\n\t1)OUR AVAILABLE SHOWS\n\t2)INFO ABOUT OUR CINEPLEX \n\t3)LOGOUT\n \t4)EXIT", name);
    pattern();
    printf("Enter your choice : ");
    int n, a;
    while (a != 4)
    {
        scanf("%d", &n);
        switch(n) 
        {
            case 1:
                see_shows();
                a = 4;
                break;
            case 2:
                cineplex_info();
                a = 4;
                break;
            case 3:
                logout();
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
}

// See which shows are available in the movie hall and select a particular date
int see_shows(void)
{
    pattern();
    printf("\tPLEASE SELECT FROM THE AVALABLE SHOWS HERE\n");
    
    // Temporary array to store shows date : Given month is a constant, K represents the number of shows (distinct).
    int k = 0, temp[5];
    char temp2[5][8];

    // Code to filter out repeated dates from the shows in movie structure.
    for (int i = 0; i < movies_count; i++)
    {
        int counter = 0;
        for (int j = i+1; j < movies_count; j++)
        {
            if (film[i].screening_day == film[j].screening_day)
            {
                counter++;
            }
        }
        if (counter == 0)
        {
            // Storing the shows in temporary array
            temp[k] = film[i].screening_day;
            strcpy(temp2[k], film[i].screening_month);
            k++;
        }
    }
    for (int i = 0; i < k; i++)
    {
        printf("\t%d)  %d'th of %s\n",i + 1,temp[i], temp2[i]);
    }
    printf("\t%d)  Return to User Interface\n", k+1);
    printf("\t%d)  Exit\n", k+2);
    pattern();
    printf("Enter your choice : ");
    int n;
    // An infinite loop that runs until the user selects valid shows or opts to exit.
    while (true)
    {
        scanf("%d", &n);
        if (n > 0 && n <= (k + 1))
        {
            break;
        }
        else 
        {
            printf("\tINVALID SHOW. PLEASE RE-ENTER VALID SHOW.\n");
            continue;
        }
    }
    // Mimicing the function of 
    if (n < (k+1))
    {
        see_movies(temp[n-1], temp2[n-1]);
    }
    else if ( n == (k+1))
    {
        printf("\tReturning to user Interface!!!");
        user_interface(username);
    }
    else {
        return 0;
    }
    return 0;
}
int see_movies(int day, char month[])
{
    pattern();
    printf("\tSHOW:  %d'th of %s\n\tPLEASE SELECT AVAILABLE MOVIES..\n", day, month);
    char movie[5][30];
    int k = 0; 
    for (int i = 0; i < movies_count; i++)
    {
        // If the date is equal to the date selected by the user return that movie name
        if (film[i].screening_day == day && strcmp(month, film[i].screening_month) == 0)
        {
            int a = film[i].length/60;
            int b = film[i].length - a * 60;

            int ending_time = film[i].starting_time + a;
            if (b == 0 ) 
            {
                k++;
                printf("\t%d)  %s: FROM %dPM to %dPM\n", k, film[i].name, film[i].starting_time, ending_time);
                printf("\t\tDirected By: %s\n\t\tGenre: %s\n", film[i].director, film[i].genre);
                strcpy(movie[k-1], film[i].name);
                
            }
            else {
                k++;
                printf("\t%d)  %s: FROM %dPM to %d:%dPM\n", k, film[i].name, film[i].starting_time, ending_time,b);
                printf("\t\tDirected By: %s\n\t\tGenre: %s\n", film[i].director, film[i].genre);
                strcpy(movie[k-1], film[i].name);
            }
        }
    }
    printf("\t%d)  Return to User Interface\n", k+1);
    printf("\t%d)  Exit\n", k+2);
    pattern();
    printf("Enter your choice : ");
    // An infinite loop that runs until the user selects valid shows or opts to exit.
    int n;
    while (true)
    {
        scanf("%d", &n);
        if (n > 0 && n <= (k + 2))
        {
            break;
        }
        else 
        {
            printf("\tINVALID CHOICE.\n");
            continue;
        }
    }
    // Mimicing the function of calling function withing certain limit if exceeds exits the function.
    if (n < (k+1))
    {
        book_seats(movie[n-1]);
    }
    else if (n == (k + 1))
    {
        printf("\tReturning to user Interface!!!");
        user_interface(username);
    }
    else {
        return 0;
    }
    return 0;
}
int display_seats(int seats[], int num_seats)
{
    printf("\n\n\t\tAvailable Seats:\n\n");
    for (int i = 0; i < num_seats; i++)
    {
        if(seats[i] == 0)
        {
            printf("%d\t", i + 1);
        }
        else {
            printf("*\t");
        }
        if ( (i+1) % 10 == 0)
        {
            printf("\n");
        }
    }
}
int book_seats(char name[])
{
    pattern();
    int film_index;
    for (int i = 0; i < movies_count; i++)
    {
        if (strcmp(name, film[i].name) == 0)
        {
            printf("\t%s\n\tDirected By: %s\n\tGenre: %s", film[i].name, film[i].director, film[i].genre);
            film_index = i;
        }
    }
    printf("\nThe current price of the ticket is:  %d", ticket_price);
    display_seats(film[film_index].seats, film[film_index].num_seats);
    pattern();

    int numTickets;
    printf("Enter the number of tickets: ");
    scanf("%d", &numTickets);

    if (numTickets < 1 || numTickets > film[film_index].num_seats) {
        printf("Invalid number of tickets.\n");
        user_interface(username);
        return 1;
    }
    printf("Are you sure you want to purchase tickets?(Y/N)\n");
    char change;
    scanf(" %c", &change);
    if ((change != 'y') && (change != 'Y'))
    {
        printf("Quitting!!!\n");
        user_interface(username);
        return 0;
    }
    printf("Enter the seat numbers:\n");    
    for (int i = 0; i < numTickets; i++) {
        int seat;
        scanf("%d", &seat);

        if (seat < 1 || seat > film[film_index].num_seats || film[film_index].seats[seat - 1] == 1) {
            printf("\tInvalid seat number or already booked.\n");
            book_seats(name);
            return 1;
        }

        film[film_index].seats[seat - 1] = 1;
        reserve[reservation_count].seats[i] = seat;
    } 
    strcpy(reserve[reservation_count].movies,film[film_index].name);
    strcpy(reserve[reservation_count].name, username);
    reserve[reservation_count].num_seats = numTickets;
    reserve[reservation_count].balance = numTickets * ticket_price;
    reservation_count++;
    printf("\t\t\t\tEastern CinePlex\n\t\t\tLangali Chowk, Dharan\n\t\t\tFilm: %s\n\t\t\tYour total billed price (including taxes) will be: NRS.%d\n",film[film_index].name, numTickets * ticket_price);
    printf("\t\t\tTickets booked successfully -- %s!\n", username);
    
    // Saving booked seats info into the file "movies.txt".
    if (saveMoviesToFile(film, movies_count) != 0)
    {
        printf("Error saving movie data to file.\n");
    } 

    // Saving reservatio data into file "reserve.txt".
    if (saveReservationToFile(reserve, reservation_count) != 0)
    {
        printf("Error saving reservation data to file.\n");
    }
    user_interface(username);   
    return 0;
}
int cineplex_info(void)
{
    pattern();
    printf("\tQFX CINEPLEX DETAILS:\n");
    printf("\t- Location: Langali Chowk, Dharan\n");
    printf("\t- Seating Options: Recliner Seats\n");
    printf("\t- Ventilation: Centralized Air Conditioning\n");
    printf("\t- Sound Quality: Dolby Atmos Surround Sound\n");
    printf("\t- Cafe Features:\n");
    printf("\t  - Variety of snacks and beverages\n");
    printf("\t  - Comfortable seating area\n");
    printf("\t  - WiFi access\n");
    printf("\t- Timings: Open from 1:00 PM to 11:00 PM\n");
    printf("\n\tPRICES:\n");
    printf("\t  - Per Seat: NRS. %d\n", ticket_price);
    pattern();
    printf(("Press any key to exit...."));
    getch();
    user_interface(username);
    return 0;
}