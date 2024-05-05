// #include <stdio.h>
#include "moveValidity.c"
void input(char[]);
int verifyPosition(int code);
void moveUpdate(int, int);
void dataReLoading();
int initialPositionCode, finialPositionCode, destination_Index = -1;

void input(char position[])
{
    // Taking the move of player.
    char moveFrom[30], moveTo[30], str[20];
    int i, j, k;
    for (i = 0; i < 2; i++)
    {
        // Finding initial and final move.
        moveFrom[i] = position[i];
        moveTo[i] = position[i + 2];
    }
    moveFrom[i] = '\0';
    moveTo[i] = '\0';
    // moveValidity(moveFrom,moveTo) return 1 if the move is valid otherwise return 0.
    indicator = moveValidity(moveFrom,moveTo);
    if (indicator) 
    {
        initialPositionCode = positionCodeGenetator(moveFrom); // passing initial move to genetate the position code.
        finialPositionCode = positionCodeGenetator(moveTo);    // passing final move to genetate the position code.
        moveUpdate(initialPositionCode, finialPositionCode);
    }
}



int verifyPosition(int code)
{
    // This function checks that whether the current position is matching with 64 block position or not.
    //  If mathches it return 1 otherwise return 0.
    int i, j;
    char ch = 'a', combine[3];
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            combine[0] = 'a' + i;
            combine[1] = 49 + j;
            combine[2] = '\0';
            if (code == positionCodeGenetator(combine))
            {
                return 1;
            }
            if (i == 7 && j == 7)
            {
                return 0;
            }
        }
    }
}

void moveUpdate(int begining, int destination)
{
    int i, index;
    for (i = 0; i < numberOfChessPiece; i++)
    {
        if (begining == chess[i].codes)
        {
            index = i;
        }
        if (destination == chess[i].codes)
        {
            destination_Index = i;
        }
    }
    chess[index].codes = destination;
}
void dataReLoading()
{
    FILE *reloaded_data;
    int i,totalNumberOfChessPiece;
    totalNumberOfChessPiece = numberOfChessPiece;
    reloaded_data = fopen("Reload.txt", "w");
    for (i = 0; i < totalNumberOfChessPiece; i++)
    {
        if (i == destination_Index)
        {
            numberOfChessPiece--;
            continue;
        }
        fprintf(reloaded_data, "%d %s\n", chess[i].codes, chess[i].chessPiece);
    }
    fclose(reloaded_data);

    reloaded_data = fopen("Reload.txt", "r");
    for (i = 0; i < numberOfChessPiece; i++)
    {
        fscanf(reloaded_data, "%d %s\n", &chess[i].codes, chess[i].chessPiece);
    }
    fclose(reloaded_data);
}