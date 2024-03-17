#include <time.h>

void lookupOrderManager(Order database[], int size)
{
    debug("lookupOrder");
    char userInput[100];
    printf("[Search]: ");
    scanf(" %[^\n]s", userInput);

    char filter[100];
    char searchValue[100];
    char rf[100];

    if (strcmp(userInput, "cancel:") == 0)
    {
        printf("Operation canceled.\n");
        return;
    }

    char *filterRunning = strstr(userInput, ":");
    if (filterRunning != NULL)
    {
        *filterRunning = '\0';
        strcpy(filter, userInput);
        strcpy(searchValue, filterRunning + 2);

        printf("Filter: %s - searchValue: %s\n", filter, searchValue);
    }
    else
    {

        for (int option = 1; option <= 7; option++)
        {
            switch (option)
            {
            case 1:
                strcpy(rf, "id");
                break;
            case 2:
                strcpy(rf, "product_name");
                break;
            case 3:
                strcpy(rf, "sender_name");
                break;
            case 4:
                strcpy(rf, "receiver_name");
                break;
            case 5:
                strcpy(rf, "receiver_phone_number");
                break;
            case 6:
                strcpy(rf, "receiver_address");
                break;
            case 7:
                strcpy(rf, "sender_phone_number");
                break;
            default:
                break;
            }

            Orders foundOrders = extractDataFromDatabase(database, size, rf, userInput, 0);

            if (foundOrders.size > 0)
            {
                printf("\nOrders found with filter %s:\n", rf);
                showTable(foundOrders, "No orders found.");
                printf("\n");
            }
        }
        return;
    }

    if (strcmp(filter, "id") == 0)
    {
        strcpy(rf, "id");
    }
    else if (strcmp(filter, "package") == 0)
    {
        strcpy(rf, "product_name");
    }
    else if (strcmp(filter, "sender") == 0)
    {
        strcpy(rf, "sender_name");
    }
    else if (strcmp(filter, "receiver") == 0)
    {
        strcpy(rf, "receiver_name");
    }
    else if (strcmp(filter, "receiver_phone") == 0)
    {
        strcpy(rf, "receiver_phone_number");
    }
    else if (strcmp(filter, "address") == 0)
    {
        strcpy(rf, "receiver_address");
    }
    else if (strcmp(filter, "sender_phone") == 0)
    {
        strcpy(rf, "sender_phone_number");
    }
    else
    {
        printf("Invalid filter.\n");
        return;
    }

    debug("lookupOrder - after filter check");

    Orders foundOrders = extractDataFromDatabase(database, size, rf, searchValue, 0);

    debug("lookupOrder - show all orders found");

    if (foundOrders.size == 0)
    {
        printf("\nOrder not found.\n");
        return;
    }
    else
    {
        showTable(foundOrders, "Orders not found");
        printf("\n");
    }
}

void createNewOrderManager(Order database[], int *size, User users[], User currentUser, int count)
{
    getchar();

    Order temp;
    char confirm;
    debug("Get random ID");
    int id = rand();
    bool ok = false;
    while (ok)
    {
        for (int i = 0; i < size; i++)
        {
            if (database[i].id == id || id == 0)
            {
                id = rand();
                continue;
            }
        }
        ok = true;
    }
    temp.id = id;

    printf("Enter product name:\n> ");
    scanf(" %[^\n]s", temp.product_name);

    printf("Enter sender phone number:\n> ");
    scanf(" %[^\n]s", temp.sender_phone_number);

    User getSender = getUserByPhoneNumber(users, count, temp.sender_phone_number);

    if (getSender.id == -1)
    {
        printf("Enter sender name:\n> ");
        scanf(" %[^\n]s", temp.sender_name);
    }
    else
    {
        strcpy(temp.sender_name, getSender.displayName);
        printf("Enter sender name (auto-filled):\n> %s\n", temp.sender_name);
    }

    printf("Enter receiver phone number:\n> ");
    scanf(" %[^\n]s", temp.receiver_phone_number);

    User getReceiver = getUserByPhoneNumber(users, count, temp.receiver_phone_number);

    if (getReceiver.id == -1)
    {
        printf("Enter receiver name:\n> ");
        scanf(" %[^\n]s", temp.receiver_name);
        printf("Enter receiver address:\n> ");
        scanf(" %[^\n]s", temp.receiver_address);
    }
    else
    {
        strcpy(temp.receiver_name, getReceiver.displayName);
        strcpy(temp.receiver_address, getReceiver.address);
        printf("Enter sender name (auto-filled):\n> %s\n", temp.receiver_name);
        printf("Enter receiver address (auto-filled):\n> %s\n", temp.receiver_address);
    }

    strcpy(temp.order_state, "Pending");

    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    strftime(temp.created_at, sizeof(temp.created_at), "%Y-%m-%d %H:%M:%S", localTime);
    printf("Created at (auto-filled):\n> %s\n\n", temp.created_at);

    debug("Show all information before confirm");

    printf("\n|PLEASE RECHECK THE INFORMATION:\n");
    printf("ID:\n> %d\n", temp.id);
    printf("Product Name:\n> %s\n", temp.product_name);
    printf("Sender Name:\n> %s\n", temp.sender_name);
    printf("Sender Phone Number:\n> %s\n", temp.sender_phone_number);
    printf("Receiver Name:\n> %s\n", temp.receiver_name);
    printf("Receiver Phone Number:\n> %s\n", temp.receiver_phone_number);
    printf("Receiver Address:\n> %s\n", temp.receiver_address);
    printf("Created At:\n> %s\n", temp.created_at);

    printf("\nConfirm? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y')
    {
        database[*size] = temp;
        (*size)++;
        exportDatabase(database, *size);
        printf("Order added successfully.\n");
    }
    else
    {
        printf("Operation canceled.\n");
    }
}

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
            printf("8. Created At: %s\n", database[i].created_at);
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
        printf("8. Created At: %s\n", database[index].created_at);

        int editChoice;
        printf("\nEnter the number of the information you want to edit (1-7): ");
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