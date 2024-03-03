#ifndef SIDE_H
#define SIDE_H

#include "main.h"

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// size of char variable
#define STD5 6
#define STD6 7
#define STD7 8
#define STD8 9


// ANSI color codes for boxed in letters
#define GREEN "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET "\e[0;39m"
#define RED_TEXT "\x1B[31m"

// ----- MAIN ----- //

int personal_area(userData *user);

// ----- WORDLE ----- //

float wordle(void);
char* get_guess(int wordsize);
int check_word(char guess[], int wordsize, int status[], char choice[]);
void print_word(char guess[], int wordsize, int status[]);
void addStats(float* temporary_score, int* temporary_level, char* temporary_permissions, float result);

// ----- CODE ----- //

void menuNavigation(int* positional_flag, userData *user, statistics *account_stats, int* root_login) {
    do {
        int err_msg_displayed = 0;
        switch (*positional_flag) {
            case 0:
                return;
            case 1:  
                int paResult = -1;              
                if (signIn(user) == 0) {
                    paResult = personal_area(user);
                    if (paResult == 0) {
                        *positional_flag = 0;
                        return;
                    } else if (paResult == 1) {
                        do {
                            paResult = personal_area(user);
                        } while (paResult == 1);
                        *positional_flag = 0;
                    }
                }
                break;
            case 2:
                *root_login = 0;
                paResult = 3;
                if (logIn(positional_flag, user, account_stats, root_login)) {  // The attempts are finished
                    *positional_flag = 0;
                    return;
                }
                printf("%d\n", *root_login);
                if (*root_login == 0) {
                    paResult = personal_area(user);
                    if (paResult == 0) {
                        *positional_flag = 0;
                        return;
                    } else if (paResult == 1) {
                        do {
                            paResult = personal_area(user);
                        } while (paResult == 1);
                        *positional_flag = 0;
                    }
                }
                break;
            case 3:
                subscriptions();
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
        if (*positional_flag == 1) {
            printf("\n2. Log-in\n");
            printf("3. Subscriptions\n");
            printf("0. Main Menu\n");
            printf("\nEnter your choice: ");
            while (scanf("%d", positional_flag) != 1 || (*positional_flag != 0 || *positional_flag != 3 || *positional_flag != 2)) {
                clearInputBuffer();
                printf("\r%sinvalid parameter%s. Enter a valid input: ", RED_TEXT, RESET_TEXT);
            }   
        } else if (*positional_flag == 2) {
            printf("\n1. Sign-in\n");
            printf("3. Subscriptions\n");
            printf("0. Main Menu\n");
            printf("\nEnter your choice: ");
            while (scanf("%d", positional_flag) != 1 || (*positional_flag != 0 && *positional_flag != 3 && *positional_flag != 1)) {
                clearInputBuffer();
                printf("\r%sinvalid parameter%s. Enter a valid input: ", RED_TEXT, RESET_TEXT);
            }   
        } else if (*positional_flag == 3) {
            printf("1. Sign-in\n");
            printf("2. Log-in\n");
            printf("0. Main Menu\n");
            printf("\nEnter your choice: ");
            while (scanf("%d", positional_flag) != 1 || (*positional_flag < 0 || *positional_flag > 2)) {
                clearInputBuffer();
                printf("\r%sinvalid parameter%s. Enter a valid input: ", RED_TEXT, RESET_TEXT);
            }    
        }
        
        clearInputBuffer();

    } while (1);
}

void generateUniqueID(userData *user) {
    // Use a combination of characters or numbers for the ID
    snprintf(user->id, 9, "%c%c%d", user->name[0], user->surname[strlen(user->surname)-1], user->index);
}

int readAndUpdateIndex(void) {
    FILE *indexFile = fopen(INDEX_FILE, "r+");
    if (indexFile == NULL)
    {
        fprintf(stderr, "Error opening index file.\n");
        return -1;
    }

    int index;
    if (fscanf(indexFile, "%d", &index) != 1)
    {
        fprintf(stderr, "Error reading index from file.\n");
        fclose(indexFile);
        return -1;
    }

    // Update the index in the file
    fseek(indexFile, 0, SEEK_SET);
    fprintf(indexFile, "%d", index + 1);

    fclose(indexFile);
    return index;
}

void clearTerminal(void) {
    // Clear terminal
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For Linux and other Unix-like systems
    #endif
}

void clearInputBuffer(void) {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void updateStats(char *fileName, int newLevel, float newScore, const char *permissions) {
    FILE *tempAccount = fopen("temp.txt", "w");
    if (tempAccount == NULL) {
        perror("Error opening the temporary file.\n");
        exit(EXIT_FAILURE);
    }

    FILE *account = fopen(fileName, "r");
    if (account == NULL) {
        perror("Error opening the original file.\n");
        fclose(tempAccount);
        exit(EXIT_FAILURE);
    }

    char buffer[STD_SIZE];

    while (fgets(buffer, sizeof(buffer), account) != NULL) {
        if (strstr(buffer, "Level:") != NULL) {
            fprintf(tempAccount, "Level: %d  ||  Total Score: %.2f  ||  Permissions: %s\n", newLevel, newScore, permissions);
        } else {
            fputs(buffer, tempAccount);
        }
    }

    fclose(account);
    fclose(tempAccount);

    if (remove(fileName) != 0) {
        perror("Error removing the original file.\n");
        exit(EXIT_FAILURE);
    }

    if (rename("temp.txt", fileName) != 0) {
        perror("Error renaming the temporary file.\n");
        exit(EXIT_FAILURE);
    }
}

int personal_area(userData *user) {
    clearTerminal();

    char fileName[STD_SIZE];
    snprintf(fileName, sizeof(fileName), "./usr/%s.txt", user->id);

    FILE *account = fopen(fileName, "r");
    if (account == NULL) {
        perror("Error opening the file.\n");
        exit(EXIT_FAILURE);
    }
    printf("%s%sWelcome back, %s!!%s%s\n\n", BKG_WHITE, BLACK_TEXT, user->name, BKG_RESET, RESET_TEXT);
    printf("%s----- Personal informations -----%s\n\nID: %s\nName: %s\nSurname: %s\nAge: %d\nPhone number: %s\nEmail: %s\nPassword: %s\n\n",
            BOLD, RESET_BOLD, user->id, user->name, user->surname, user->age, user->phonenumber, user->email, user->password);
    printf("%s----- %s's Zone -----%s\n", BOLD, user->name, RESET_BOLD); // print the name
    printf("\nStatistics:\n\n");

    char buffer[STD_SIZE];

    while (fgets(buffer, sizeof(buffer), account) != NULL) {
        if (strstr(buffer, "Level:") != NULL) {
            printf("%s\n", buffer);
            break;
        }
    }
    
    fclose(account);

    printf("\n1. WORDLE\n");
    printf("0. Exit\n");
    printf("\nEnter your choice: ");

    int choice = 2;
    while (scanf("%d", &choice) != 1 || (choice != 0 && choice != 1)) {
        clearInputBuffer();
        printf("\r%sinvalid parameter%s. Enter a valid input: ", RED_TEXT, RESET_TEXT);
    }

    if (choice == 1) {
        float result = wordle();

        if (result != 0) {
            account = fopen(fileName, "r");
            if (account == NULL) {
                perror("Error opening the file.\n");
                exit(EXIT_FAILURE);
            }

            buffer[0] = '\0';
            float temporary_score = 0;
            int temporary_level = 0;
            char temporary_permissions[STD_SIZE];

            while (fgets(buffer, sizeof(buffer), account) != NULL) {
                if (strstr(buffer, "Level:") != NULL) {
                    sscanf(buffer, "Level: %d  ||  Total Score: %f  ||  Permissions: %99[^\n]", &temporary_level, &temporary_score, temporary_permissions);
                    break;
                }
            }

            addStats(&temporary_score, &temporary_level, temporary_permissions, result);

            updateStats(fileName, temporary_level, temporary_score, temporary_permissions);
        }
        return 1;

    } else if (choice == 0) {
        return 0;
    }
}

void addStats(float* temporary_score, int* temporary_level, char* temporary_permissions, float result) {
                if (*temporary_score < 5) {
                *temporary_score += result;
                if (*temporary_score >= 5) {
                    (*temporary_level)++;
                    strcpy(temporary_permissions, "basic+");
                }
            } else {
                *temporary_score += result;
            }
    return;
}

float wordle(void) {
    int wordsize = 0;
    clearTerminal();
    printf("Welcome, enter the size of the word, between 5 and 8.\n");
    printf("A size of 8 corresponds to 1.00 points.\n");
    printf("A size of 7 corresponds to 0.75 points.\n");
    printf("A size of 6 corresponds to 0.50 points.\n");
    printf("A size of 5 corresponds to 0.25 points.\n\n");
    printf("\nWORD SIZE: ");
    while (scanf("%d", &wordsize) != 1 || wordsize < 5 || wordsize > 8) {
        clearInputBuffer();
        printf("%sInvalid size%s.\n", RED_TEXT, RESET);
        printf("WORD SIZE: ");
    }

    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[15];
    sprintf(wl_filename, "./wordle/%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        exit(EXIT_FAILURE);
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    char choice[wordsize + 1];
    strcpy(choice, options[rand() % LISTSIZE]);

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    int won = 0;

    // print greeting, using ANSI color codes to demonstrate
    system("clear");
    printf(GREEN "This is WORDLE50" RESET "\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    char *guess;
    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];
        // set all elements of status array initially to 0, aka WRONG
        // TODO #4
        for (int j = 0; j < wordsize; j++)
        {
            status[j] = 0;
        }

        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);
        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);
        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = 1;
            break;
        }
    }

    free(guess);

    // Print the game's result
    // TODO #7
    if (won)
    {
        if (wordsize == 5) {   
            printf("\nYou won!\n");
            printf("+0.25");
            fflush(stdout);
            fclose(wordlist);
            sleep(5);
            return 0.25;
        } else if (wordsize == 6) {
            printf("\nYou won!\n");
            printf("+0.50");
            fflush(stdout);
            fclose(wordlist);
            sleep(5);
            return 0.50;
        } else if (wordsize == 7) {
            printf("\nYou won!\n");
            printf("+0.75");
            fflush(stdout);
            fclose(wordlist);
            sleep(5);
            return 0.75;
        } else if (wordsize == 8) {
            printf("\nYou won!\n");
            printf("+1.00");
            fflush(stdout);
            fclose(wordlist);
            sleep(5);
            return 1;
        }
    }
    else
    {
        printf("Sorry.. The word was: %s\n", choice);
        fclose(wordlist);
        sleep(5);
        return 0;
    }
}

char* get_guess(int wordsize)
{
    // TODO #3
    
    int displayed = 0;
    char *guess = (char *)malloc((wordsize + 1));
    if (guess == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    int length;

    printf("Enter a %i-letter word: ", wordsize);
    do {
        if (displayed) {
            printf("%sInvalid input%s. Enter a %i-letter word:", RED_TEXT, RESET, wordsize);
        } else {
            displayed = 1;
        }

        while (scanf("%s", guess) != 1) {
            char c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        length = strlen(guess);

    } while (length != wordsize);
    return guess;
}

int check_word(char guess[], int wordsize, int status[], char choice[])
{
    // compare guess to choice and score points as appropriate, storing points in status
    // TODO #5
    int score = 0;
    for (int i = 0; i < wordsize; i++)
    {
        if (guess[i] == choice[i])
        {
            status[i] = EXACT;
            score += EXACT;
        }
        else
        {
            for (int j = 0; j < wordsize; j++)
            {
                if (guess[i] == choice[j])
                {
                    status[i] = CLOSE;
                    score += CLOSE;
                }
            }
        }
    }
    return score;
}

void print_word(char guess[], int wordsize, int status[])
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    // TODO #6
    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == EXACT)
        {
            printf(GREEN "%c" RESET, guess[i]);
        }
        else if (status[i] == CLOSE)
        {
            printf(YELLOW "%c" RESET, guess[i]);
        }
        else
        {
            printf(RED "%c" RESET, guess[i]);
        }
    }
    printf("\n");
    return;
}
#endif  // SIDE_H