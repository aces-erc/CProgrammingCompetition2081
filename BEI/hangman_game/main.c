#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 60
#define MAX_WORD_LENGTH 20
#define MAX_ATTEMPTS 7

struct Player {
    char name[50];
    
};

char* pickRandomWord(char words[MAX_WORDS][MAX_WORD_LENGTH], int size) {
    int index = rand() % size;
    return words[index];
}

void displayHangman(int attempts) {
    switch (attempts) {
        case 1:
            printf("  __\n");
            printf(" |/   |\n");
            printf(" |    O\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            printf("|\n");
            break;

        case 2:
            printf("  __\n");
            printf(" |/   |\n");
            printf(" |    O\n");
            printf(" |    |\n");
            printf(" |\n");
            printf(" |\n");
            printf("|\n");
            break;

        case 3:
            printf("  __\n");
            printf(" |/   |\n");
            printf(" |    O\n");
            printf(" |   /|\n");
            printf(" |\n");
            printf(" |\n");
            printf("|\n");
            break;

        case 4:
            printf("  __\n");
            printf(" |/   |\n");
            printf(" |    O\n");
            printf(" |   /|\\\n");
            printf(" |\n");
            printf(" |\n");
            printf("|\n");
            break;

        case 5:
            printf("  __\n");
            printf(" |/   |\n");
            printf(" |    O\n");
            printf(" |   /|\\\n");
            printf(" |   / \n");
            printf(" |\n");
            printf("|\n");
            break;

        case 6:
            printf("  __\n");
            printf(" |/   |\n");
            printf(" |    O\n");
            printf(" |   /|\\\n");
            printf(" |   / \\\n");
            printf(" |\n");
            printf("|\n");
            break;

        case 7:
            printf("  __\n");
            printf(" |/   |\n");
            printf(" |    O\n");
            printf(" |   /|\\\n");
            printf(" |   / \\\n");
            printf(" |\n");
            printf("|\n");
            break;

        default:
            break;
    }
}

void savePlayer(struct Player player) {
    FILE *file = fopen("hangman_scores.txt", "w+");
    if (file != NULL) {
        fprintf(file, "%s\n", player.name);
        fclose(file);
    } else {
        printf("Error saving score.\n");
    }

}

int main() {
    char picked_word[MAX_WORD_LENGTH];
    char guess,confirm;
    int number_of_tries, match, len,select,n;
    char play_again;

    struct Player player;
    printf("Enter your name: ");
    fgets(player.name, sizeof(player.name), stdin);
    strtok(player.name, "\n");  // Remove newline character from fgets

    char words[MAX_WORDS][MAX_WORD_LENGTH] = {"games", "books", "rhododendron", "flags", "excellent", "humble", "apple", "orange", "grape", "elephant", "rainbow",
                                               "telescope", "mountain", "whisper", "chocolate", "keyboard", "universe", "pillow", "bicycle", "dragonfly", "sunshine",
                                               "adventure", "library", "notebook", "guitar", "fireworks", "waterfall", "compass", "strawberry", "symphony",
                                               "marshmallow", "telescope", "penguin", "sunshine", "envelope", "bicycle", "kangaroo", "whisper", "castle",
                                               "pineapple", "friendship", "cinnamon", "jellyfish", "lemonade", "umbrella", "chocolate", "galaxy", "butterfly",
                                               "dragon", "harmony", "moonlight", "adventure", "zebra", "lighthouse", "fireworks", "dolphin", "popcorn", "bubble"};

    srand(time(NULL));
    back:
    printf(" /$$   /$$                               /$$      /$$                     /$$\n");
    printf("| $$  | $$                              | $$$    /$$$                    | $$\n");
    printf("| $$  | $$  /$$$$$$  /$$$$$$$   /$$$$$$ | $$$$  /$$$$  /$$$$$$  /$$$$$$$ | $$\n");
    printf("| $$$$$$$$ |____  $$| $$__  $$ /$$__  $$| $$ $$/$$ $$ |____  $$| $$__  $$| $$\n");
    printf("| $$__  $$  /$$$$$$$| $$  \\ $$| $$  \\ $$| $$  $$$| $$  /$$$$$$$| $$  \\ $$|__/\n");
    printf("| $$  | $$ /$$__  $$| $$  | $$| $$  | $$| $$\\  $ | $$ /$$__  $$| $$  | $$    \n");
    printf("| $$  | $$|  $$$$$$$| $$  | $$|  $$$$$$$| $$ \\/  | $$|  $$$$$$$| $$  | $$ /$$\n");
    printf("|__/  |__/ \\_______/|__/  |__/ \\____  $$|__/     |__/ \\_______/|__/  |__/|__/\n");
    printf("                               /$$  \\ $$                                     \n");
    printf("                              |  $$$$$$/                                     \n");
    printf("                               \\______/                                     \n");

    printf("\t\t======================================\n");
    printf("\t\t\tWELCOME TO HANGMAN GAME!!!\n");
    printf("\t\t\tFROM BEI TEAM...\n");
    printf("\t\t\t1.Start\n\t\t\t2.Help\n\t\t\t3.Exit\n");
    printf("\t\t======================================\n");
    
    scanf("%d",&select);
if(select==1)
{
restart:
    number_of_tries = 0;
    
    strcpy(picked_word, pickRandomWord(words, MAX_WORDS));
    len = strlen(picked_word);

    char store[len + 1];
    memset(store, '_', len);
    store[len] = '\0';

    printf("%s\n", store);

    while (number_of_tries < MAX_ATTEMPTS) {
        if (strcmp(picked_word, store) == 0) {
            printf("Congratulations! You guessed the word correctly.\n");
            
            break;
        } else {
            printf("Enter a character: ");
            scanf(" %c", &guess);

            match = 0;
            for (int i = 0; i < len; i++) {
                if (guess == picked_word[i]) {
                    store[i] = picked_word[i];
                    match = 1;
                }
            }

            if (!match) {
                number_of_tries++;
                printf("Incorrect guess!\n");
                printf("Attempts left: %d\n", MAX_ATTEMPTS - number_of_tries);
                displayHangman(number_of_tries);
            } else {
                printf("Correct guess!\n");
            }

            printf("%s\n", store);
        }
    }

    if (number_of_tries == MAX_ATTEMPTS) {
        printf("You lose!\nThe word was: %s\n", picked_word);
    }

    savePlayer(player);

    printf("Do you want to play again? (y/n): ");
    scanf(" %c", &play_again);

    if (play_again == 'y' || play_again == 'Y') {
        goto restart;
    }
    else{
        printf("Thanks for playing!!!");
    }
}
    else if(select==2)
        {
            printf("\n\n1.Objective: Guess the word before the hangman is fully drawn.\n2.Setup: One player thinks of a word and draws dashes representing each letter.\n3.Guessing: Guess letters one at a time. Correct guesses fill in the blanks, wrong guesses add parts to the hangman.\n4.Number of Guesses: Typically 8 incorrect guesses allowed.\n5.Strategy: Start with common letters. Look for patterns in the blanks.\n6.Winning/Losing: Guesser wins if they guess the word. Chooser wins if the hangman is fully drawn.\n");
            printf("\nPress 1 to return homepage\n");
            scanf("%d",&n);
            if(n==1)
                goto back;
        }
     else if(select==3)
        {
            back1:
            printf("Are you sure you want to exit? Type 'y' for yes or 'n' for no\n");
            scanf(" %c",&confirm);

            if(confirm=='y')
            {
                printf("Thanks for playing!!");
            }
            else if(confirm=='n')
            {
                goto back;
            }
            else
            {
                printf("Please follow the instructions properly!\n");
                goto back1;
            }

        }
        else
        {
            printf("Please select among these three options\n");
            goto back;
        }
return 0;
}