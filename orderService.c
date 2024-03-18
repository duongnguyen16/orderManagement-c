#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void showDatabase(Order database[], int size, char *filterColumn, char *filterValue, int sort_by_num)
{
    Orders result = extractDataFromDatabase(database, size, filterColumn, filterValue, 1);
    switch (sort_by_num)
    {
    case 1:
        strcpy(result.sort_by, "State");
        break;
    case 2:
        strcpy(result.sort_by, "Id: low to high");
        break;
    case 3:
        strcpy(result.sort_by, "Id: high to low");
        break;
    case 4:
        strcpy(result.sort_by, "Product_name: A-Z");
        break;
    case 5:
        strcpy(result.sort_by, "Product_name: Z-A");
        break;
    default:
        strcpy(result.sort_by, "State");
        break;
    }
    showTable(result, "No orders found.");
}

void order_management_main(Session session)
{
    if (session.groupId == 0)
    {
        exit(1);
    }
    else
    {
        // debug("init database");
        Order database[MAX_ORDERS_AVAILABLE];
        int size = 0;

        User users[100];
        int countUser = 0;
        importUsers(users, &countUser);

        User currentUser = getUserByUsername(users, countUser, session.userName);

        importDatabase(database, &size);
        exportDatabase(database, size);

        char defaultTable;
        if (session.groupId <= 2)
            defaultTable = 'a';
        else
        {
            defaultTable = 'c';
        }

        char choice = defaultTable;
        char currentTab = defaultTable;
        int sort_by_num = 1;
        do
        {
            choice = currentTab;

            system("cls");
            printf("| Current session: %s [%s]\n", currentUser.displayName, GROUP_NAME[session.groupId]);
            showMenu(session.groupId);
            showTabs(choice, session.groupId);

            switch (choice)
            {
            case 'a':
                showDatabase(database, size, "sender_phone_number", currentUser.phoneNumber, sort_by_num);
                currentTab = 'a';
                break;
            case 'b':
                showDatabase(database, size, "receiver_phone_number", currentUser.phoneNumber, sort_by_num);
                currentTab = 'b';
                break;
            case 'c':
                showDatabase(database, size, "", "", sort_by_num);
                currentTab = 'c';
                break;
            }
            printf("> Enter: ");
            scanf(" %c", &choice);

            switch (choice)
            {
            case '1':
                system("cls");
                if (session.groupId >= 2)
                {
                    lookupOrderManager(database, size);
                }
                else
                {
                    lookupOrderUser(database, size, currentUser.phoneNumber);
                }
                getchar();
                printf("\nPress [Enter] to continue...");
                getchar();
                break;
            case '2':
                system("cls");
                if (session.groupId >= 2)
                {
                    createNewOrderManager(database, &size, users, currentUser, countUser);
                }
                else
                {
                    createNewOrderUser(database, &size, users, currentUser, countUser);
                }
                getchar();
                printf("Press [Enter] to continue...");
                getchar();
                break;
            case '3':
                system("cls");
                if (session.groupId > 2)
                {
                    editDeleteOrder(database, size);
                    printf("Press [Enter] to continue...");
                    getchar();
                }
                else
                {
                    printf("Invalid choice. Please try again.\n");
                }

                break;
            case '0':
                return;
            case 'a':
                currentTab = 'a';
                break;
            case 'b':
                currentTab = 'b';
                break;
            case 'c':
                if (session.groupId > 2)
                {
                    currentTab = 'c';
                }
                else
                {
                    printf("Invalid choice. Please try again.\n");
                }
                break;
            case 's':
                sort_by_num = sort_by_choose();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
            }
            exportDatabase(database, size);
        } while (choice != '0');
    }
}
