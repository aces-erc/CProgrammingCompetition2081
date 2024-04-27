
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
/**
 * @brief Clears the console screen or parts of it.
 *
 * @param console_clear_type Type of clearing operation:
 *      - CLEAR_FROM_CURSOR_TO_END_OF_SCREEN: Clear from cursor to end of screen.
 *      - CLEAR_FROM_CURSOR_TO_BEGINING_OF_SCREEN: Clear from cursor to beginning of screen.
 *      - CLEAR_WHOLE_SCREEN_MOVE_CURSOR_TO_UPPER_LEFT: Clear whole screen and move cursor to upper left.
 *      - CLEAR_WHOLE_SCREEN_DELETE_ALL_LINES_SAVED_IN_SCROOLBACK_BUFFER: Clear whole screen and delete all lines saved in scrollback buffer.
 */
void clear(int console_clear_type);

/**
 * @brief Hides the console cursor.
 */
void hideCursor();

/**
 * @brief Shows the console cursor.
 */
void showCursor();

/**
 * @brief Moves the console cursor to the right by the specified number of characters.
 *
 * @param byHowManyCharacters Number of characters to move the cursor.
 */
void moveCursorRight(int byHowManyCharacters);

/**
 * @brief Moves the console cursor to the left by the specified number of characters.
 *
 * @param byHowManyCharacters Number of characters to move the cursor.
 */
void moveCursorLeft(int byHowManyCharacters);

/**
 * @brief Moves the console cursor down by the specified number of lines.
 *
 * @param byHowManyLines Number of lines to move the cursor.
 */
void moveCursorDown(int byHowManyLines);

/**
 * @brief Moves the console cursor up by the specified number of lines.
 *
 * @param byHowManyLines Number of lines to move the cursor.
 */
void moveCursorUp(int byHowManyLines);

/**
 * @brief Moves the console cursor to the specified position.
 *
 * @param x X-coordinate of the cursor.
 * @param y Y-coordinate of the cursor.
 */
void gotoxy(int x, int y);

/**
 * @brief Gets the current position of the console cursor.
 *
 * @param x Pointer to store the X-coordinate.
 * @param y Pointer to store the Y-coordinate.
 */
void getCursorPos(int *x, int *y);

/**
 * @brief Gets the width of the console screen.
 *
 * @return Width of the console screen.
 */
int getScreenWidth();

/**
 * @brief Gets the height of the console screen.
 *
 * @return Height of the console screen.
 */
int getScreenHeight();

/**
 * @brief Linearly interpolates between two values.
 *
 * @param s Start value.
 * @param e End value.
 * @param p Interpolation parameter.
 * @return Interpolated value.
 */
float lerp(float s, float e, float p);

/**
 * @brief Draws a horizontal line on the console screen.
 *
 * @param start Starting position of the line.
 * @param end Ending position of the line.
 * @param cy Y-coordinate of the line.
 * @param color Color code of the line.
 */
/**
 * @brief Prints formatted text to the console screen.
 *
 * @param format Format string.
 * @param ... Optional arguments.
 */
void print(const char *format, ...);

/**
 * @brief Deletes a line from the console screen.
 *
 * @param deleteType Type of deletion operation:
 *      - CLEAR_FROM_CURSOR_TO_END_OF_LINE: Clear from cursor to end of line.
 *      - CLEAR_FROM_CURSOR_TO_BEGINING_OF_LINE: Clear from cursor to beginning of line.
 *      - CLEAR_THE_ENTIRE_LINE_CURSOR_POS_NOT_CHANGE: Clear the entire line without changing cursor position.
 */
void deleteLine(int deleteType);

/**
 * @brief Sets the text color on the console screen.
 *
 * @param color Color code for text.
 */
void setTextColor(int color);

/**
 * @brief Sets the background color for text on the console screen.
 *
 * @param color Color code for background.
 */
void setTextBackground(int color);

/**
 * @brief Sets the font variant for text on the console screen.
 *
 * @param style Style of the font.
 */
void setFontVarient(int style);

/**
 * @brief Generates a random floating-point number between 0 and 1.
 *
 * @return Random floating-point number.
 */
double random();
/**
 * @brief Generates a random integer between the specified range.
 *
 * @param min Minimum value.
 * @param max Maximum value.
 * @return Random integer.
 */
int randomNumber(int min, int max);
void saveCursorPosition();
void restoreCursorPosition();
void popUpMessage(int x, int y, char message[], int color, int _delay);
void saveColor();
void restoreColor();
int showMenu(char option[][50], int totalOptions, int serialNumberColor, int unSelectedOptionColor, int selectedOptionColor, int leftSpacing);
void saveBgColor();
void restoreBgColor();
void textTimerAnimation(char text[], int color, int delay);

typedef enum
{
    ARROW_UP = 72,
    ARROW_DOWN = 80,
    ARROW_LEFT = 75,
    ARROW_RIGHT = 77,
    _DELETE = 83,
    ENTER = 13,
} KEYBOARD;
typedef enum
{

    CLEAR_FROM_CURSOR_TO_END_OF_SCREEN = 0,
    CLEAR_FROM_CURSOR_TO_BEGINING_OF_SCREEN = 1,
    CLEAR_WHOLE_SCREEN_MOVE_CURSOR_TO_UPPER_LEFT = 2,
    CLEAR_WHOLE_SCREEN_DELETE_ALL_LINES_SAVED_IN_SCROOLBACK_BUFFER = 3

} CONSOLE_CLEAR_TYPE;
typedef enum
{
    CLEAR_FROM_CURSOR_TO_END_OF_LINE = 0,
    CLEAR_FROM_CURSOR_TO_BEGINING_OF_LINE = 1,
    CLEAR_THE_ENTIRE_LINE_CURSOR_POS_NOT_CHANGE = 2,

} CLEAR_CONSOLE_LINE_TYPE;
typedef enum
{
    DARK_GRAY = 30,
    DARK_RED = 31,
    DARK_GREEN = 32,
    DARK_YELLOW = 33,
    DARK_BLUE = 34,
    DARK_MAGNETA = 35,
    DARK_CYAN = 36,
    DARK_WHITE = 37,

    LIGHT_GRAY = 30,
    LIGHT_RED = 91,
    LIGHT_GREEN = 92,
    LIGHT_YELLOW = 93,
    LIGHT_BLUE = 94,
    LIGHT_MAGNETA = 55,
    LIGHT_CYAN = 96,
    LIGHT_WHITE = 97,

    DEFAULT = 1,

    DARK_BG_BLACK = 40,
    DARK_BG_RED = 41,
    DARK_BG_GREEN = 42,
    DARK_BG_YELLOW = 43,
    DARK_BG_BLUE = 44,
    DARK_BG_MAGNETA = 45,
    DARK_BG_CYAN = 46,
    DARK_BG_WHITE = 47,

    LIGHT_BG_RED = 101,
    LIGHT_BG_GREEN = 102,
    LIGHT_BG_YELLOW = 103,
    LIGHT_BG_BLUE = 104,
    LIGHT_BG_MAGNETA = 105,
    LIGHT_BG_CYAN = 106,
    LIGHT_BG_WHITE = 107,

    FONT_FAMILY_ITALIC = 3,
    UNDERLINE = 4,
    DOUBLE_UNDERLINE = 21,
    FONT_WEIGHT_BOLD = 1,
    FONT_WEIGHT_LIGHT = 2,
    FONT_WEIGHT_DEFAULT = 0,

} CONSOLE_COLORS;
int CURRENT_FONT_VARIENT = DEFAULT;
int CURRENT_COLOR = DEFAULT;
int tempBgColorHolder = DEFAULT;
int CURRENT_TEXT_BACKGROUND = DEFAULT;
int TEMP;
int cursorX, cursorY;

void clear(int console_clear_type)
{
    printf("\033[%dJ", console_clear_type);
}
void deleteLine(int deleteType)
{
    printf("\033[%dK", deleteType);
}
void hideCursor()
{
    printf("\033[?25l");
}
void showCursor()
{
    printf("\033[?25h");
}
void moveCursorRight(int byHowManyCharacters)
{
    printf("\033[%dC", byHowManyCharacters);
}
void moveCursorLeft(int byHowManyCharacters)
{
    printf("\033[%dD", byHowManyCharacters);
}
void moveCursorDown(int byHowManyLines)
{
    printf("\033[%dB", byHowManyLines); 
}
void moveCursorUp(int byHowManyLines)
{
    printf("\033[%dA", byHowManyLines);
}
void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}
void getCursorPos(int *x, int *y)
{
    CONSOLE_SCREEN_BUFFER_INFO cbi;

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbi))
    {
        *x = cbi.dwCursorPosition.X;
        *y = cbi.dwCursorPosition.Y;
    }
    else
    {
        printf("Error getting cursor position: %d\n", GetLastError());
    }
}
int getScreenWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwSize.X;
}
int getScreenHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwSize.Y;
}
void saveCursorPosition()
{
    printf("\033[s");
}

void restoreCursorPosition()
{
    printf("\033[u");
}
float lerp(float s, float e, float p)
{
    return s + (e - s) * p;
}
void setTextColor(int color)
{
    CURRENT_COLOR = color;
}
void setTextBackground(int color)
{
    CURRENT_TEXT_BACKGROUND = color;
}

void setFontVarient(int style)
{
    CURRENT_FONT_VARIENT = style;
}

void print(const char *format, ...)
{
    printf("\033[%d;%d;%dm", CURRENT_FONT_VARIENT, CURRENT_COLOR, CURRENT_TEXT_BACKGROUND);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\033[0m");
}

void popUpMessage(int x, int y, char message[], int color, int _delay)
{
    saveCursorPosition();
    hideCursor();
    gotoxy(x - strlen(message) / 2, y);
    setTextColor(color);
    print("%s", message);
    Sleep(_delay);
    deleteLine(CLEAR_FROM_CURSOR_TO_BEGINING_OF_LINE);
    restoreCursorPosition();
}

void write(char name[], int random, int x, int y)
{
    char alphabets[27][6][6];
    int i, j, k;
    strcpy(alphabets[0][1], "  *  ");
    strcpy(alphabets[0][2], " * * ");
    strcpy(alphabets[0][3], "*****");
    strcpy(alphabets[0][4], "*   *");
    strcpy(alphabets[0][5], "*   *");

    strcpy(alphabets[1][1], "**** ");
    strcpy(alphabets[1][2], "*   *");
    strcpy(alphabets[1][3], "**** ");
    strcpy(alphabets[1][4], "*   *");
    strcpy(alphabets[1][5], "**** ");

    strcpy(alphabets[2][1], " *** ");
    strcpy(alphabets[2][2], "*    ");
    strcpy(alphabets[2][3], "*    ");
    strcpy(alphabets[2][4], "*    ");
    strcpy(alphabets[2][5], " *** ");

    strcpy(alphabets[3][1], "**** ");
    strcpy(alphabets[3][2], "*   *");
    strcpy(alphabets[3][3], "*   *");
    strcpy(alphabets[3][4], "*   *");
    strcpy(alphabets[3][5], "**** ");

    strcpy(alphabets[4][1], "*****");
    strcpy(alphabets[4][2], "*    ");
    strcpy(alphabets[4][3], "*****");
    strcpy(alphabets[4][4], "*    ");
    strcpy(alphabets[4][5], "*****");

    strcpy(alphabets[5][1], "*****");
    strcpy(alphabets[5][2], "*    ");
    strcpy(alphabets[5][3], "*****");
    strcpy(alphabets[5][4], "*    ");
    strcpy(alphabets[5][5], "*    ");

    strcpy(alphabets[6][1], " *** ");
    strcpy(alphabets[6][2], "*    ");
    strcpy(alphabets[6][3], "* ***");
    strcpy(alphabets[6][4], "*   *");
    strcpy(alphabets[6][5], " ****");

    strcpy(alphabets[7][1], "*   *");
    strcpy(alphabets[7][2], "*   *");
    strcpy(alphabets[7][3], "*****");
    strcpy(alphabets[7][4], "*   *");
    strcpy(alphabets[7][5], "*   *");

    strcpy(alphabets[8][1], "*****");
    strcpy(alphabets[8][2], "  *  ");
    strcpy(alphabets[8][3], "  *  ");
    strcpy(alphabets[8][4], "  *  ");
    strcpy(alphabets[8][5], "*****");

    strcpy(alphabets[9][1], "    *");
    strcpy(alphabets[9][2], "    *");
    strcpy(alphabets[9][3], "    *");
    strcpy(alphabets[9][4], "*   *");
    strcpy(alphabets[9][5], " *** ");

    strcpy(alphabets[10][1], "*   *");
    strcpy(alphabets[10][2], "*  * ");
    strcpy(alphabets[10][3], "**   ");
    strcpy(alphabets[10][4], "*  * ");
    strcpy(alphabets[10][5], "*   *");

    strcpy(alphabets[11][1], "*    ");
    strcpy(alphabets[11][2], "*    ");
    strcpy(alphabets[11][3], "*    ");
    strcpy(alphabets[11][4], "*    ");
    strcpy(alphabets[11][5], "*****");

    strcpy(alphabets[12][1], "*   *");
    strcpy(alphabets[12][2], "** **");
    strcpy(alphabets[12][3], "* * *");
    strcpy(alphabets[12][4], "*   *");
    strcpy(alphabets[12][5], "*   *");

    strcpy(alphabets[13][1], "*   *");
    strcpy(alphabets[13][2], "**  *");
    strcpy(alphabets[13][3], "* * *");
    strcpy(alphabets[13][4], "*  **");
    strcpy(alphabets[13][5], "*   *");

    strcpy(alphabets[14][1], " *** ");
    strcpy(alphabets[14][2], "*   *");
    strcpy(alphabets[14][3], "*   *");
    strcpy(alphabets[14][4], "*   *");
    strcpy(alphabets[14][5], " *** ");

    strcpy(alphabets[15][1], "**** ");
    strcpy(alphabets[15][2], "*   *");
    strcpy(alphabets[15][3], "**** ");
    strcpy(alphabets[15][4], "*    ");
    strcpy(alphabets[15][5], "*    ");

    strcpy(alphabets[16][1], " *** ");
    strcpy(alphabets[16][2], "*   *");
    strcpy(alphabets[16][3], "* * *");
    strcpy(alphabets[16][4], " * * ");
    strcpy(alphabets[16][5], "   *");

    strcpy(alphabets[17][1], "**** ");
    strcpy(alphabets[17][2], "*   *");
    strcpy(alphabets[17][3], "***  ");
    strcpy(alphabets[17][4], "*  * ");
    strcpy(alphabets[17][5], "*   *");

    strcpy(alphabets[18][1], " ****");
    strcpy(alphabets[18][2], "*    ");
    strcpy(alphabets[18][3], " *** ");
    strcpy(alphabets[18][4], "    *");
    strcpy(alphabets[18][5], "**** ");

    strcpy(alphabets[19][1], "*****");
    strcpy(alphabets[19][2], "  *  ");
    strcpy(alphabets[19][3], "  *  ");
    strcpy(alphabets[19][4], "  *  ");
    strcpy(alphabets[19][5], "  *  ");

    strcpy(alphabets[20][1], "*   *");
    strcpy(alphabets[20][2], "*   *");
    strcpy(alphabets[20][3], "*   *");
    strcpy(alphabets[20][4], "*   *");
    strcpy(alphabets[20][5], "*****");

    strcpy(alphabets[21][1], "*   *");
    strcpy(alphabets[21][2], "*   *");
    strcpy(alphabets[21][3], "*   *");
    strcpy(alphabets[21][4], " * * ");
    strcpy(alphabets[21][5], "  *  ");

    strcpy(alphabets[22][1], "*   *");
    strcpy(alphabets[22][2], "*   *");
    strcpy(alphabets[22][3], "* * *");
    strcpy(alphabets[22][4], "** **");
    strcpy(alphabets[22][5], " * * ");

    strcpy(alphabets[23][1], "*   *");
    strcpy(alphabets[23][2], " * * ");
    strcpy(alphabets[23][3], "  *  ");
    strcpy(alphabets[23][4], " * * ");
    strcpy(alphabets[23][5], "*   *");

    strcpy(alphabets[24][1], "*   *");
    strcpy(alphabets[24][2], " * * ");
    strcpy(alphabets[24][3], "  *  ");
    strcpy(alphabets[24][4], "  *  ");
    strcpy(alphabets[24][5], "  *  ");

    strcpy(alphabets[25][1], "****");
    strcpy(alphabets[25][2], "  * ");
    strcpy(alphabets[25][3], " *  ");
    strcpy(alphabets[25][4], "*   ");
    strcpy(alphabets[25][5], "****");
    strcpy(alphabets[26][1], " ");
    strcpy(alphabets[26][2], " ");
    strcpy(alphabets[26][3], " ");
    strcpy(alphabets[26][4], " ");
    strcpy(alphabets[26][5], " ");
    TEMP = CURRENT_COLOR;
    gotoxy(x, y);

    for (j = 1; j <= 5; j++)
    {
        k = 0;
        i = (int)(toupper(name[k])) - 65;
        if (i == -33) // TO HANDLE SPACE
        {
            i = 26;
        }
        while (i < 27)
        {
            if (random)
            {
                CURRENT_COLOR = randomNumber(31, 37);
                print("%s ", alphabets[i][j]);
            }
            else
            {
                print("%s ", alphabets[i][j]);
            }
            if (name[++k] == '\0')
            {
                break;
            }
            i = (int)(toupper(name[k])) - 65;
            if (i == -33) // TO HANDLE SPACE
            {
                i = 26;
            }
        }
        gotoxy(x, y + j);
    }
    CURRENT_COLOR = TEMP;
}

void saveColor()
{
    TEMP = CURRENT_COLOR;
}
void restoreColor()
{
    setTextColor(TEMP);
}
void saveBgColor()
{
    tempBgColorHolder = CURRENT_TEXT_BACKGROUND;
}

void restoreBgColor()
{
    setTextBackground(tempBgColorHolder);
}
double random()
{
    return (double)rand() / (RAND_MAX + 1.0);
}

int randomNumber(int min, int max)
{
    return (int)(random() * (max - min + 1) + min);
}
int showMenu(char option[][50], int totalOptions, int serialNumberColor, int unSelectedOptionColor, int selectedOptionColor, int leftSpacing)
{
    hideCursor();
    char ch;
    int choice = 0;
    saveCursorPosition();
    do
    {
        restoreCursorPosition();
        clear(CLEAR_FROM_CURSOR_TO_END_OF_SCREEN);
        switch (ch)
        {
        case ARROW_UP:
            if (choice > 0)
            {
                choice--;
            }
            else
            {
                choice = totalOptions - 1;
            }
            break;
        case ARROW_DOWN:
            if (choice < totalOptions - 1)
            {
                choice++;
            }
            else
            {
                choice = 0;
            }
            break;
        }
        for (int i = 0; i < totalOptions; i++)
        {
            setTextColor(serialNumberColor);
            moveCursorRight(leftSpacing);
            print("%d:", i + 1);
            if (i == choice)
            {
                setTextColor(selectedOptionColor);
                print("%s\n", option[i]);
            }
            else
            {
                setTextColor(unSelectedOptionColor);
                print("%s\n", option[i]);
            }
        }
    } while ((ch = getch()) != '\r');
    return choice + 1;
}

void textTimerAnimation(char text[], int color, int delay)
{
    int i;
    setTextColor(color);
    for (i = 0; i < strlen(text); i++)
    {
        print("%c", text[i]);
        Sleep(delay);
    }
}