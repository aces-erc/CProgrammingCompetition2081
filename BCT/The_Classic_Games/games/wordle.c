#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NUM_OF_WORDS 100

void cls() {
    system("clear || cls");
}

int processGuess(const char *theAnswer, const char *theGuess) {
    char clue[6] = "-----";
    int correctCount = 0;
    int wrongPositionCount = 0;
    bool answerFlags[5] = {false};

    for (int i = 0; i < 5; i++) {
        if (theGuess[i] == theAnswer[i]) {
            clue[i] = 'G';
            answerFlags[i] = true;
            correctCount++;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (clue[i] == '-') {
            for (int j = 0; j < 5; j++) {
                if (theGuess[i] == theAnswer[j] && !answerFlags[j]) {
                    clue[i] = 'Y';
                    answerFlags[j] = true;
                    wrongPositionCount++;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        if (clue[i] == 'G') {
            printf("\033[0;32m%c\033[0m", theGuess[i]); // Green
        } else if (clue[i] == 'Y') {
            printf("\033[0;34m%c\033[0m", theGuess[i]); // Blue
        } else {
            printf("\033[0;31m%c\033[0m", theGuess[i]); // Red
        }
    }
    printf("\n");

    if (correctCount == 5) {
        return 1; // Guessed correctly
    } else {
        return 0; // Incorrect guess
    }
}

void saveHighScore(const char *username, int highScore) {
    FILE *file = fopen("Score_wordle.txt", "a");
    if (file == NULL) {
        printf("Failed to open the score file.\n");
        return;
    }
    fprintf(file, "%s %d", username, highScore);
    fclose(file);
}

int loadHighScore(const char *username) {
    FILE *file = fopen("Score_wordle.txt", "r");
    if (file == NULL) {
        return 0; // No high score file found
    }
    char name[100];
    int score;
    while (fscanf(file, "%s %d", name, &score) != EOF) {
        if (strcmp(name, username) == 0) {
            fclose(file);
            return score;
        }
    }
    fclose(file);
    return 0; // Username not found
}
int wordle2() {
    cls();
    printf("Color Legend:\n");
    printf("\033[0;32mGreen\033[0m: Correct letter in correct position\n");
    printf("\033[0;34mBlue\033[0m: Correct letter in wrong position\n");
    printf("\033[0;31mRed\033[0m: Incorrect letter\n\n");

    char *wordsList[MAX_NUM_OF_WORDS];
    int wordCount = 0;
    char fiveLetterWord[6];

    FILE *wordsFile = fopen("words.txt", "r");
    if (wordsFile == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    while (fscanf(wordsFile, "%5s", fiveLetterWord) != EOF && wordCount < MAX_NUM_OF_WORDS) {
        wordsList[wordCount] = malloc(6 * sizeof(char));
        strcpy(wordsList[wordCount], fiveLetterWord);
        wordCount++;
    }
    fclose(wordsFile);

    srand(time(NULL));
    char *answer = wordsList[rand() % wordCount];

    int num_of_guesses = 0;
    int guessed_correctly = 0;
    char guess[6];

    while (num_of_guesses < 6 && !guessed_correctly) {
        printf("\nInput a 5 letter word and press enter: ");
        scanf("%5s", guess); // Limit input to 5 characters
        if (strlen(guess) != 5) {
            printf("Invalid input. Please enter a 5-letter word.\n");
            continue;
        }
        printf("\nYou guessed: ");

        guessed_correctly = processGuess(answer, guess);
        if (!guessed_correctly) {
            printf("Incorrect guess! Try again.\n");
        } else {
            printf("Congratulations! You guessed the correct word.\n");
        }

        num_of_guesses++;
    }

    if (!guessed_correctly) {
        printf("Sorry, you've used all your guesses. The correct word is %s\n", answer);
    }

    for (int i = 0; i < wordCount; i++) {
        free(wordsList[i]);
    }

    return 0;
}

void wordle(){
      char playAgain = 'y';
    while (playAgain == 'y' || playAgain == 'Y') {
        wordle2();
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain);
    }
    printf("Thanks for playing!\n");
}