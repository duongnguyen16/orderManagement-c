void lookupOrderUser(Order database[], int size, char phoneNumber[100])
{
    debug("lookupOrder");
    char userInput[100];
    printf("[Search] Enter the ID of order here: ");
    scanf(" %[^\n]s", userInput);

    char filter[100];
    char searchValue[100];
    char rf[100];

    Orders foundOrders = extractDataFromDatabase(database, size, "id", userInput, 1);

    debug("lookupOrder - show all orders found");

    if (foundOrders.size == 0)
    {
        printf("\nOrder not found.\n");
        return;
    }
    else
    {
        Order result = foundOrders.orders[0];
        printf("State: %s\n\n", result.order_state);
        printf("ID: %d\n", result.id);
        printf("Package: %s\n", result.product_name);
        printf("Sender: %s\n", result.sender_name);
        printf("Receiver: %s\n", result.receiver_name);
        printf("Receiver Phone: %s\n", result.receiver_phone_number);
        printf("Receiver Address: %s\n", result.receiver_address);
        printf("Created at: %s\n", result.created_at);
        printf("\n");
    }
}

void createNewOrderUser(Order database[], int *size, User users[], User currentUser, int count)
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

    User getSender = getUserByPhoneNumber(users, count, currentUser.phoneNumber);

    strcpy(temp.sender_phone_number, getSender.phoneNumber);
    printf("Enter sender phone number (auto-filled):\n> %s\n", temp.sender_phone_number);

    strcpy(temp.sender_name, getSender.displayName);
    printf("Enter sender name (auto-filled):\n> %s\n", temp.sender_name);

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
