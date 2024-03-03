#ifndef ROOT_H
#define ROOT_H

#include "side.h"

// ----- DECLARATIONS ----- //

// Function to check root at log-in
int checkRoot(FILE* database, char buffer[], size_t buffer_size, char email[], char password[]);

// Function to access in ROOT
void rootMenu(int* root_positional_flag, int* positional_flag, userData *user, int* root_login);

// Function ROOT account deletion
void deleteAccount(userData *user);

// Function to display all the ID
void checkID(void);

//Function to reset the database
void reset(void);

// ----- CODE ----- //

int checkRoot(FILE* database, char buffer[], size_t buffer_size, char email[], char password[]) {

    if (strstr(buffer, "ROOT") != NULL) {
        size_t root_block = ftell(database);
        char cmpEmail[STD_SIZE];
        char cmpPassword[STD_SIZE];
        while(fgets(buffer, buffer_size, database) != NULL && buffer[0] != '\n') {
            if (strstr(buffer, "Email: ") != NULL) {
                sscanf(buffer, "Email: %99[^\n]", cmpEmail);
            } else if (strstr(buffer, "Password: ") != NULL) {
                sscanf(buffer, "Password: %99[^\n]", cmpPassword);
            }
        }
        if (strcmp(email, cmpEmail) == 0 && strcmp(password, cmpPassword) == 0) {
            fseek(database, root_block, SEEK_SET);
            while(fgets(buffer, buffer_size, database) != NULL && buffer[0] != '\n') {
               if (strstr(buffer, "Root_Name # ") != NULL) {
                sscanf(buffer, "Root_Name # %99[^\n]", root_name);
                break;
                } 
            }
            clearTerminal();
            
            return 1;
        }
    }
    return 0;
}

void rootMenu(int* root_positional_flag, int* positional_flag, userData *user, int* root_login) {
    do {
        *root_login = 1;
        printf("%s-- ROOT MENU --%s\n", BKG_RED, BKG_RESET);
        printf("ROOT: %s\n\n", root_name);  // Assuming root_name is a string variable
        printf("1. Delete Account\n");
        printf("2. Reset Database\n");
        printf("3. Show ID\n");
        printf("0. Exit\n");
        printf("Coming Soon..\n");
        printf("\nEnter your choice: ");

        if (scanf("%d", root_positional_flag) != 1) {
            clearInputBuffer();  // Clear the input buffer in case of non-numeric input
            clearTerminal();
            printf("%sInput not recognized.%s\n\n", RED_TEXT, RESET_TEXT);
            continue;  // Go back to the beginning of the loop
        }

        switch (*root_positional_flag) {
            case 0:
                *positional_flag = 0;
                return;
            case 1:
                deleteAccount(user);
                break;
            case 2:
                reset();
                break;
            case 3:
                checkID();
                int validator = 1;
                printf("\n\n0. Exit");
                printf("\n");
                while (scanf("%d", &validator) != 1 || validator != 0) {
                    printf("\r%sInvalid Input%s. Enter a correct value: ", RED_TEXT, RESET_TEXT);
                    clearInputBuffer();
                }
                clearTerminal();
                break;
            default:
                clearTerminal();
                printf("%sInput not recognized.%s\n\n", RED_TEXT, RESET_TEXT);
                break;
        }
        
    } while (1);
}

void deleteAccount(userData *user) {
    getchar();

    char choice[10];
    choice[0] = '\0';
    char id[10];
    id[0] = '\0';
    size_t data_block_start = 0;
    size_t data_block_end = 0;

    clearTerminal();
    printf("%s%sEnter the ID of the account to delete.%s%s\n\n", BKG_WHITE, BLACK_TEXT, RESET_TEXT, BKG_RESET);
    printf("ID: ");
    fgets(choice, sizeof(choice), stdin);
    // Remove the newline character
    size_t length = strlen(choice);
    if (length > 0 && choice[length - 1] == '\n') {
        choice[length - 1] = '\0';
    }

    char buffer[STD_SIZE];
    buffer[0] = '\0';

    FILE *database = fopen(DATA_FILE, "r");
    if (database == NULL) {
        perror("Error opening the file.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), database) != NULL) {
        if (strstr(buffer, "ACCOUNT ID: ") != NULL) {
            sscanf(buffer, "ACCOUNT NUMBER: %*d  //  ACCOUNT ID: %9[^\n]", id);
            data_block_start = ftell(database) - strlen(buffer);
            printf("%s\n", id);
        }

        if (strcmp(choice, id) == 0) {
            // Find the end of the data block (next white line)
            while (fgets(buffer, sizeof(buffer), database) != NULL) {
                if (strcmp(buffer, "\n") == 0) {
                    break;
                }
            }
            data_block_end = ftell(database);


            // Open a temporary file for writing
            FILE *tempFile = fopen("./Data/temp.txt", "w");
            if (tempFile == NULL) {
                perror("Error opening the temporary file.\n");
                fclose(database);
                return;
            }

            fseek(database, 0, SEEK_SET);

            // Copy contents excluding the data block to the temporary file
            while (ftell(database) != data_block_start) {
                if (fgets(buffer, sizeof(buffer), database) != NULL) {
                    fputs(buffer, tempFile);
                } else {
                    break;
                }
            }

            // Skip the data block in the original file
            fseek(database, data_block_end, SEEK_SET);

            // Copy the rest of the file to the temporary file
            while (fgets(buffer, sizeof(buffer), database) != NULL) {
                fputs(buffer, tempFile);
            }

            // Close both files
            fclose(database);
            fclose(tempFile);

            // Rename the temporary file to the original file
            if (rename("./Data/temp.txt", DATA_FILE) != 0) {
                perror("Error renaming the temporary file.\n");
            }

            // Updating the index
            FILE *index = fopen(INDEX_FILE, "r");
            if (index == NULL) {
                perror("Error opening the index file.\n");
                return;
            }

            char idx[10];
            int n = 0;

            fgets(idx, sizeof(idx), index);
            sscanf(idx, "%d", &n);
            
            fclose(index);

            FILE *newIndex = fopen(INDEX_FILE, "w");
            if (newIndex == NULL) {
                perror("Error opening the new file.\n");
                return;
            }

            // Write in txt file the same index minus one...
            n--;
            fprintf(newIndex, "%d\n", n);

            fclose(newIndex);

            char file_to_delete[50];
            snprintf(file_to_delete, sizeof(file_to_delete), "./usr/%s.txt", id);
            remove(file_to_delete);

            clearTerminal();
            printf("%sAccount deleted successfully.%s\n\n", RED_TEXT, RESET_TEXT);
            return;
        }
    }

    fclose(database);
    clearTerminal();
    printf("%s%sID not found.%s%s\n\n", BKG_WHITE, BLACK_TEXT, RESET_TEXT, BKG_RESET);
}

void checkID(void) {
    clearTerminal();
    printf("%s%sBelow the list of all the ID and associated email on the platform.%s%s\n", BKG_WHITE, BLACK_TEXT, RED_TEXT, BKG_RESET);

    FILE *database = fopen(DATA_FILE, "r");
    if (database == NULL) {
        perror("Error opening the file.\n");
        return;
    }
    
    char buffer[STD_SIZE];
    char id[10];
    char email[STD_SIZE];

    while(fgets(buffer, sizeof(buffer), database) != NULL) {
        if (strstr(buffer, "ACCOUNT NUMBER: ") != NULL) {
            sscanf(buffer, "ACCOUNT NUMBER: %*d  //  ACCOUNT ID: %9[^\n]", id);
            printf("\nUser's ID: %s", id);
            while (fgets(buffer, sizeof(buffer), database) != NULL && buffer[0] != '\n') {
                if (strstr(buffer, "Email: ") != NULL) {
                    sscanf(buffer, "Email: %99[^\n]", email);
                    printf("\nEmail: %s", email);
                    printf("\n-----");
                }
            }
        } 
    }

    fclose(database);
}

void reset(void) {
    clearTerminal();
    char choice[2];
    printf("%s%sARE YOU SURE YOU WANT TO RESET THE DATABASE ?%s%s\n", BKG_RED, BLACK_TEXT, RESET_TEXT, BKG_RESET);
    printf("If you confirm, all the data will be lost.\n-y to confirm\n-n to decline\n\n");
    printf("Enter your choice: ");

    while (scanf("%1s", choice) != 1 || (choice[0] != 'y' && choice[0] != 'Y' && choice[0] != 'n' && choice[0] != 'N')) {
        clearInputBuffer();
        printf("%s\nInvalid Input%s. Enter 'y' to confirm or 'n' to return in the ROOT menù.\n", RED_TEXT, RESET_TEXT);
        printf("\nEnter your choice: ");
    }

    if (choice[0] == 'y' || choice[0] == 'Y') {
        FILE *file = fopen(DATA_FILE, "r");
        if (file == NULL) {
            perror ("Error opening the file for the deletion.\n");
            exit(EXIT_FAILURE);
        }

        char buffer[STD_SIZE];
        char fileId[STD_SIZE];
        char fileName[STD_SIZE*2];

        while (fgets(buffer, sizeof(buffer), file) != NULL){
            if (strstr(buffer, "ACCOUNT") != NULL) {
                sscanf(buffer, "ACCOUNT NUMBER: %*d  //  ACCOUNT ID: %99[^\n]", fileId);
                sprintf(fileName, "./usr/%s.txt", fileId);
                remove(fileName);
            }
        }

        fclose(file);

        file = fopen(DATA_FILE, "w");
        FILE *fileIndex = fopen(INDEX_FILE, "w");
        if (file == NULL || fileIndex == NULL) {
            perror ("Error opening the file for reset.\n");
            exit(EXIT_FAILURE);
        }

        fprintf(file, "ROOT USER\n");
        fprintf(file, "Root_Name # Salvatore\n");
        fprintf(file, "Email: root@menu.access\n");
        fprintf(file, "Password: root\n\n");

        fclose(file);
        fprintf(fileIndex, "2");
        fclose(fileIndex);

        clearTerminal();
        printf("Formatting...");
        fflush(stdout);
        sleep(4);
        clearTerminal();
        printf("%sDatabase formatted succesfully%s.\n\n", RED_TEXT, RESET_TEXT);
        fflush(stdout);
        sleep(2);
        return;
    } else {
        clearTerminal();
        printf("Declined..");
        fflush(stdout);
        sleep(2);
        clearTerminal();
        return;
    }
}

#endif // ROOT_H