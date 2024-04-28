#include "./lib.c"
#define ROW 9
#define COL 9
#define EASY 1
#define MEDIUM 2
#define HARD 3
#define EMPTY_CELL_SELECTION_BG_COLOR DARK_BG_WHITE
#define COMMON_NUMBERS_SELECTION_BG_COLOR LIGHT_BG_GREEN
#define NON_EMPTY_CELL_SELECTED_BG_COLOR DARK_BG_YELLOW
typedef struct
{
    char name[40];
    char feedBack[200];
    int rating;
} FeedBack;
void drawBlock(int, int, int, int);
void drawGrid(int, int);
void initializeSudoku(int[9][9]);
int isSafe(int, int, int);
int generateSudoku(int, int);
void setQuestion(int Level);
void copyArray(int[][9], int[][9]);
void moveToCell(int, int);
void selectCell(int, int);
void keyboardHandler();
void handelInput();
void showLife();
void showHelp();
void intro();
void handleGameOver();
void handleWin();
void showLevel();
int isGameCompleted();
int YesNoBoxSelection(char text[], int x, int y, int width, int height, int boxColor, int selectedBgColor, int defaultSelectedBgColor, int textColor, char positiveOption[], char negativeOption[]);
void takeFeedBack();
void viewFeedBack();
int sudoku[9][9];
int sudokuquestion[9][9];
int sudokuQuestionCopy[9][9];
int selectedCell[9][2];
int selectedCellCount, totalFilledCellCount;
int selectedLevel = EASY;

const int cellWidth = 5, cellHeight = 3;
int current_row, current_col, prev_row, prev_col, gridWidth, gridHeight, temp, life = 3, isGameOver = FALSE, numberOfCellToBeFill;
int startX, startY;
int defaultBGColor = DARK_BG_BLACK, mainBorderLineColor = DARK_RED, defaultBorderLineColor = LIGHT_CYAN;
char ch;

int main()
{
    gridWidth = cellWidth * COL;
    gridHeight = cellHeight * ROW;
    startX = getScreenWidth() / 2 - gridWidth / 2;
    startY = getScreenHeight() / 2 - gridHeight / 2;
    intro();
    initializeSudoku(sudoku);
    generateSudoku(0, 0);
    copyArray(sudokuquestion, sudoku);
    clear(CLEAR_WHOLE_SCREEN_MOVE_CURSOR_TO_UPPER_LEFT);
    setTextColor(DARK_WHITE);
    showLevel();
    setTextBackground(DARK_BG_BLACK);
    setQuestion(selectedLevel);
    copyArray(sudokuQuestionCopy, sudokuquestion);
    drawGrid(startX, startY);
    showLife();
    print("\n");
    hideCursor();
    sudokuquestion[0][0] = 0;
    while (!isGameOver)
    {
        selectCell(current_row, current_col);
        keyboardHandler();
    }

    getch();

    return 0;
}
void initializeSudoku(int sudoku[9][9])
{
    int row, col, i, j, k;
    for (row = 0; row < ROW; row++)
    {
        for (col = 0; col < COL; col++)
        {
            sudoku[row][col] = 0;
        }
    }
}

int isSafe(int row, int col, int num)
{
    if (sudoku[row][col] != 0)
    {
        return FALSE;
    }
    int i, j, startRow, startCol;
    for (i = 0; i < ROW; i++)
    {
        if (sudoku[row][i] == num || sudoku[i][col] == num)
        {
            return FALSE;
        }
    }
    startRow = row - row % 3;
    startCol = col - col % 3;
    for (i = startRow; i < startRow + 3; i++)
    {
        for (j = startCol; j < startCol + 3; j++)
        {
            if (sudoku[i][j] == num)
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

int generateSudoku(int row, int col)

{
    int i, num;
    if (row == ROW - 1 && col == COL)
    {
        return TRUE;
    }
    if (col == COL)
    {
        row++;
        col = 0;
    }
    if (sudoku[row][col] != 0)
    {
        return generateSudoku(row, col + 1);
    }

    for (i = 1; i <= COL; i++)
    {
        num = randomNumber(1, 9);
        if (isSafe(row, col, num))
        {
            sudoku[row][col] = num;
            if (generateSudoku(row, col + 1))
            {
                return TRUE;
            }
            sudoku[row][col] = 0;
        }
    }
    return FALSE;
}

void drawBlock(int x, int y, int row, int col)
{
    if (col == 2 || col == 5 || row == 2 || row == 5)
    {
        setTextColor(mainBorderLineColor);
    }
    else
    {
        setTextColor(defaultBorderLineColor);
    }
    gotoxy(x, y);
    print("     ");
    if (col != 8)
    {
        if (col == 2 || col == 5)
        {
            print("|");
        }
        else
        {
            saveColor();
            setTextColor(defaultBorderLineColor);
            print("|");
            restoreColor();
        }
    }

    gotoxy(x, y + 1);
    saveColor();
    setTextColor(LIGHT_WHITE);
    if (sudokuquestion[row][col])
    {
        print("  %d  ", sudokuquestion[row][col]);
    }
    else
    {
        print("     ", sudokuquestion[row][col]);
    }
    restoreColor();
    if (col != 8)
    {
        if (col == 2 || col == 5)
        {

            print("|");
        }
        else
        {
            saveColor();
            setTextColor(defaultBorderLineColor);
            print("|");
            restoreColor();
        }
    }
    gotoxy(x, y + 2);
    if (row != 8)
    {
        saveColor();
        if (row == 2 || row == 5)
        {
            setTextColor(mainBorderLineColor);
            print("_____");
        }
        else
        {
            setTextColor(defaultBorderLineColor);
            print("_____");
        }
        restoreColor();
    }
    else
    {
        print("     ");
    }
    if (col != 8)
    {
        if (col == 2 || col == 5)
        {

            print("|");
        }
        else
        {
            saveColor();
            setTextColor(defaultBorderLineColor);
            print("|");
            restoreColor();
        }
    }
}

void drawGrid(int x, int y)
{
    int i, j;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {

            drawBlock(x + (cellWidth + 1) * j, y + i * 3, i, j);
        }
    }
}

void setQuestion(int level)
{
    int i, row, col, count, srow, scol, r, c;

    switch (level)
    {
    case EASY:
        numberOfCellToBeFill = 30;
        break;
    case MEDIUM:
        numberOfCellToBeFill = 40;
        break;
    case HARD:
        numberOfCellToBeFill = 45;
        break;

    default:
        break;
    }
    for (i = 1; i <= numberOfCellToBeFill; i++)
    {
        do
        {
            row = randomNumber(0, 8);
            col = randomNumber(0, 8);
            srow = row - row % 3;
            scol = col - col % 3;
            count = 0;
            for (r = srow; r < srow + 3; r++)
            {
                for (c = scol; c < scol + 3; c++)
                {
                    if (sudokuquestion[r][c] == 0)
                    {
                        count++;
                    }
                }
            }
        } while (sudokuquestion[row][col] == 0 && count <= ((ROW * COL) / numberOfCellToBeFill));
        sudokuquestion[row][col] = 0;
    }
}

void copyArray(int To[][9], int From[][9])
{
    int row, col;
    for (row = 0; row < ROW; row++)
    {
        for (col = 0; col < COL; col++)
        {
            To[row][col] = From[row][col];
        }
    }
}

void moveToCell(int row, int col)
{
    int posx, posy, offSetx = 1, offSety = 1;
    posx = startX + (cellWidth * col) + col + offSetx; // add extra col to maintain the cursor position because there is a single space between two cells
    posy = startY + (cellHeight * row) + offSety;
    gotoxy(posx, posy);
}
void selectCell(int row, int col)
{
    int i, j;
    setTextColor(DARK_WHITE);
    if (sudokuquestion[row][col] != 0)
    {
        selectedCellCount = 0;
        for (i = 0; i < ROW; i++)
        {
            for (j = 0; j < COL; j++)
            {
                if (sudokuquestion[row][col] == sudokuquestion[i][j])
                {
                    selectedCell[selectedCellCount][0] = i;
                    selectedCell[selectedCellCount][1] = j;
                    selectedCellCount++;
                    moveToCell(i, j);
                    setTextBackground(COMMON_NUMBERS_SELECTION_BG_COLOR);
                    print(" %d ", sudokuquestion[row][col]);
                    setTextBackground(defaultBGColor);
                }
                else
                {
                    moveToCell(i, j);
                    setTextBackground(defaultBGColor);
                    if (sudokuquestion[i][j])
                    {
                        print(" %d ", sudokuquestion[i][j]);
                    }
                    else
                    {

                        print("   ");
                    }
                }
            }
        }
        moveToCell(row, col);
        setTextBackground(NON_EMPTY_CELL_SELECTED_BG_COLOR);
        print(" %d ", sudokuquestion[row][col]);
        setTextBackground(defaultBGColor);
    }
    else
    {
        for (i = 0; i < selectedCellCount; i++)
        {
            moveToCell(selectedCell[i][0], selectedCell[i][1]);
            setTextBackground(defaultBGColor);
            print(" %d ", sudokuquestion[selectedCell[i][0]][selectedCell[i][1]]);
        }
        if (sudokuquestion[prev_row][prev_col] == 0)
        {
            saveCursorPosition();
            gotoxy(10, 1);
            restoreCursorPosition();
            moveToCell(prev_row, prev_col);
            setTextBackground(defaultBGColor);
            print("   ");
        }
        moveToCell(row, col);
        setTextBackground(EMPTY_CELL_SELECTION_BG_COLOR);
        print("   ");
        setTextBackground(defaultBGColor);
        handelInput();
    }
    prev_row = row;
    prev_col = col;
}

void keyboardHandler()
{
    ch = getch();
    switch (ch)
    {
    case ARROW_UP:
        if (current_row > 0)
        {
            current_row--;
        }
        else
        {
            current_row = ROW - 1;
        }
        break;
    case ARROW_DOWN:
        if (current_row < ROW - 1)
        {
            current_row++;
        }
        else
        {
            current_row = 0;
        }
        break;
    case ARROW_RIGHT:
        if (current_col < COL - 1)
        {
            current_col++;
        }
        else
        {
            if (current_row < ROW - 1)
            {
                current_row++;
                current_col = 0;
            }
            else
            {
                current_row = 0;
                current_col = 0;
            }
        }
        break;
    case ARROW_LEFT:
        if (current_col > 0)
        {
            current_col--;
        }
        else
        {
            if (current_row > 0)
            {
                current_row--;
                current_col = 8;
            }
            else
            {
                current_col = 8;
                current_row = 8;
            }
        }
        break;
    default:
        break;
    }
}

void handelInput()
{
    int digit;
    if (sudokuquestion[current_row][current_col] == 0)
    {
        if (ch > 48 && ch <= 57)
        {
            digit = 9 - (57 - ch);

            if (sudoku[current_row][current_col] == digit)
            {
                sudokuquestion[current_row][current_col] = digit;
                moveToCell(current_row, current_col);
                printf(" %d ", digit);
                selectCell(current_row, current_col);
                if (isGameCompleted())
                {
                    takeFeedBack();
                    setTextBackground(defaultBGColor);
                    handleWin();
                }
            }
            else
            {
                life--;
                saveColor();
                setTextColor(DARK_RED);
                moveToCell(current_row, current_col);
                print(" %d ", digit);
                popUpMessage(lerp(0, getScreenWidth(), 0.5), 1, "You have place wrong number!!", DARK_RED, 1000);
                Beep(1500, 200);
                moveToCell(current_row, current_col);
                saveBgColor();
                setTextBackground(EMPTY_CELL_SELECTION_BG_COLOR);
                print("   ");
                restoreBgColor();
                restoreColor();
                showLife();
                if (!life)
                {
                    takeFeedBack();
                    handleGameOver();
                }
            }
        }
    }
}

void showLife()
{
    saveCursorPosition();
    gotoxy(lerp(0, getScreenWidth(), 0.8), 2);
    saveColor();
    setTextColor(DARK_GREEN);
    print("Life: ");
    setTextColor(DARK_RED);
    print("%d", life);
    restoreColor();
    restoreCursorPosition();
}
void showHelp()
{

    // Print the help content
    char help[][200] = {
        "Sudoku is a number puzzle game consisting of a 9x9 grid divided into 3x3 subgrids (called regions).",
        "The objective is to fill the grid with digits so that each column, each row, and each of the nine 3x3 ",
        "subgrids contains all the digits from 1 to 9.",
    };
    setTextColor(DARK_WHITE);
    int startY = (int)lerp(0, getScreenHeight(), 0.3);
    saveColor();
    setTextColor(DARK_GREEN);
    gotoxy((int)lerp(0, getScreenWidth(), 0.46), startY);
    setFontVarient(FONT_WEIGHT_BOLD);
    print("About Sudoku");
    restoreColor();
    gotoxy((int)lerp(0, getScreenWidth(), 0.15), startY + 2);
    print("%s", help[0]);
    gotoxy((int)lerp(0, getScreenWidth(), 0.15), startY + 3);
    print("%s", help[1]);
    gotoxy((int)lerp(0, getScreenWidth(), 0.35), startY + 4);
    print("%s", help[2]);
    saveColor();
    setTextColor(DARK_GREEN);
    gotoxy((int)lerp(0, getScreenWidth(), 0.48), startY + 10);
    setFontVarient(FONT_WEIGHT_BOLD);
    print("Controls");
    restoreColor();
    gotoxy((int)lerp(0, getScreenWidth(), 0.42), startY + 12);
    print("Arrow keys - Move cursor");
    gotoxy((int)lerp(0, getScreenWidth(), 0.42), startY + 13);
    print("1-9 - Enter number in cell");

    // Print instructions on how to return to main menu
    setTextColor(DARK_CYAN);
    setFontVarient(FONT_FAMILY_ITALIC);
    gotoxy((int)lerp(0, getScreenWidth(), 0.4), getScreenHeight() - 3);
    print("Press any key to return to main menu...");
    getch();
    clear(CLEAR_WHOLE_SCREEN_MOVE_CURSOR_TO_UPPER_LEFT);
    setFontVarient(FONT_WEIGHT_DEFAULT);
    intro();
}

void intro()
{
    char option1[][50] = {
        "Play",
        "Help",
        "Feedbacks",
        "Exit"};
    char option2[][50] = {
        "Easy",
        "Medium",
        "Hard",
        "Back",
    };
    int option1_count = 4;
    int option_selected = 0;
    int leftSpacing = (int)lerp(0, getScreenWidth(), 0.5);
    int optionStartY = (int)lerp(0, getScreenHeight(), 0.5) - 3;
    srand(time(0));
    clear(CLEAR_WHOLE_SCREEN_MOVE_CURSOR_TO_UPPER_LEFT);
    setTextColor(DARK_YELLOW);
    write("SUDOKU", TRUE, (int)lerp(0, getScreenWidth(), 0.4), 1);
    saveCursorPosition();
    gotoxy(0, optionStartY);
    option_selected = showMenu(option1, option1_count, DARK_WHITE, DARK_WHITE, DARK_CYAN, leftSpacing);
    if (option_selected == 1)
    {
        restoreCursorPosition();
        clear(CLEAR_FROM_CURSOR_TO_END_OF_SCREEN);
        getCursorPos(&cursorX, &cursorY);
        setTextColor(DARK_RED);
        gotoxy((int)lerp(0, getScreenWidth(), 0.5), cursorY - 1);
        print("LEVELS:");
        restoreCursorPosition();
        option_selected = showMenu(option2, option1_count, DARK_WHITE, DARK_WHITE, DARK_GREEN, leftSpacing);
        if (option_selected == 1)
        {
            selectedLevel = EASY;
        }
        else if (option_selected == 2)
        {
            selectedLevel = MEDIUM;
        }
        else if (option_selected == 3)
        {
            selectedLevel = HARD;
        }
        else if (option_selected == 4)
        {
            intro();
        }
    }
    else if (option_selected == 2)
    {
        restoreCursorPosition();
        clear(CLEAR_FROM_CURSOR_TO_END_OF_SCREEN);
        showHelp();
    }
    else if (option_selected == 3)
    {

        restoreCursorPosition();
        clear(CLEAR_FROM_CURSOR_TO_END_OF_SCREEN);
        viewFeedBack();
        getch();
    }
    else if (option_selected == 4)
    {
        exit(0);
    }
}

void handleWin()
{
    int option_selected;
    clear(CLEAR_WHOLE_SCREEN_MOVE_CURSOR_TO_UPPER_LEFT);
    setTextColor(DARK_BLUE);
    write("CONGRATULATION", TRUE, (int)lerp(0, getScreenWidth(), 0.2), 1);
    write("YOU WON", TRUE, (int)lerp(0, getScreenWidth(), 0.36), 7);

    option_selected = YesNoBoxSelection("Do you want to play new game?", (int)lerp(0, getScreenWidth(), 0.5) - 20, (int)lerp(0, getScreenHeight(), 0.4), 40, 8, DARK_BG_CYAN, DARK_BG_GREEN, DARK_BG_RED, DARK_RED, "YES", "NO");
    if (option_selected == 1)
    {
        clear(CLEAR_WHOLE_SCREEN_MOVE_CURSOR_TO_UPPER_LEFT);
        initializeSudoku(sudoku);
        generateSudoku(0, 0);
        copyArray(sudokuquestion, sudoku);
        setQuestion(selectedLevel);
        life = 3;
        setTextBackground(DARK_BG_BLACK);
        drawGrid(startX, startY);
        showLife();
        showLevel();
        current_row = 0;
        current_col = 0;
        selectCell(current_row, current_col);
        isGameOver = FALSE;
    }
    else
    {
        exit(0);
    }
}

void handleGameOver()
{
    int option_selected;
    clear(CLEAR_WHOLE_SCREEN_MOVE_CURSOR_TO_UPPER_LEFT);
    setTextColor(DARK_RED); 
    setTextColor(DARK_WHITE);
    saveColor();
    saveCursorPosition();
    write("GAME OVER", TRUE, (int)lerp(0, getScreenWidth(), 0.32), 1);
    restoreCursorPosition();
    restoreColor();

    option_selected = YesNoBoxSelection("Do you want to play Again?", (int)lerp(0, getScreenWidth(), 0.5) - 20, (int)lerp(0, getScreenHeight(), 0.4), 40, 8, DARK_BG_CYAN, DARK_BG_GREEN, DARK_BG_RED, DARK_RED, "YES", "NO");

    if (option_selected == 1)
    {
        clear(CLEAR_WHOLE_SCREEN_MOVE_CURSOR_TO_UPPER_LEFT);
        copyArray(sudokuquestion, sudokuQuestionCopy);
        life = 3;
        setTextBackground(DARK_BG_BLACK);
        drawGrid(startX, startY);
        showLife();
        showLevel();
        current_row = 0;
        current_col = 0;
        selectCell(current_row, current_col);
        isGameOver = FALSE;
    }
    else
    {
        exit(0);
    }
}
int YesNoBoxSelection(char text[], int x, int y, int width, int height, int boxColor, int selectedBgColor, int defaultSelectedBgColor, int textColor, char positiveOption[], char negativeOption[])
{
    saveBgColor();
    saveColor();
    int i, j;
    int choice = 1;
    char ch;
    setTextBackground(boxColor);
    for (i = x; i <= x + width; i++)
    {
        for (j = y; j <= y + height; j++)
        {
            gotoxy(i, j);
            print(" ");
        }
    }

    setTextColor(textColor);
    gotoxy((int)lerp(x, x + width, 0.5) - strlen(text) / 2, (int)lerp(y, y + height, 0.2));
    setTextBackground(boxColor);
    print("%s", text);
    gotoxy((int)lerp(x, x + width, 0.2), (int)lerp(y, y + height, 0.8));
    setTextBackground(selectedBgColor);
    print(" %s ", negativeOption);
    setTextBackground(defaultSelectedBgColor);

    gotoxy((int)lerp(x, x + width, 0.7), (int)lerp(y, y + height, 0.8));
    print(" %s ", positiveOption);
    do
    {
        switch (ch)
        {
        case ARROW_RIGHT:
            if (choice == 0)
            {
                choice = 1;
                gotoxy((int)lerp(x, x + width, 0.2), (int)lerp(y, y + height, 0.8));
                setTextBackground(selectedBgColor);
                print(" %s ", negativeOption);

                setTextBackground(defaultSelectedBgColor);
                gotoxy((int)lerp(x, x + width, 0.7), (int)lerp(y, y + height, 0.8));
                print(" %s ", positiveOption);
            }
            break;
        case ARROW_LEFT:
            if (choice == 1)
            {
                choice = 0;
                gotoxy((int)lerp(x, x + width, 0.2), (int)lerp(y, y + height, 0.8));
                setTextBackground(defaultSelectedBgColor);
                print(" %s ", negativeOption);
                setTextBackground(selectedBgColor);

                gotoxy((int)lerp(x, x + width, 0.7), (int)lerp(y, y + height, 0.8));
                print(" %s ", positiveOption);
            }
            break;

        default:
            break;
        }

    } while ((ch = getch()) != '\r');
    restoreColor();
    restoreBgColor();
    return choice;
}
void showLevel()
{
    gotoxy(lerp(0, getScreenWidth(), 0.2), 2);
    setTextColor(DARK_GREEN);
    print("Level: ");
    setTextColor(DARK_MAGNETA);
    if (selectedLevel == EASY)
    {
        print("Easy");
    }
    else if (selectedLevel == MEDIUM)
    {
        print("Medium");
    }
    else
    {
        print("Hard");
    }
}

int isGameCompleted()
{
    int i, j;
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            if (sudokuquestion[i][j] == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void takeFeedBack()
{

    int option_selected;
    clear(CLEAR_WHOLE_SCREEN_MOVE_CURSOR_TO_UPPER_LEFT);
    restoreColor();

    if (!YesNoBoxSelection("Give your suggestion?", (int)lerp(0, getScreenWidth(), 0.5) - 20, (int)lerp(0, getScreenHeight(), 0.4), 40, 8, DARK_BG_CYAN, DARK_BG_GREEN, DARK_BG_RED, DARK_RED, "Give now", "Skip now "))
    {
        return;
    }

    FeedBack fb;
    clear(CLEAR_WHOLE_SCREEN_MOVE_CURSOR_TO_UPPER_LEFT);
    saveColor();
    saveBgColor();
    showCursor();
    setTextColor(DARK_RED);
    gotoxy((int)lerp(0, getScreenWidth(), 0.48), 1);
    print("FeedBack Section");
    gotoxy((int)lerp(0, getScreenWidth(), 0.3), (int)lerp(0, getScreenHeight(), 0.2));
    textTimerAnimation("Enter your full Name: ", DARK_BLUE, 100);
    gets(fb.name);
    gotoxy((int)lerp(0, getScreenWidth(), 0.3), (int)lerp(0, getScreenHeight(), 0.2) + 1);
    textTimerAnimation("Give Us FeedBack: ", DARK_BLUE, 100);
    gets(fb.feedBack);
    gotoxy((int)lerp(0, getScreenWidth(), 0.3), (int)lerp(0, getScreenHeight(), 0.2) + 2);
    textTimerAnimation("Rate Us (1-10): ", DARK_BLUE, 100);
    saveCursorPosition();
    while (!(fb.rating > 0 && fb.rating <= 10))
    {
        scanf("%d", &fb.rating);
        if (!(fb.rating > 0 && fb.rating <= 10))
        {
            gotoxy(getScreenWidth() / 2, getScreenHeight() / 2);
            setTextColor(DARK_RED);
            print("Invalid Input");
            Sleep(1000);
            deleteLine(CLEAR_THE_ENTIRE_LINE_CURSOR_POS_NOT_CHANGE);
            restoreCursorPosition();
            printf("                                    ");
            restoreCursorPosition();
        }
    }
    hideCursor();
    FILE *fp = fopen("feedback.txt", "a");
    if (fp == NULL)
    {
        fopen("feedback.txt", "w");
    }
    fwrite(&fb, sizeof(FeedBack), 1, fp);
    fclose(fp);
    restoreBgColor();
    restoreColor();
}

void viewFeedBack()
{
    FILE *fp = fopen("feedback.txt", "r");
    int y = 2, isFeedBackFound = FALSE;
    saveColor();
    if (fp == NULL)
    {
        fp = fopen("feedback.txt", "w");
        gotoxy(getScreenWidth() / 2 - 5, getScreenHeight() / 2);
        setTextColor(DARK_BLUE);
        print("Feedbacks not available.");
        setTextColor(DARK_CYAN);
        setFontVarient(FONT_FAMILY_ITALIC);
        gotoxy((int)lerp(0, getScreenWidth(), 0.4), getScreenHeight() - 3);
        print("Press any key to return to main menu...");
        setFontVarient(FONT_WEIGHT_DEFAULT);
        getch();
        restoreColor();
        intro();
    }
    FeedBack fb;
    while (fread(&fb, sizeof(FeedBack), 1, fp))
    {
        isFeedBackFound = TRUE;
        gotoxy((int)lerp(0, getScreenWidth(), 0.4), 5 + y);
        setTextColor(DARK_BLUE);
        print("Name: ");
        setTextColor(DARK_WHITE);
        print("%s", fb.name);
        gotoxy((int)lerp(0, getScreenWidth(), 0.4), 5 + y + 1);
        setTextColor(DARK_BLUE);
        print("Feedback: ");
        setTextColor(DARK_WHITE);
        print("%s", fb.feedBack);
        gotoxy((int)lerp(0, getScreenWidth(), 0.4), 5 + y + 2);
        setTextColor(DARK_BLUE);
        print("Rating: ");
        setTextColor(DARK_WHITE);
        print("%d", fb.rating);
        y += 4;
    }
    if (!isFeedBackFound)
    {
      gotoxy(getScreenWidth() / 2 - 5, getScreenHeight() / 2);
        setTextColor(DARK_BLUE);
        print("Feedbacks not available.");
    }
    setTextColor(DARK_CYAN);
    setFontVarient(FONT_FAMILY_ITALIC);
    gotoxy((int)lerp(0, getScreenWidth(), 0.4), getScreenHeight() - 3);
    print("Press any key to return to main menu...");
    setFontVarient(FONT_WEIGHT_DEFAULT);
    getch();
    intro();
    restoreColor();
    fclose(fp);
}