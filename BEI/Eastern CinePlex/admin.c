//For admin part of things.
//Snehaa Completion part.

int admin_interface()
{
    pattern();
    printf("\tWelcome -- Abhishek--\n\t1) Edit movies and their details\n\t2) Edit price of the ticket\n\t3) View current shows\n\t4) View Reservation \n\t5) View Earnings \n\t6) Logout\n\t7) Exit\n");
    pattern();
    printf("Enter your choice : ");
    int a = 0, n;
    while (a != 7)
    {
        scanf("%d", &n);
        switch(n) 
        {
            case 1:
                edit_movies();
                a = 7;
                break;
            case 2:
                edit_price();
                a = 7;
                break;
            case 3: 
                view_current_shows();
                a = 7; 
                break;
            case 4:
                view_reservation();
                a = 7; 
                break;
            case 5:
                view_balance();
                a = 7;
                break;
            case 6:
                logout();
                a = 7; 
                break;
            case 7:
                a = 7;
                break;
            default: 
                printf("INVALID INPUT\n");
                break;
        }
    }
    return 0;
}
int edit_price()
{
    pattern();
    printf("\t\tEastern CinePlex\n\tEdit the price of the ticket\n\tThe current price of the ticket is %d", ticket_price);
    printf("\n\tEnter the new price of ticket: \t");
    int new_price;
    scanf("%d", &new_price);
    printf("\n\tAre you sure you want to change the price?(Y/N)?\t");
    char decision;
    scanf(" %c", &decision);
    if ((decision == 'Y') || (decision == 'y'))
    {
        ticket_price = new_price;
        printf("\n\tPrice changed successfully!!!");
        admin_interface();
    }
    else {
        admin_interface();
    }
}
int edit_movies()
{
    pattern();
    printf("\tEastern CinePlex\n\tThe current movies in listing are: \n");
    for (int i = 0; i < movies_count; i++)
    {
        printf("\t%d) %s\n", i + 1, film[i].name);
    }
    int n;
    pattern();
    printf("Enter the movie that you want to edit : ");
    scanf("%d", &n);
    if ((n) < 1 || (n) > MAX_MOVIES)
    {
        printf("We cannot show more than %d movies.", MAX_MOVIES);
        edit_movies();
    }
    printf("\tEnter the new movie that you want to broadcast\n");
    printf("\tName of the movie: \t");
    scanf(" %[^\n]s", film[n - 1].name);
    printf("\n\tStarting time: \t");
    scanf("%d", &film[n - 1].starting_time);
    printf("\n\tLength of the movie(in minutes): \t");
    scanf("%d", &film[n - 1].length);
    printf("\n\tBroadcasting date: \t");
    scanf("%d", &film[n - 1].screening_day);
    printf("\n\tBroadcasting month: \t");
    scanf("%s", film[n - 1].screening_month);
    printf("\n\tGenre: \t");
    scanf(" %[^\n]s", film[n - 1].genre);
    printf("\n\tDirectors: \t");
    scanf(" %[^\n]s", film[n - 1].director);
    printf("\tData taken successfully!!!");
    admin_interface();
    return 0;
}
int view_current_shows()
{
    pattern();
    printf("\tEastern CinePlex\n");
    printf("\tThe current shows in the listing are: \n");
    for (int i = 0; i < movies_count; i++)
    {
        printf("\t%d) %s: Length: %d(minutes)\n \t\tGenre: %s\n\t\tDirectors: %s\n\t\tScreening on: %d'th of %s\n",i+1, film[i].name, film[i].length, film[i].genre, film[i].director, film[i].screening_day, film[i].screening_month);
    }
    printf("\tDo you want to change the listing?(Y/N)\t");
    char change;
    scanf(" %c", &change);
    if ((change == 'y') || (change == 'Y'))
    {
        edit_movies();
        return 0;
    }
    admin_interface();
    return 0;
}
int logout(void)
{
    printf("\tLogging out!!!\n");
    main();
    return 0;
}
int view_reservation()
{
    pattern();
    printf("\tVIEW_RESERVATION\n\tCurrent Movies Are: \n");
    int i, n;
    for (i = 0; i < 5; i++)
    {
        printf("\t\t%d) %s\n", i+1, film[i].name);
    }
    printf("\t%d) LOGOUT\n\t", i+1);
    printf("%d) EXIT\n", i+2);
    pattern();
    printf("Enter your choice : ");
    scanf("%d", &n);
    if (n > 0 && n < (i + 1))
    {
        see_reservation(film[n-1].name);
        return 0;
    }
    else if (n == (i + 1))
    {
        logout();
        return 0;
    }
    else if(n == (i+2))
    {
        return 0;
    }
    else {
        view_reservation();
    }
}
int see_reservation(char movie[])
{
    if (reservation_count == 0)
    {
        printf("\t There are currently no reservation for %s\n", movie);
        view_reservation();
        return 0;
    }
    pattern();
    printf("VIEWING RESERVATION FOR --%s--\n", movie);
    for (int i = 0; i < reservation_count; i++)
    {
        if (strcmp(reserve[i].movies, movie) == 0)
        {
            printf("%d) %s has booked seat no. : \t", i+1, reserve[i].name);
            for (int j = 0; j < reserve[i].num_seats; j++ )
            {
                printf("%d \t", reserve[i].seats[j]);
            }
            printf("\n");
        }   
    }
    pattern();
    printf(("Press any key to exit...."));
    getch();
    admin_interface();
}
int view_balance()
{
    pattern();
    int total_balance = 0;
    for (int i = 0; i < reservation_count; i++)
    {
        total_balance = total_balance + reserve[i].balance;
    }
    printf("\t\tEastern CinePlex\n\tTotal balance is: \t NRS.%d\n", total_balance);
    printf("\tThe balance report:\n");
    for (int i = 0; i < reservation_count; i++)
    {
        printf("\t\t%d) NRS. %d from %s.\n", i+1, reserve[i].balance, reserve[i].movies);
    }
    pattern();
    printf(("Press any key to exit...."));
    getch();
    admin_interface();
}