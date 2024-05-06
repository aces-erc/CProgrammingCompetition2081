#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Function to register a new player
void registerPlayer() {
    char username[20];
    char password[20];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    FILE *file = fopen("players.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);

    printf("Registration successful!\n");
}

// Function to check if the username and password match
int login(char *username, char *password) {
    FILE *file = fopen("players.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char user[20];
    char pass[20];

    while (fscanf(file, "%s %s", user, pass) != EOF) {
        if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
            fclose(file);
            return 1; // Login successful
        }
    }

    fclose(file);
    return 0; // Login failed
}

void printBoard(char board[]) {
    system("cls");

    printf("\n\n");
    printf("==== TIC TAC TOE ====\n\n");
    printf("   |   |   \n");
    printf(" %c | %c | %c \n", board[1], board[2], board[3]);
    printf("___|___|___\n");
    printf("   |   |   \n");
    printf(" %c | %c | %c \n", board[4], board[5], board[6]);
    printf("___|___|___\n");
    printf("   |   |   \n");
    printf(" %c | %c | %c \n", board[7], board[8], board[9]);
    printf("___|___|___\n");
    printf("\n\n");
}

int checkwin(char board[]) {
    if (board[1] == board[2] && board[2] == board[3]) return 1;
    if (board[1] == board[4] && board[4] == board[7]) return 1;
    if (board[7] == board[8] && board[8] == board[9]) return 1;
    if (board[3] == board[6] && board[6] == board[9]) return 1;
    if (board[1] == board[5] && board[5] == board[9]) return 1;
    if (board[3] == board[5] && board[5] == board[7]) return 1;
    if (board[2] == board[5] && board[5] == board[8]) return 1;
    if (board[4] == board[5] && board[5] == board[6]) return 1;

    int count = 0;
    for (int i = 1; i <= 9; i++) {
        if (board[i] == 'X' || board[i] == 'O') count++;
    }

    if (count == 9) return 0;

    return -1;
}

int main() {
    int choice;
    char username[20];
    char password[20];

    printf("1. Register\n");
    printf("2. Login\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            registerPlayer();
            break;

        case 2:
            printf("Enter username: ");
            scanf("%s", username);

            printf("Enter password: ");
            scanf("%s", password);

            if (login(username, password)) {
                printf("Login successful!\n");
                // Proceed to the game
                {
                    int player = 1, input, status = -1;
                    char board[] = {'0','1','2','3','4','5','6','7','8','9'};
                    printBoard(board);

                    while (status == -1) {
                        player = (player % 2 == 0) ? 2 : 1;
                        char mark = (player == 1) ? 'X' : 'O';
                        printf("Player %d, enter a number: ", player);
                        scanf("%d", &input);

                        if (input < 1 || input > 9 || board[input] == 'X' || board[input] == 'O') {
                            printf("Invalid input or position already taken.\n");
                            continue;
                        }

                        board[input] = mark;
                        printBoard(board);

                        int result = checkwin(board);

                        if (result == 1) {
                            printf("Player %d wins!\n", player);
                            break;
                        } else if (result == 0) {
                            printf("It's a draw!\n");
                            return 0;
                        }

                        player++;
                    }
                }
            } else {
                printf("Login failed. Invalid username or password.\n");
            }
            break;

        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
