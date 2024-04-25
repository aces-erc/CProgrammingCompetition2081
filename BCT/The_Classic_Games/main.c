#include "games/pacman.c"
#include "games/tictactoe.c"
#include "games/snake.c"
#include <stdio.h>
#include <stdlib.h>
#include "games/wordle.c"
// Function prototypes

int main()
{
    int choice;
    system("cls");
    // Display menu
    printf("Welcome to the Game Center!\n");
    printf("1. Pacman\n");
    printf("2. Tic Tac Toe\n");
    printf("3. Snake\n");
    printf("4. Wordle\n");
    printf("Please enter the number of the game you want to play: ");
    scanf("%d", &choice);

    // Perform action based on user choice
    system("cls");

    switch (choice)
    {
    case 1:
        pacman();
        break;
    case 2:
        tictactoe();
        break;
    case 3:
        snake();
        break;
    case 4:
        wordle();
        break;
    default:
        printf("Invalid choice. Please enter a number between 1 and 4.\n");
        break;
    }

    return 0;
}

