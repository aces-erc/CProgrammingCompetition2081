#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

struct User
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User users[MAX_USERS];
int userCount = 0;

void saveUsersToFile()
{
    FILE *file = fopen("users.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < userCount; i++)
    {
        fprintf(file, "\n%s %s", users[i].username, users[i].password);
    }

    fclose(file);
}

void loadUsersFromFile()
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("No existing users found.\n");
        return;
    }

    while (fscanf(file, "%s %s", users[userCount].username, users[userCount].password) == 2)
    {
        userCount++;
    }

    fclose(file);
}


int registerUser()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    pattern();
    printf("\tWELCOME TO REGISTRATION PAGE\n");
    printf("\tENTER USERNAME: ");
    scanf("%s", username);
    printf("\tENTER PASSWORD: ");
    scanf("%s", password);

    if (userCount >= MAX_USERS)
    {
        printf("\tCANNOT REGISTER MORE USERS.\n");
        main();
        return 0;
    }

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            printf("\tUSERNAME ALREADY EXISTS.PLEASE CHOOSE A DIFFERENT ONE.\n");
            main();
            return 0;
        }
    }

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;
    saveUsersToFile();
    printf("\tUSER REGISTERED SUCCESSFULLY.\n");
    main();
    return 1;
}

int loginUser()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    loadUsersFromFile();
    pattern();
    printf("\tWELCOME TO LOGIN PAGE\n");
    printf("\tENTER USERNAME: ");
    scanf("%s", username);
    printf("\tENTER PASSWORD: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            printf("\n\tLOGIN SUCCESSSFUL\n");
            user_interface(username);
            return 0;
        }
    }

    printf("\tINVALID USERNAME OR PASSWORD.\n");
    main();
    return 0;
}