/*
   General Tests:
   1.Given position is on the board or not.
   2.Starting and ending chess piece is own or others.
   3.Begining position is empty or not.

   Specific Tests:
   1.Rook move.
   2.Bishop move.
   3.Queen move.
   4.Pawn move.
   5.Knight move.
   6.King move.
   7.Check mate.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "positionCodeGenerator.c"

#define WHITE 0
#define BLACK 1
#define SUFFIX 1
#define PREFIX 0
#define UP -1
#define DOWN 1

int positionOnBoard(char[], char[]);
int ownPieceCheckerHelper(char[], char[], char);
int ownPieceChecker(char[], char[]);
int rookMove(char[], char[]);
int verticalHorizontalSearch(char, char, char);
void concat(char, char, char *);
int crossSearch(char, char, char);
int BishopMove(char[], char[]);
int pawnMove(char[], char[]);
int Is_Empty(char[]);
int knightMove(char[], char[]);
int kingMove(char[], char[]);
int upDownKingMove(char[], char, char[]);
int check(char[]);
int checkMate();

typedef struct positionData
{
    char position[5];
    char chessPiece[5];
    int codes;
} chessData;
chessData chess[33];
int cat;

int indicator, turn = 1, numberOfChessPiece = 32, flag, rooksCheck; 
char chessPieceSuffix, king[3];

int moveValidity(char moveFrom[], char moveTo[])
{
    int i, j;
    switch (1)
    {
    case 1:
        if (!positionOnBoard(moveFrom, moveTo))
        {
            return 0;
        }
    case 2:
        if (!ownPieceChecker(moveFrom, moveTo))
        {
            return 0;
        }

    case 3:
          if(checkMate())
          {
             printf("CHECK MATE");
            
             exit(0);
          }    

    case 4:
            if (chessPieceSuffix == '*')
            {
                if (kingMove(moveFrom, moveTo))
                {
                    if (!check(moveFrom))
                    {
                        for (i = 0; i < numberOfChessPiece; i++)
                        {
                            if (positionCodeGenetator(moveFrom) == chess[i].codes)
                            {
                                if (chess[i].chessPiece[SUFFIX] == '*')
                                {
                                    return 1;
                                }
                                else
                                {
                                    return 0;
                                }
                            }
                        }
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                if (!check(moveFrom))
                {
                    for (i = 0; i < numberOfChessPiece; i++)
                    {
                        if (positionCodeGenetator(moveFrom) == chess[i].codes)
                        {
                            if (chess[i].chessPiece[SUFFIX] == '*')
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }
                    }
                }
            }
        

    case 5:
        switch (chessPieceSuffix)
        {
        case 'R':
            if (rookMove(moveFrom, moveTo))
            {
                return 1;
            }
            else
            {
                return 0;
            }

        case 'B':
            if (BishopMove(moveFrom, moveTo))
            {
                return 1;
            }
            else
            {
                return 0;
            }

        case 'Q':
            // Queen move testing
            if (rookMove(moveFrom, moveTo) || BishopMove(moveFrom, moveTo))
            {
                return 1;
            }
            else
            {
                return 0;
            }

        case 'P':
            // Pawn move testing
            if (pawnMove(moveFrom, moveTo))
            {
                return 1;
            }
            else
            {
                return 0;
            }

        case 'K':
            if (knightMove(moveFrom, moveTo))
            {
                return 1;
            }
            else
            {
                return 0;
            }

        case '*':
            if (kingMove(moveFrom, moveTo))
            {
                if (!check(moveFrom))
                {
                    for (i = 0; i < numberOfChessPiece; i++)
                    {
                        if (positionCodeGenetator(moveFrom) == chess[i].codes)
                        {
                            if (chess[i].chessPiece[SUFFIX] == '*')
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }
                    }
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                return 0;
            }
        }

    case 6:
        return 1;
    }
}
int positionOnBoard(char moveFrom[], char moveTo[])
{
    int i, j, flag = 0;
    char ch = 'a', combine[3];
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            // Generating all the valid position.
            combine[0] = 'a' + i;
            combine[1] = 49 + j;
            combine[2] = '\0';
            if (!strcmp(moveFrom, combine))
            {
                flag++;
            }

            if (!strcmp(moveTo, combine))
            {
                flag++;
            }
        }
    }
    if (flag == 2)
        return 1;
    else
        return 0;
}

int ownPieceChecker(char moveFrom[], char moveTo[])
{
    // This function checks whether the chess piece is own or not with the help of onPiece() function.
    if (turn == WHITE)
    {
        return ownPieceCheckerHelper(moveFrom, moveTo, 'W');
    }
    else
    {
        return ownPieceCheckerHelper(moveFrom, moveTo, 'B');
    }
}
int ownPieceCheckerHelper(char moveFrom[], char moveTo[], char ch)
{
    // This function finds whether the chess piece to move is own or not.
    int code[2], i, j, index[2] = {0, 0};
    code[0] = positionCodeGenetator(moveFrom);
    code[1] = positionCodeGenetator(moveTo);
    for (j = 0; j < 2; j++)
    {
        for (i = 0; i < numberOfChessPiece; i++)
        {
            if (code[j] == chess[i].codes)
            {
                /*
                -> Index[0] stores the index of chess piece to move if present in the structure data loaded
                   form file Reload.txt. If there no data than it holds 0 as initialized in begining.
                -> index[1] stores the index of chess piece(if present) of final destination.
                   If not present in the file(no chess piece in final destination) than it holds 0;
                */
                index[j] = i;
                break;
            }
        }
    }
    /* -> Initial position of move should not be empty. If empty than that move will be invalid.
       -> index[0] is 0 means initial position is empty which should not be for valid move.
       -> First expression checks whether the chess piece to be moved is own or not.
          If own piece than move is valid.
       -> ch in first expression holds 'W' or 'B' as provided by calling function according to the turn of player.
    */

    // Checking begining position move validity.
    if ((chess[index[0]].chessPiece[0] == ch) && index[0] != 0)
    {
        // Finding the chess piece (like rook, knight,queen,etc.).
        chessPieceSuffix = chess[index[0]].chessPiece[1];

        /*
          -> Checking the destination move validity.
        */
        if ((chess[index[1]].chessPiece[0] != ch) || index[1] == 0)
        {
            return 1;
        }
        return 0;
    }
    else
    {
        return 0;
    }
}

int rookMove(char moveFrom[], char moveTo[])
{
    /*
        -> Function rookMove() restricts the rook move.
        -> It takes the initial and final position of move.
    */
    int i, j;
    char rookVerticalSteps[3], rookHorizontalSteps[3], checkPostition[3];
    for (i = 0; i < 8; i++)
    {

        concat(moveFrom[0], i + '1', rookVerticalSteps);
        concat('a' + i, moveFrom[1], rookHorizontalSteps);
        if ((positionCodeGenetator(moveTo) == positionCodeGenetator(rookVerticalSteps)) || (positionCodeGenetator(moveTo) == positionCodeGenetator(rookHorizontalSteps)))
        {
            if (moveFrom[PREFIX] == moveTo[PREFIX])
            {
                if (moveFrom[SUFFIX] < moveTo[SUFFIX])
                {
                    flag = 1;
                    return verticalHorizontalSearch(moveFrom[PREFIX], moveFrom[SUFFIX], moveTo[SUFFIX]);
                }
                else
                {
                    flag = 1;
                    return verticalHorizontalSearch(moveFrom[PREFIX], moveTo[SUFFIX], moveFrom[SUFFIX]);
                }
            }
            else
            {
                if (moveFrom[PREFIX] < moveTo[PREFIX])
                {
                    flag = 2;
                    return verticalHorizontalSearch(moveFrom[SUFFIX], moveFrom[PREFIX], moveTo[PREFIX]);
                }
                else
                {
                    flag = 2;
                    return verticalHorizontalSearch(moveFrom[SUFFIX], moveTo[PREFIX], moveFrom[PREFIX]);
                }
            }
        }
    }
    return 0;
}

void concat(char prifix, char suffix, char *str)
{
    *str = prifix;
    *(str + 1) = suffix;
    *(str + 2) = '\0';
}

int verticalHorizontalSearch(char moveFromPrefix, char moveFromSuffix, char moveTo)
{
    int i, j;
    char checkPostition[3];
    for (i = 1; i <= (moveTo - moveFromSuffix - 1); i++)
    {
        if (flag == 1)
        {
            concat(moveFromPrefix, moveFromSuffix + i, checkPostition);
        }
        else
        {

            concat(moveFromSuffix + i, moveFromPrefix, checkPostition);
        }
        for (j = 0; j < numberOfChessPiece; j++)
        {
            if (positionCodeGenetator(checkPostition) == chess[j].codes)
            {
                return 0;
            }
        }
    }
    return 1;
}

int BishopMove(char moveFrom[], char moveTo[])
{
    int i = 0, j;
    char suffix, prefix, upNegative[3], downNegative[3], upPositive[3], downPositive[3];

    prefix = moveFrom[PREFIX];
    suffix = moveFrom[SUFFIX];
    // upNegative[PREFIX] != 'a' || upNegative[SUFFIX] != '8' || downNegative[PREFIX] != 'h'
    while (1)
    {
        i++;
        concat(prefix - i, suffix + i, upNegative);
        concat(prefix + i, suffix - i, downNegative);
        concat(prefix + i, suffix + i, upPositive);
        concat(prefix - i, suffix - i, downPositive);
        if ((positionCodeGenetator(moveTo) == positionCodeGenetator(upNegative)) || (positionCodeGenetator(moveTo) == positionCodeGenetator(downNegative)) || (positionCodeGenetator(moveTo) == positionCodeGenetator(upPositive)) || (positionCodeGenetator(moveTo) == positionCodeGenetator(downPositive)))
        {
            if (moveFrom[PREFIX] < moveTo[PREFIX])
            {
                if (moveFrom[SUFFIX] < moveTo[SUFFIX])
                {
                    flag = 1;
                    return crossSearch(moveTo[PREFIX], moveFrom[PREFIX], moveFrom[SUFFIX]);
                }
                else
                {
                    flag = 2;
                    return crossSearch(moveTo[PREFIX], moveFrom[PREFIX], moveFrom[SUFFIX]);
                }
            }
            else
            {
                if (moveFrom[SUFFIX] > moveTo[SUFFIX])
                {
                    flag = 1;
                    return crossSearch(moveFrom[PREFIX], moveTo[PREFIX], moveTo[SUFFIX]);
                }
                else
                {
                    flag = 2;
                    return crossSearch(moveFrom[PREFIX], moveTo[PREFIX], moveTo[SUFFIX]);
                }
            }
        }
        if (i == 8)
        {
            return 0;
        }
    }
}

int crossSearch(char moveBiggerPrefix, char moveSmallerPrefix, char moveBiggerSmallerSuffix)
{
    int i, j;
    char upDown[3];
    for (i = 1; i < moveBiggerPrefix - moveSmallerPrefix; i++)
    {
        if (flag == 1)
        {
            concat(moveSmallerPrefix + i, moveBiggerSmallerSuffix + i, upDown);
        }
        else
        {
            concat(moveSmallerPrefix + i, moveBiggerSmallerSuffix - i, upDown);
        }

        for (j = 0; j < numberOfChessPiece; j++)
        {
            if (positionCodeGenetator(upDown) == chess[j].codes)
            {
                return 0;
            }
        }
    }
    return 1;
}

int pawnMove(char moveFrom[], char moveTo[])
{
    int destinationRow, beginingRow, i;

    // code is divided by 10000 to get row number.
    // e.g: if code is 31230 then number in ten thousand place represent row number.
    // i.e, row number in this case is 3(up to down) of chess board.
    beginingRow = positionCodeGenetator(moveFrom) / 10000;
    destinationRow = positionCodeGenetator(moveTo) / 10000;
    char middlePosition[3];

    if (moveFrom[PREFIX] == moveTo[PREFIX])
    {
        if (turn == WHITE)
        {

            if (beginingRow <= 7)
            {
                // checking that whether the move is one step forward or not.
                if (destinationRow == beginingRow - 1)
                {
                    return 1;
                }
                // checking whether the starting move is two step forward or not.
                else if ((beginingRow == 7) && (destinationRow == beginingRow - 2))
                {
                    // Finding the middle postion of move for pawn.
                    // Here, character 0 is added to intiger 6 to convert intiger 6 to '6' because concat() takes parameter onlt character.
                    concat(moveFrom[PREFIX], 3 + '0', middlePosition);
                    return Is_Empty(middlePosition);
                }
                else
                {
                    return 0;
                }
            }
        }
        else
        { // For black pawn.
            if (beginingRow >= 2)
            {
                // checking that whether the move is one step forward or not.
                if (destinationRow == beginingRow + 1)
                {
                    return 1;
                }
                // checking whether the starting move is two step forward or not.
                else if ((beginingRow == 2) && (destinationRow == beginingRow + 2))
                {
                    // Finding the middle postion of move for pawn.
                    concat(moveFrom[PREFIX], 6 + '0', middlePosition);
                    return Is_Empty(middlePosition);
                }
                else
                {
                    return 0;
                }
            }
        }
    }
    else if (moveTo[PREFIX] == moveFrom[PREFIX] + 1 || moveTo[PREFIX] == moveFrom[PREFIX] - 1)
    {
        if (destinationRow == beginingRow + 1 || destinationRow == beginingRow - 1)
        {
            if (turn == WHITE)
            {

                if ((destinationRow < beginingRow))
                {
                    return !(Is_Empty(moveTo));
                }
                else if ((destinationRow < beginingRow))
                {
                    return !(Is_Empty(moveTo));
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                if ((destinationRow > beginingRow))
                {
                    concat(moveFrom[PREFIX] + 1, moveFrom[SUFFIX] - 1, middlePosition);
                    return !(Is_Empty(moveTo));
                }
                else if ((destinationRow > beginingRow))
                {
                    return !(Is_Empty(moveTo));
                }
                else
                {
                    return 0;
                }
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
int Is_Empty(char middlePosition[])
{
    int i;
    for (i = 0; i < numberOfChessPiece; i++)
    {
        // Checking whether the middle position is empty or not.
        // If empty than return 1 otherwise return 0.
        if (positionCodeGenetator(middlePosition) == chess[i].codes)
        {
            return 0;
        }
    }
    return 1;
}

int knightMove(char moveFrom[], char moveTo[])
{
    if ((moveFrom[PREFIX] == moveTo[PREFIX] + 1) || (moveFrom[PREFIX] == moveTo[PREFIX] - 1))
    {
        if ((moveFrom[SUFFIX] == moveTo[SUFFIX] + 2) || (moveFrom[SUFFIX] == moveTo[SUFFIX] - 2))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if ((moveFrom[PREFIX] == moveTo[PREFIX] + 2) || (moveFrom[PREFIX] == moveTo[PREFIX] - 2))
    {
        if ((moveFrom[SUFFIX] == moveTo[SUFFIX] + 1) || (moveFrom[SUFFIX] == moveTo[SUFFIX] - 1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int kingMove(char moveFrom[], char moveTo[])
{
    int i, j;
    char pos[3], chesspiece[3];
    if ((moveFrom[PREFIX] == moveTo[PREFIX] + 1) || (moveFrom[PREFIX] == moveTo[PREFIX] - 1) || (moveFrom[PREFIX] == moveTo[PREFIX]))
    {
        if ((moveFrom[SUFFIX] == moveTo[SUFFIX] + 1) || (moveFrom[SUFFIX] == moveTo[SUFFIX] - 1) || (moveFrom[SUFFIX] == moveTo[SUFFIX]))
        {
            if (turn == WHITE)
            {
                if (!upDownKingMove(moveTo, 'B', "UP") || !upDownKingMove(moveTo, 'B', "DOWN") || !upDownKingMove(moveTo, 'B', "LEFT") || !upDownKingMove(moveTo, 'B', "RIGHT") || !upDownKingMove(moveTo, 'B', "RIGHT_UP") || !upDownKingMove(moveTo, 'B', "LEFT_UP") || !upDownKingMove(moveTo, 'B', "RIGHT_DOWN") || !upDownKingMove(moveTo, 'B', "LEFT_DOWN"))
                {
                    return 0;
                }
            }
            else
            {
                if (!upDownKingMove(moveTo, 'W', "UP") || !upDownKingMove(moveTo, 'W', "DOWN") || !upDownKingMove(moveTo, 'W', "LEFT") || !upDownKingMove(moveTo, 'W', "RIGHT") || !upDownKingMove(moveTo, 'W', "RIGHT_UP") || !upDownKingMove(moveTo, 'W', "LEFT_UP") || !upDownKingMove(moveTo, 'W', "RIGHT_DOWN") || !upDownKingMove(moveTo, 'W', "LEFT_DOWN"))
                {
                    return 0;
                }
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
    return 1;
}
int upDownKingMove(char moveTo[], char piece, char UpDown[])
{
    int i, j;
    char pos[3], chessPieceR[3], chessPieceQ[3], chessPieceB[3];
    for (i = 1; 1; i++)
    {
        if (!strcmp(UpDown, "UP"))
        {
            concat(moveTo[PREFIX], moveTo[SUFFIX] + i, pos);
        }
        else if (!strcmp(UpDown, "DOWN"))
        {
            concat(moveTo[PREFIX], moveTo[SUFFIX] - i, pos);
        }
        else if (!strcmp(UpDown, "LEFT"))
        {
            concat(moveTo[PREFIX] - i, moveTo[SUFFIX], pos);
        }
        else if (!strcmp(UpDown, "RIGHT"))
        {
            concat(moveTo[PREFIX] + i, moveTo[SUFFIX], pos);
        }
        else if (!strcmp(UpDown, "RIGHT_UP"))
        {
            concat(moveTo[PREFIX] + i, moveTo[SUFFIX] + i, pos);
        }
        else if (!strcmp(UpDown, "RIGHT_DOWN"))
        {
            concat(moveTo[PREFIX] + i, moveTo[SUFFIX] - i, pos);
        }
        else if (!strcmp(UpDown, "LEFT_UP"))
        {
            concat(moveTo[PREFIX] - i, moveTo[SUFFIX] + i, pos);
        }
        else if (!strcmp(UpDown, "LEFT_DOWN"))
        {
            concat(moveTo[PREFIX] - i, moveTo[SUFFIX] - i, pos);
        }

        for (j = 0; j < numberOfChessPiece; j++)
        {
            if (positionCodeGenetator(pos) == chess[j].codes)
            {
                concat(piece, 'R', chessPieceR);
                concat(piece, 'Q', chessPieceQ);
                concat(piece, 'B', chessPieceB);
                if (!strcmp(UpDown, "UP") || !strcmp(UpDown, "DOWN") || !strcmp(UpDown, "LEFT") || !strcmp(UpDown, "RIGHT"))
                {

                    if (strcmp(chess[j].chessPiece, chessPieceR) && strcmp(chess[j].chessPiece, chessPieceQ))
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    if (strcmp(chess[j].chessPiece, chessPieceQ) && strcmp(chess[j].chessPiece, chessPieceB))
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }
        if (i > 8)
        {
            return 1;
        }
    }
}

int check(char moveFrom[])
{

    int i, j;
    char Bposition[3] = {'\0'}, Wposition[3] = {'\0'};
    for (i = 0; i < numberOfChessPiece; i++)
    {
        for (j = 0; 1; j++)
        {
            if (!strcmp("B*", chess[j].chessPiece))
            {
                postitionCodeDecoder(chess[j].codes, Bposition);
                break;
            }
        }
        for (j = 0; 1; j++)
        {

            if (!strcmp("W*", chess[j].chessPiece))
            {
                postitionCodeDecoder(chess[j].codes, Wposition);
                break;
            }
        }

        if (turn == WHITE)
        {
            strcpy(king, Wposition);
            if (!upDownKingMove(Wposition, 'B', "UP") || !upDownKingMove(Wposition, 'B', "DOWN") || !upDownKingMove(Wposition, 'B', "LEFT") || !upDownKingMove(Wposition, 'B', "RIGHT") || !upDownKingMove(Wposition, 'B', "RIGHT_UP") || !upDownKingMove(Wposition, 'B', "LEFT_UP") || !upDownKingMove(Wposition, 'B', "RIGHT_DOWN") || !upDownKingMove(Wposition, 'B', "LEFT_DOWN"))
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            strcpy(king, Bposition);
            if (!upDownKingMove(Bposition, 'W', "UP") || !upDownKingMove(Bposition, 'W', "DOWN") || !upDownKingMove(Bposition, 'W', "LEFT") || !upDownKingMove(Bposition, 'W', "RIGHT") || !upDownKingMove(Bposition, 'W', "RIGHT_UP") || !upDownKingMove(Bposition, 'W', "LEFT_UP") || !upDownKingMove(Bposition, 'W', "RIGHT_DOWN") || !upDownKingMove(Bposition, 'W', "LEFT_DOWN"))
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
}

int checkMate()
{
    int i, j;
    char Bposition[3] = {'\0'}, Wposition[3] = {'\0'};
    for (i = 0; i < numberOfChessPiece; i++)
    {
        for (j = 0; 1; j++)
        {
            if (!strcmp("B*", chess[j].chessPiece))
            {
                postitionCodeDecoder(chess[j].codes, Bposition);
                break;
            }
        }
        for (j = 0; 1; j++)
        {

            if (!strcmp("W*", chess[j].chessPiece))
            {
                postitionCodeDecoder(chess[j].codes, Wposition);
                break;
            }
        }

        if (turn == WHITE)
        {
            strcpy(king, Wposition);
            if (!upDownKingMove(Wposition, 'B', "UP") && !upDownKingMove(Wposition, 'B', "DOWN") && !upDownKingMove(Wposition, 'B', "LEFT") && !upDownKingMove(Wposition, 'B', "RIGHT") && !upDownKingMove(Wposition, 'B', "RIGHT_UP") && !upDownKingMove(Wposition, 'B', "LEFT_UP") && !upDownKingMove(Wposition, 'B', "RIGHT_DOWN") && !upDownKingMove(Wposition, 'B', "LEFT_DOWN"))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            strcpy(king, Bposition);
            if (!upDownKingMove(Bposition, 'W', "UP") && !upDownKingMove(Bposition, 'W', "DOWN") && !upDownKingMove(Bposition, 'W', "LEFT") && !upDownKingMove(Bposition, 'W', "RIGHT") && !upDownKingMove(Bposition, 'W', "RIGHT_UP") && !upDownKingMove(Bposition, 'W', "LEFT_UP") && !upDownKingMove(Bposition, 'W', "RIGHT_DOWN") && !upDownKingMove(Bposition, 'W', "LEFT_DOWN"))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}