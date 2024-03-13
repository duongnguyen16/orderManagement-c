#include <stdio.h>
#include <conio.h> // For getch() function

#define MENU_SIZE 4

const char *menuOptions[MENU_SIZE] = {
    "Option 1",
    "Option 2",
    "Option 3",
    "Exit"};

int main()
{
    int choice = 0;
    int i;

    while (1)
    {
        // Display menu options
        for (i = 0; i < MENU_SIZE; i++)
        {
            if (i == choice)
            {
                printf(">> %s\n", menuOptions[i]);
            }
            else
            {
                printf("   %s\n", menuOptions[i]);
            }
        }

        // Get user input
        char key = getch();

        // Handle user input
        switch (key)
        {
        case 'w': // Up arrow key
            choice = (choice - 1 + MENU_SIZE) % MENU_SIZE;
            break;
        case 's': // Down arrow key
            choice = (choice + 1) % MENU_SIZE;
            break;
        case '\r': // Enter key
            if (choice == MENU_SIZE - 1)
            {
                // Exit if "Exit" option is selected
                return 0;
            }
            printf("\nYou selected: %s\n", menuOptions[choice]);
            break;
        default:
            break;
        }

        // Move cursor up to the beginning of the menu
        for (i = 0; i < MENU_SIZE; i++)
        {
            printf("\033[A");
        }
    }

    return 0;
}
