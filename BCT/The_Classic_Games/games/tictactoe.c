#include <stdio.h>
#include <stdlib.h>

void printBOARD();
int checkWin();
void clearScreen(); // Declare clearScreen function

char BOARD[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void tictactoe()
{
    char p1[30], p2[30];
    printf("Enter first player name\n");
    scanf("%s", p1);
    printf("Enter second player name\n");
    scanf("%s", p2);
    int player = 1, input, status = -1, i;
    printBOARD();

    while (status == -1)
    {
        player = (player % 2 == 0) ? 2 : 1;
        if (player == 1)
        {
            printf("Enter a number for player 1 (%s)\n", p1);
        }
        else
        {

            printf("Enter a number for player 2 (%s)\n", p2);
        }
        scanf("%d", &input);
        char mark = (player == 1) ? 'X' : 'O';
        if (input < 1 || input > 9 || BOARD[input] == 'X' || BOARD[input] == 'O')
        {

            printf("Invalid Input\n");
            exit(0);
        }
        BOARD[input] = mark;
        printBOARD();
        int result = checkWin();
        if (result == 1)
        {
            printf("Congratulations, player %d won!\n", player);
            break;
        }
        else if (result == 0)
        {

            printf("DRAW\n");
            break;
        }

        player++;
    }
}

void printBOARD()
{
    clearScreen();
    printf("\033[1;31m\033[1m\n~~~~ WELCOME TO TIC TAC TOE ~~~~\n\n");

    // Top row
    printf("          \033[1;37m|\033[0m         \033[1;37m|\033[0m        \n");
    printf("    \033[1;33m%c\033[0m     \033[1;37m|\033[0m   \033[1;33m%c\033[0m     \033[1;37m|\033[0m   \033[1;33m%c\033[0m   \n", BOARD[1], BOARD[2], BOARD[3]);
    printf(" \033[1;37m_________\033[1;37m|\033[0m_________\033[1;37m|\033[0m________\n");

    // Middle row
    printf("          \033[1;37m|\033[0m         \033[1;37m|\033[0m        \n");
    printf("    \033[1;33m%c\033[0m     \033[1;37m|\033[0m   \033[1;33m%c\033[0m     \033[1;37m|\033[0m   \033[1;33m%c\033[0m  \n", BOARD[4], BOARD[5], BOARD[6]);
    printf(" \033[1;37m_________\033[1;37m|\033[0m_________\033[1;37m|\033[0m________\n");

    // Bottom row
    printf("          \033[1;37m|\033[0m         \033[1;37m|\033[0m        \n");
    printf("    \033[1;33m%c\033[0m     \033[1;37m|\033[0m   \033[1;33m%c\033[0m     \033[1;37m|\033[0m   \033[1;33m%c\033[0m  \n", BOARD[7], BOARD[8], BOARD[9]);
    printf("          \033[1;37m|\033[0m         \033[1;37m|\033[0m        \n\n");
}

int checkWin()
{
    if (BOARD[1] == BOARD[2] && BOARD[2] == BOARD[3])
    {
        return 1;
    }
    if (BOARD[4] == BOARD[5] && BOARD[5] == BOARD[6])
    {
        return 1;
    }
    if (BOARD[7] == BOARD[8] && BOARD[8] == BOARD[9])
    {
        return 1;
    }
    if (BOARD[1] == BOARD[4] && BOARD[4] == BOARD[7])
    {
        return 1;
    }
    if (BOARD[2] == BOARD[5] && BOARD[5] == BOARD[8])
    {
        return 1;
    }
    if (BOARD[3] == BOARD[6] && BOARD[6] == BOARD[9])
    {
        return 1;
    }
    if (BOARD[1] == BOARD[5] && BOARD[5] == BOARD[9])
    {
        return 1;
    }
    if (BOARD[3] == BOARD[5] && BOARD[5] == BOARD[7])
    {
        return 1;
    }
    int count = 0;
    for (int i = 1; i <= 9; i++)
    {
        if (BOARD[i] == 'X' || BOARD[i] == 'O')
        {
            count++;
        }
    }
    if (count == 9)
        return 0;

    return -1;
}

void clearScreen()
{
    system("cls");
}