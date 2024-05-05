#include <stdio.h>
#include "input.c"
void players();
void oddBoardRow();
void evenBoardRow();
void board();
void horizontal_line();
void board_Horizontal_LetterIndex();
int positionCode(int, int, int);
void dataFetching();
void setChessPiece(int, int, int);
#define num 8
char a[100][100][100];
int bnum = 8, passRowNumber, flag;

int dataNumber = 0;
typedef struct player_detail
{
    char playerName[40], choice;

} player_detail;

player_detail player[2];
int main()
{
    char moves[5];
    players();
    dataFetching(); // loading the chesspiece position in the structure.
    while (1)
    {
        system("cls");
        board();
        if (turn == 1)
        {
            if (flag == 0)
            {
                printf("\n White move (%s): ", player[0].playerName);
                turn--;
            }
            else
            {
                printf("\n White move (%s): ", player[1].playerName);
                turn--;
            }
        }
        else
        {
            if (flag == 1)
            {
                printf("\n Black move(%s): ", player[0].playerName);
                turn++;
            }
            else
            {
                printf("\n Black move(%s): ", player[1].playerName);
                turn++;
            }
        }
        gets(moves);
        strlwr(moves);// converting given input into lower case.
        input(moves); // Taking the move of players.
        if (indicator == 0)
        {
            if (turn == 0)
            {
                turn++;
            }
            else
            {
                turn--;
            }
            printf("\nInvalid move.");
            getch();
            continue;
        }
        dataReLoading();
    }
    return 0;
}

void players()
{
    char username1[30], username2[30], choice;
    printf("\t\t\t\t\t\t <<<<<<< WELCOM TO CHESS >>>>>>");
    printf("\nPlayer 1, Enter your name:  ");
    gets(player[0].playerName);

    printf("\nPlayer 2, Enter your name:  ");
    gets(player[1].playerName);
    system("cls");
    printf("\n\t\t\t\t\t\t\t  ");
    printf("Welcome %s and %s!\n", player[0].playerName, player[1].playerName);
    printf("\n");
label:
    printf("\n%s, Do you want to play as Black or White (B/W)?", player[0].playerName);
    scanf(" %c", &choice);
    // printf("\n\t\t\t\t\t\t");
    if (choice == 'B' || choice == 'b')
    {
        printf("\n%s plays as White and %s plays as Black", player[1].playerName, player[0].playerName);
        flag = 1;
    }
    else if (choice == 'W' || choice == 'w')
    {
        printf("\n%s plays as White and %s plays as Black", player[0].playerName, player[1].playerName);
        flag = 0;
    }
    else
    {
        printf("\nPlease, Enter either B/W or b/w");
        goto label;
    }

    printf("\nPress any key two times to continue.");
    getch();
}
void oddBoardRow()
{
    int i, j, k, left = 0, left1 = 0, x, y, z;
    char *address;

    for (i = 0; i < 3; i++) // i represents smallest horizontal row.
    {
        // Handeling board column number.
        if (i == 1)
        {
            printf("%d", bnum);
            bnum--;
        }
        else
        {
            printf("%c", 255);
        }
        printf("|");
        for (k = 0; k < 4; k++) // k represents white black pair.
        {
            for (j = 0; j < num; j++)
            {
                a[i][k][j] = 219;
                // a[1][0][3] = 'B';
                // address = &a[i][k][j];

                // setPosition(i, k, j, address);
                // left = 0;
                if (verifyPosition(positionCode(i, k, j)))
                {
                    x = i;
                    y = k;
                    z = j;
                    setChessPiece(i, k, j);
                    // printf("%s", "**");
                }
                else
                {
                    if (i == x && k == y && j == (z + 1))
                    {

                        continue;
                    }
                    printf("%c", a[i][k][j]);
                }
            }

            for (j = num; j < (num + 8); j++)
            {
                a[i][k][j] = 255;
                if (verifyPosition(positionCode(i, k, j)))
                {
                    x = i;
                    y = k;
                    z = j;
                    setChessPiece(i, k, j);
                }
                else
                {
                    if (i == x && k == y && j == (z + 1))
                    {

                        continue;
                    }
                    printf("%c", a[i][k][j]);
                }
            }
        }
        // if (j != 8)
        printf("|");
        printf("\n");
    }
}
void evenBoardRow()
{
    int i, j, k, x, y, z;
    for (i = 0; i < 3; i++)
    {
        if (i == 1)
        {
            printf("%d", bnum);
            bnum--;
        }
        else
        {
            printf("%c", 255);
        }

        printf("|");
        for (k = 0; k < 4; k++)
        {
            for (j = 0; j < num; j++)
            {
                a[i][k][j] = 255;
                if (verifyPosition(positionCode(i, k, j)))
                {
                    x = i;
                    y = k;
                    z = j;
                    setChessPiece(i, k, j);
                }
                else
                {
                    if (i == x && k == y && j == (z + 1))
                    {

                        continue;
                    }
                    printf("%c", a[i][k][j]);
                }
            }

            for (j = num; j < num + 8; j++)
            {
                a[i][k][j] = 219;
                if (verifyPosition(positionCode(i, k, j)))
                {
                    x = i;
                    y = k;
                    z = j;
                    setChessPiece(i, k, j);
                    // setposition
                }
                else
                {
                    if (i == x && k == y && j == (z + 1))
                    {
                        continue;
                    }
                    printf("%c", a[i][k][j]);
                }
            }
        }
        printf("|");
        printf("\n");
    }
}
void horizontal_line()
{
    int i;
    printf("%c", 255);
    for (i = 1; i <= 65; i++)
    {
        printf("-");
    }
    printf("\n");
}
void board()
{
    int i, a = 1;
    horizontal_line();
    for (i = 1; i <= 4; i++)
    {
        passRowNumber = a++;
        oddBoardRow();
        passRowNumber = a++;
        evenBoardRow();
    }
    bnum = 8;
    horizontal_line();
    board_Horizontal_LetterIndex();
}
void board_Horizontal_LetterIndex()
{
    // Horizontal lettering of board.
    int i, b = 0, letter = 65; // 65 is ther ASCII value of a.
    printf("%c%c", 255, 255);
    for (i = 0; i < 64; i++)
    {
        if (i == 3 + b)
        {
            printf("%c", letter);
            b += 8;
            letter++;
        }
        else
        {
            printf("%c", 255); // 255 is ASCII value of black.
        }
    }
}
int positionCode(int i, int k, int j)
{
    if (j > 9)
    {
        return ((((passRowNumber * 10000) + (i * 1000)) + (k * 100)) + j);
    }
    else
    {
        return ((((passRowNumber * 10000) + (i * 1000)) + (k * 100)) + j * 10);
    }
}
void dataFetching()
{
    char positions[5], chessPiece[5], again;
    int codes, flag = 2;
    FILE *data;
    data = fopen("data.txt", "r");
    if (data == NULL)
    {
        printf("File cannot be opened.");
        exit(1);
    }
    while (1)
    {
        if (feof(data))
        {
            break;
        }
        fscanf(data, "%s %d %s", chess[dataNumber].position, &chess[dataNumber].codes, chess[dataNumber].chessPiece);
        // printf("%s %d %s\n",c1.position,c1.codes,c1.gooti);
        dataNumber++;
        // flag--;
    }
    fclose(data);
}
void setChessPiece(int i, int k, int j)
{
    int x, update = -1;
    for (x = 0; x < numberOfChessPiece; x++)
    {
        if (positionCode(i, k, j) == chess[x].codes)
        {
            update = x;
            break;
        }
    }
    if (update == -1)
    {
        if ((passRowNumber % 2 != 0 && j == 11) || (passRowNumber % 2 == 0 && j == 3))
        {
            printf("%c%c", 255, 255); // 255 is ASCII value of black.
        }
        else
        {
            printf("%c%c", 219, 219); // 219 is ASCII value of white.
        }
    }
    else
    {
        printf("%s", chess[update].chessPiece);
    }
}