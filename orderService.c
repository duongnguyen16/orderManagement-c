#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void editDeleteOrder(Order database[], int size)
{
    int id;
    printf("Enter the ID of the order: ");
    scanf("%d", &id);

    int index = -1;
    for (int i = 0; i < size; i++)
    {
        if (database[i].id == id)
        {
            index = i;
            printf("\nOrder Information:\n");
            printf("1. Product Name: %s\n", database[i].product_name);
            printf("2. Sender Name: %s\n", database[i].sender_name);
            printf("3. Sender Phone Number: %s\n", database[i].sender_phone_number);
            printf("4. Receiver Name: %s\n", database[i].receiver_name);
            printf("5. Receiver Phone Number: %s\n", database[i].receiver_phone_number);
            printf("6. Receiver Address: %s\n", database[i].receiver_address);
            printf("7. Order State: %s\n", database[i].order_state);
            printf("8. Estimated Delivery Time: %s\n", database[i].estimated_delivery_time);
            printf("9. Created At: %s\n", database[i].created_at);
            break;
        }
    }

    if (index == -1)
    {
        printf("Order not found.\n");
        return;
    }

    int choice;
    printf("\nWhat do you want to do?\n");
    printf("1. Edit order\n");
    printf("2. Delete order\n");
    printf("3. Cancel\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("\nOrder Information:\n");
        printf("1. Product Name: %s\n", database[index].product_name);
        printf("2. Sender Name: %s\n", database[index].sender_name);
        printf("3. Sender Phone Number: %s\n", database[index].sender_phone_number);
        printf("4. Receiver Name: %s\n", database[index].receiver_name);
        printf("5. Receiver Phone Number: %s\n", database[index].receiver_phone_number);
        printf("6. Receiver Address: %s\n", database[index].receiver_address);
        printf("7. Order State: %s\n", database[index].order_state);
        printf("8. Estimated Delivery Time: %s\n", database[index].estimated_delivery_time);
        printf("9. Created At: %s\n", database[index].created_at);

        int editChoice;
        printf("\nEnter the number of the information you want to edit (1-8): ");
        scanf("%d", &editChoice);

        switch (editChoice)
        {
        case 1:
            printf("Enter new product name: ");
            scanf(" %[^\n]s", database[index].product_name);
            break;
        case 2:
            printf("Enter new sender name: ");
            scanf(" %[^\n]s", database[index].sender_name);
            break;
        case 3:
            printf("Enter new sender phone number: ");
            scanf(" %[^\n]s", database[index].sender_phone_number);
            break;
        case 4:
            printf("Enter new receiver name: ");
            scanf(" %[^\n]s", database[index].receiver_name);
            break;
        case 5:
            printf("Enter new receiver phone number: ");
            scanf(" %[^\n]s", database[index].receiver_phone_number);
            break;
        case 6:
            printf("Enter new receiver address: ");
            scanf(" %[^\n]s", database[index].receiver_address);
            break;
        case 7:
            printf("Enter new order state (pending/shipping/delivery): ");
            scanf(" %[^\n]s", database[index].order_state);
            break;
        case 8:
            printf("Enter new estimated delivery time (5h, 1d, 1w): ");
            scanf(" %[^\n]s", database[index].estimated_delivery_time);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }

    else if (choice == 2)
    {
        for (int i = index; i < size - 1; i++)
        {
            database[i] = database[i + 1];
        }
        size--;
        memset(&database[size], 0, sizeof(Order));

        printf("Order deleted successfully.\n");
    }
    else
    {
        printf("Cancelled.\n");
    }
    exportDatabase(database, size);
}

void showDatabase(Order database[], int size, const char *filterColumn, const char *filterValue)
{
    Orders result = extractDataFromDatabase(database, size, filterColumn, filterValue, 1);
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
        debug("init database");
        Order database[MAX_ORDERS_AVAILABLE];
        int size = 0;

        User users[100];
        int countUser = 0;
        importUsers(users, &countUser);

        User currentUser = getUserByUsername(users, countUser, session.userName);

        importDatabase(database, &size);
        exportDatabase(database, size);

        char defaultTable;
        if (session.groupId == 1)
            defaultTable = 'a';
        else if (session.groupId == 2)
            defaultTable = 'c';
        else
            defaultTable = 'd';

        char choice = defaultTable;
        char currentTab = defaultTable;
        do
        {
            choice = currentTab;

            system("cls");

            printf("| Current session: %s [%s]\n\n", currentUser.displayName, GROUP_NAME[session.groupId]);
            printf("  [1] Look up/ Search \t [2] Create an order  \t [3] Edit/Delete order \t [0] Log out / Exit\n\n");

            printf("%c (a) Sent %c   %c (b) Receive %c   %c (c) Assigned %c   %c (d) All %c\n",
                   showTabs(choice, 'a'), showTabs(choice, 'a'),
                   showTabs(choice, 'b'), showTabs(choice, 'b'),
                   showTabs(choice, 'c'), showTabs(choice, 'c'),
                   showTabs(choice, 'd'), showTabs(choice, 'd'));

            switch (choice)
            {
            case 'a':
                showDatabase(database, size, "sender_phone_number", currentUser.phoneNumber);
                currentTab = 'a';
                break;
            case 'b':
                showDatabase(database, size, "receiver_phone_number", currentUser.phoneNumber);
                currentTab = 'b';
                break;
            case 'c':

                printf("\n3In development.\n");
                currentTab = 'c';
                break;
            case 'd':
                showDatabase(database, size, "", "");
                currentTab = 'd';
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
                    lookupOrderManager(database, &size);
                }
                else
                {
                    lookupOrderUser(database, &size, currentUser.phoneNumber);
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
                editDeleteOrder(database, size);
                printf("Press [Enter] to continue...");
                getchar();
                break;
            case '0':
                main();
            case 'a':
                currentTab = 'a';
                break;
            case 'b':
                currentTab = 'b';
                break;
            case 'c':
                currentTab = 'c';
                break;
            case 'd':
                currentTab = 'd';
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
            }
            exportDatabase(database, size);
        } while (choice != '0');
    }
}
