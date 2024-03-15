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

    char *filterColon = strstr(userInput, ":");
    if (filterColon != NULL)
    {
        *filterColon = '\0';
        strcpy(filter, userInput);
        strcpy(searchValue, filterColon + 2);

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
            if (database[i].id == id)
            {
                id = rand();
                continue;
                printf("ID: %d already exists. Generating new ID...\n", id);
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

    printf("Enter delivery time (5h, 1d, 1w):\n> ");
    scanf(" %[^\n]s", temp.estimated_delivery_time);

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
    printf("Estimated Delivery Time:\n> %s\n", temp.estimated_delivery_time);
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
