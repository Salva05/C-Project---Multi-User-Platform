#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Define the maximum size for strings
#define STD_SIZE 100
#define INDEX_FILE "./Data/index.txt"
#define DATA_FILE "./Data/data.txt"

// ANSI color escape codes
#define GREEN_TEXT "\x1b[32m"
#define RED_TEXT "\x1B[31m"
#define WHITE_TEXT "\033[37m"
#define BLACK_TEXT "\x1b[30m"
#define RESET_TEXT "\x1b[0m"
#define BKG_BLACK "\033[40m"
#define BKG_WHITE "\033[47m"
#define BKG_GREEN "\033[42m"
#define BKG_RED "\033[41m"
#define BKG_RESET "\033[0m"
#define BOLD "\033[1m"
#define RESET_BOLD "\033[0m"

// --- WORDLE50 --- //

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// --- MAIN --- //

// Struct for user's account
typedef struct {
    int index;
    char id[10];
    char name[STD_SIZE];
    char surname[STD_SIZE];
    int age;
    char phonenumber[STD_SIZE];
    char email[STD_SIZE];
    char password[STD_SIZE];
} userData;

typedef struct {
    int level;
    char permissions[STD_SIZE];
    float score;
} statistics;

char root_name[STD_SIZE];

// ----- Side Functions ----- //

// Function to clear the terminal
void clearTerminal(void);

// Function to clear the input buffer
void clearInputBuffer(void);

// Function to generate a unique ID
void generateUniqueID(userData *user);

// Function to read and update the index from a file
int readAndUpdateIndex(void);

// Function to retrive the level for subscriptions
int getLvl(char name[], char temp_id[]);

// ----- Menu Functions ----- //

// Function to navigate through menu
void menuNavigation(int* positional_flag, userData *user, statistics *account_stats, int* root_login);

// Function to display main menu
void mainMenu(int* invalid_input);

// ----- Main Functions ----- //

// Function for user registration
int signIn(userData *user);

// Function for login validation
int logIn(int* positional_flag, userData *user, statistics *account_stats, int* root_login);

// Function for subscription details
void subscriptions(void);

// ----- ROOT Functions ----- //

// Function to check root at log-in
int checkRoot(FILE* database, char buffer[], size_t buffer_size, char email[], char password[]);

// Function to access in ROOT
void rootMenu(int* root_positional_flag, int* positional_flag, userData *user, int* root_login);

// Function ROOT account deletion
void deleteAccount(userData *user);

// Function to display all the ID
void checkID(void);

// Function to reset the database
void reset(void);

// ----- WORDLE50 ----- //
float wordle(void);
char* get_guess(int wordsize);
int check_word(char guess[], int wordsize, int status[], char choice[]);
void print_word(char guess[], int wordsize, int status[]);

// ----- CODE ----- //

void mainMenu(int* invalid_input) {
    if (*invalid_input == 0) {
        clearTerminal();
    }
    printf("%s--- WELCOME TO THE PLATFORM ---%s\n", BKG_GREEN, BKG_RESET);
    printf("           %sMain Menu%s\n", GREEN_TEXT, RESET_TEXT);
    printf("\n1. Sign-in\n");
    printf("2. Log-in\n");
    printf("3. Subscriptions\n");
    printf("0. Quit\n");
    printf("\nEnter your choice: ");
}

int signIn(userData *user) {
    clearTerminal();
    printf("%s%sWelcome, here you can register to the plattform.\nPlease follow the instructions.%s%s\n\nName: ",
             BKG_WHITE, BLACK_TEXT, BKG_RESET, RESET_TEXT);
            
    char buffer[STD_SIZE];

    scanf("%99s", user->name);
    getchar();

    clearTerminal();
    printf("%s%sWelcome, here you can register to the plattform.\nPlease follow the instructions.%s%s\n\n",
             BKG_WHITE, BLACK_TEXT, BKG_RESET, RESET_TEXT);
    printf("Surname: ");
    scanf("%99s", user->surname);
    getchar();

    clearTerminal();
    printf("%s%sWelcome, here you can register to the plattform.\nPlease follow the instructions.%s%s\n\n",
             BKG_WHITE, BLACK_TEXT, BKG_RESET, RESET_TEXT);
    printf("Email: ");
    scanf("%99s", user->email);
    getchar();

    clearTerminal();
    printf("%s%sWelcome, here you can register to the plattform.\nPlease follow the instructions.%s%s\n\n",
             BKG_WHITE, BLACK_TEXT, BKG_RESET, RESET_TEXT);
    printf("Age: ");
    scanf("%d", &user->age);
    getchar();

    clearTerminal();
    printf("%s%sWelcome, here you can register to the plattform.\nPlease follow the instructions.%s%s\n\n",
             BKG_WHITE, BLACK_TEXT, BKG_RESET, RESET_TEXT);
    // Treat the phone number field differently
    // since it could contain a space (after the prefix perhaps)
    printf("Phone number: ");
    fgets(user->phonenumber, sizeof(user->phonenumber), stdin);
    // Remove the trailing newline character, if present
    size_t len = strlen(user->phonenumber);
    if (len > 0 && user->phonenumber[len - 1] == '\n') {
        user->phonenumber[len - 1] = '\0';
    }

    clearTerminal();
    printf("%s%sWelcome, here you can register to the plattform.\nPlease follow the instructions.%s%s\n\n",
             BKG_WHITE, BLACK_TEXT, BKG_RESET, RESET_TEXT);
    printf("Password: ");
    scanf("%99s", user->password);

    FILE* database = fopen(DATA_FILE, "a");
    if (database == NULL)
    {
        fprintf(stderr, "Error opening the file.\n");
        exit(EXIT_FAILURE);
    }

    // Read and update the index from a file
    int currentIndex = readAndUpdateIndex();
    if (currentIndex == -1) {
        // Error handling
        perror("Error occurred.\n");
        exit(EXIT_FAILURE);
    }

    // Set the user's index
    user->index = currentIndex;

    // Generate a unique ID for the user
    generateUniqueID(user);

    // Write user data to the file
    fprintf(database, "ACCOUNT NUMBER: %d  //  ACCOUNT ID: %s\n", user->index, user->id);
    fprintf(database, "Name: %s\n", user->name);
    fprintf(database, "Surname: %s\n", user->surname);
    fprintf(database, "Email: %s\n", user->email);
    fprintf(database, "Age: %d\n", user->age);
    fprintf(database, "Phone number: %s\n", user->phonenumber);
    fprintf(database, "Password: %s\n\n", user->password);

    fclose(database); // Close the file after writing
    clearTerminal();

    char fileName[20];
    snprintf(fileName, sizeof(fileName), "./usr/%s.txt", user->id);

    FILE *account = fopen(fileName, "w");
    if (account == NULL) {
    perror("Error opening file");
    return 1;
    }
    
    statistics account_stats;
    strcpy(account_stats.permissions, "basic");
    account_stats.level = 1;
    account_stats.score = 0.0;

    // Write user data to the file
    fprintf(account, "                  ## Data ##\n\n");
    fprintf(account, "ACCOUNT NUMBER: %d  //  ACCOUNT ID: %s\n", user->index, user->id);
    fprintf(account, "Name: %s\n", user->name);
    fprintf(account, "Surname: %s\n", user->surname);
    fprintf(account, "Email: %s\n", user->email);
    fprintf(account, "Age: %d\n", user->age);
    fprintf(account, "Phone number: %s\n", user->phonenumber);
    fprintf(account, "Password: %s\n\n", user->password);

    fprintf(account, "                  ## Statistics ##\n\n");
    fprintf(account, "Level: %d", account_stats.level);
    fprintf(account, "  ||  Total Score: %.2f", account_stats.score);
    fprintf(account, "  ||  Permissions: %s", account_stats.permissions);
    // More coming soon..

    fclose(account);
    printf("%s%sRegistration was successful! Thanks for joining us.%s%s\n\n", BKG_WHITE, BLACK_TEXT, BKG_RESET, RESET_TEXT);
    sleep(2);
    return 0;
}

int logIn(int* positional_flag, userData *user, statistics *account_stats, int* root_login) {
    int root = 0;
    clearTerminal();
    printf("%s%sEnter your data to log into the platform.%s%s\n\n", BKG_WHITE, BLACK_TEXT, BKG_RESET, RESET_TEXT);
    int result = 0;
    int error_code = 0;
    int attempts = 3;

    FILE *database = fopen(DATA_FILE, "r");
    if (database == NULL) {
        perror("Error opening the file.\n");
        free(user);
            exit(EXIT_FAILURE);
    }

    char fileName[50];
    fileName[0] = '\0';

    do {
        if (attempts == 0) {
            clearTerminal();
            printf("%sNumber of attempts exceeded, quitting...%s", RED_TEXT, RESET_TEXT);
            fflush(stdout); // Flush the output buffer
            sleep(2); // Pause for 2 seconds
            return 1;
        }
        fseek(database, 0, SEEK_SET);
        char buffer[STD_SIZE];
        buffer[0] = '\0';
        size_t data_block = 0;
        
        char email[STD_SIZE];
        email[0] = '\0';
        char password[STD_SIZE];
        password[0] = '\0';
        char cmpEmail[STD_SIZE];
        cmpEmail[0] = '\0';
        char cmpPassword[STD_SIZE];
        cmpPassword[0] = '\0' ;


        // Prompt the user for data
        clearTerminal();
        if (error_code) {
            printf("%sError: invalid email or password. %d Attempts left.%s\n\n", RED_TEXT, attempts, RESET_TEXT);
        }
        printf("%s%sEnter your data to log into the platform.%s%s\n\n", BKG_WHITE, BLACK_TEXT, BKG_RESET, RESET_TEXT);
        printf("Email: ");
        scanf("%99s", email);

        clearTerminal();
        if (error_code) {
            printf("%sError: invalid email or password. %d Attempts left.%s\n\n", RED_TEXT, attempts, RESET_TEXT);
        }
        printf("%s%sEnter your data to log into the platform.%s%s\n\n", BKG_WHITE, BLACK_TEXT, BKG_RESET, RESET_TEXT);
        printf("Password: ");
        scanf("%99s", password);

        error_code = 0;

        while (fgets(buffer, sizeof(buffer), database) != NULL) {
            if (checkRoot(database, buffer, sizeof(buffer), email, password)) {
                root = 1;
                break;
            } else if (strstr(buffer, "ACCOUNT NUMBER: ") != NULL) {
                data_block = ftell(database) - strlen(buffer);
                cmpEmail[0] = '\0';
                cmpPassword[0] = '\0';
            }

            if (strstr(buffer, "Email: ") != NULL) {
                sscanf(buffer, "Email: %99[^\n]", cmpEmail);
            } else if (strstr(buffer, "Password: ") != NULL) {
                sscanf(buffer, "Password: %99[^\n]", cmpPassword);
            }

            if (strcmp(email, cmpEmail) == 0 && strcmp(password, cmpPassword) == 0) {
                
                fseek(database, data_block, SEEK_SET);

                while (fgets(buffer, sizeof(buffer), database) != NULL && buffer[0] != '\n') {
                    if (strstr(buffer, "ACCOUNT NUMBER: ") != NULL) {
                        sscanf(buffer, "ACCOUNT NUMBER: %d  //  ACCOUNT ID: %9[^\n]", &user->index, user->id);
                        snprintf(fileName, sizeof(fileName), "./usr/%s.txt" ,user->id);
                    } else if (strstr(buffer, "Name: ") != NULL) {
                        sscanf(buffer, "Name: %99[^\n]", user->name);
                    } else if (strstr(buffer, "Surname: ") != NULL) {
                        sscanf(buffer, "Surname: %99[^\n]", user->surname);
                    } else if (strstr(buffer, "Age: ") != NULL) {
                        sscanf(buffer, "Age: %d", &user->age);
                    } else if (strstr(buffer, "Phone number: ") != NULL) {
                        sscanf(buffer, "Phone number: %99[^\n]", user->phonenumber);
                    } else if (strstr(buffer, "Email: ") != NULL) {
                        sscanf(buffer, "Email: %99[^\n]", user->email);
                    } else if (strstr(buffer, "Password: ") != NULL) {
                        sscanf(buffer, "Password: %99[^\n]", user->password);
                    }
                }
                result = 1;
                break;
            }
        }

        if (result == 0 && root != 1) {
            error_code = 1;
            attempts--;
        }

    } while (result == 0 && root != 1);
    if (root == 0) {
        fclose(database);
        clearTerminal();

        FILE *account = fopen(fileName, "r");
        if (account == NULL) {
            perror("Error opening the file.\n");
            return 1;
        }
        
        char line[STD_SIZE*2];

        while (fgets(line, sizeof(line), account) != NULL) {
            if (strstr(line, "Level:") != NULL) {
                sscanf(line, "Level: %d  ||  Total Score: %f  ||  Permissions: %20[^\n]", &account_stats->level, &account_stats->score, account_stats->permissions);
                break;
            }
        }
        
        fclose(account);

    } else if (root == 1) {
        int root_positional_flag = 0;
        rootMenu(&root_positional_flag, positional_flag, user, root_login);
    }
}

void subscriptions(void) {
    clearTerminal();
    printf("%s%sHere you can see the number of subscriptions and the name of each.%s%s\n",
             BKG_WHITE, BLACK_TEXT, BKG_RESET, RESET_TEXT);
    FILE* file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        perror("Error opening the file.\n");
        return;
    }
    
    int subscribed = 0;
    char buffer[STD_SIZE];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, "Name: ") != NULL) {
            subscribed++;
        }
    }

    printf("\n%sTotal subscribed: %d%s\n\n",BOLD, subscribed, RESET_BOLD);
    fseek(file, 0, SEEK_SET);

    char temp_id[STD_SIZE];
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, "ACCOUNT") != NULL) {
            sscanf(buffer, "ACCOUNT NUMBER: %*d  //  ACCOUNT ID: %99[^\n]", temp_id);
        }
        if (strstr(buffer, "Name: ") != NULL) {
            char name[STD_SIZE];
            sscanf(buffer, "Name: %99[^\n]", name);
            int level = getLvl(name, temp_id);
            printf("Signed: %s  ~  Level: %d\n", name, level);
        }
    }

    fclose(file);
    printf("\n");
}

int getLvl(char name[], char temp_id[]) {
    int level = 0;

    char id[20];
    id[0] = '\0';
    FILE* file1 = fopen(DATA_FILE, "r");
    if (file1 == NULL) {
        perror("Errorrr opening the file for subscriptions.\n");
        exit(EXIT_FAILURE);
    }

    char cmp_id[STD_SIZE];
    size_t block = 0;    
    char buffer[STD_SIZE];
    while (fgets(buffer, sizeof(buffer), file1) != NULL) {
        if (strstr(buffer, "ACCOUNT NUMBER") != NULL) {
            sscanf(buffer, "ACCOUNT NUMBER: %*d  //  ACCOUNT ID: %99[^\n]", cmp_id); 
            block = ftell(file1) - (strlen(buffer));
        }
        if (strstr(buffer, name) != NULL && strstr(buffer, "Root") == NULL && strcmp(temp_id, cmp_id) == 0) {
            fseek(file1, block, SEEK_SET);
            fgets(buffer, sizeof(buffer), file1);
            sscanf(buffer, "ACCOUNT NUMBER: %*d  //  ACCOUNT ID: %99[^\n]", id);
            break;
        }
    }
    fclose(file1);

    char fileName[30];
    sprintf(fileName, "./usr/%s.txt", id);
    FILE* file2 = fopen(fileName, "r");
    if (file2 == NULL) {
        perror("Error opening the file for subscriptions.\n");
        exit(EXIT_FAILURE);
    }


    while (fgets(buffer, sizeof(buffer), file2) != NULL) {
        if (strstr(buffer, "Level:") != NULL) {
            sscanf(buffer, "Level: %d  ||  Total Score: %*f  ||  Permissions: %*s", &level);
            break;
        }
    }
    fclose(file2);
    return level;
}

#endif // LOGIN_H