#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./Headers/main.h"
#include "./Headers/root.h"
#include "./Headers/side.h"

int main(void)
{
    userData *user = malloc(sizeof(userData));  // Dynamically allocate memory
        if (user == NULL) {
            perror("Error allocating memory.\n");
            return 1;
        }

    statistics *account_stats = malloc(sizeof(statistics));  // Dynamically allocate memory
        if (account_stats == NULL) {
            perror("Error allocating memory.\n");
            return 1;
        }

    int root_login = 0;
    int positional_flag = 0;
    int invalid_input = 0;
    char choice;

    do {
        mainMenu(&invalid_input);
        invalid_input = 0;
        scanf(" %c", &choice);
        clearInputBuffer();

        switch (choice) {
            case '0':
                clearTerminal();
                printf("Quitting..\n\n");
                fflush(stdout);
                sleep(1);
                free(user);
                return 0;
            case '1':
                positional_flag = 1;
                menuNavigation(&positional_flag, user, account_stats, &root_login);
                break;
            case '2':
                positional_flag = 2;
                menuNavigation(&positional_flag, user, account_stats, &root_login);
                break;
            case '3':
                positional_flag = 3;
                menuNavigation(&positional_flag, user, account_stats, &root_login);
                break;
            default:
                invalid_input = 1;
                clearTerminal();
                printf("%sInvalid Input%s: you must enter %s1%s to register, %s2%s to log-in, %s3%s to show the list of subscriptions or %s0%s to quit.\n\n",
                        RED_TEXT, RESET_TEXT, GREEN_TEXT, RESET_TEXT, GREEN_TEXT, RESET_TEXT, GREEN_TEXT, RESET_TEXT, GREEN_TEXT, RESET_TEXT);
        }
    } while (positional_flag == 0);
    free(user);
    free(account_stats);
    return 0;
}