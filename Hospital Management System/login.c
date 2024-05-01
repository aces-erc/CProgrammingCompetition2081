#include "login.h"

int login(pas p[]) {
    int i;
    char un[20], pass[20];
    homepage();
    printf("Enter your username:");
    scanf("%s", un);
    printf("Enter your password:");
    scanf("%s", pass);
    user = fopen("user.bin", "rb");
    if (user != NULL) {
        while (fread(&p[log_data], sizeof(pas), 1, user)) {
            if ((strcmp(p[log_data].username, un) == 0) && (strcmp(p[log_data].password, pass) == 0)) {
                printf("Congratulations, you are logged in!\n");
                getch();
                fclose(user);
                return 1;
            }
        }
        printf("Invalid username or password!\n");
    } else {
        printf("Error: Could not open file for reading.\n");
    }
    getch();
    return 0;
}

int create(pas p[]) {
    system("cls");
    printf("Enter your name:");
    scanf("%s", p[log_data].name);
    printf("Create your username:");
    scanf("%s", p[log_data].username);
    printf("Enter your email:");
    scanf("%s", p[log_data].email);
    printf("Enter your password:");
    scanf("%s", p[log_data].password);
    user = fopen("user.bin", "ab+");
    if (user != NULL) {
        fwrite(&p[log_data], sizeof(pas), 1, user);
        printf("Congratulations, Account Created!\n");
        fclose(user);
        log_data++;
        getch();
        return 1;
    } else {
        printf("Error: Could not open file for writing.\n");
    }
    getch();
    return 0;
}
