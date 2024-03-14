#include <stdio.h>
#include <conio.h>

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

        char key = getch();

        switch (key)
        {
        case 'w':
            choice = (choice - 1 + MENU_SIZE) % MENU_SIZE;
            break;
        case 's':
            choice = (choice + 1) % MENU_SIZE;
            break;
        case '\r':
            if (choice == MENU_SIZE - 1)
            {

                return 0;
            }
            printf("\nYou selected: %s\n", menuOptions[choice]);
            break;
        default:
            break;
        }

        for (i = 0; i < MENU_SIZE; i++)
        {
            printf("\033[A");
        }
    }

    return 0;
}
