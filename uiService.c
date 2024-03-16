void spam_something(char *str, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s", str);
    }
    printf("\n");
}

int compareIdsAsc(const void *a, const void *b)
{
    const Order *orderA = (const Order *)a;
    const Order *orderB = (const Order *)b;
    return orderA->id - orderB->id;
}

int compareIdsDesc(const void *a, const void *b)
{
    const Order *orderA = (const Order *)a;
    const Order *orderB = (const Order *)b;
    return orderB->id - orderA->id;
}

int compareProductNamesAsc(const void *a, const void *b)
{
    const Order *orderA = (const Order *)a;
    const Order *orderB = (const Order *)b;
    return strcmp(orderA->product_name, orderB->product_name);
}

int compareProductNamesDesc(const void *a, const void *b)
{
    const Order *orderA = (const Order *)a;
    const Order *orderB = (const Order *)b;
    return strcmp(orderB->product_name, orderA->product_name);
}

int compareStates(const void *a, const void *b)
{
    const Order *orderA = (const Order *)a;
    const Order *orderB = (const Order *)b;

    if (strcmp(orderA->order_state, orderB->order_state) == 0)
    {
        return orderA->id - orderB->id;
    }
    else if (strcmp(orderA->order_state, "pending") == 0)
    {
        return -1;
    }
    else if (strcmp(orderB->order_state, "pending") == 0)
    {
        return 1;
    }
    else if (strcmp(orderA->order_state, "delivery") == 0)
    {
        return -1;
    }
    else if (strcmp(orderB->order_state, "delivery") == 0)
    {
        return 1;
    }
    else if (strcmp(orderA->order_state, "shipping") == 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void showTable(Orders orders, const char *noOrderMessage)
{

    int size = orders.size;
    char sort_by[100];
    strcpy(sort_by, orders.sort_by);
    Order *database = orders.orders;

    if (size == 0)
    {
        printf("%s\n", noOrderMessage);
        return;
    }

    if (strcmp(sort_by, "Id: low to high") == 0)
    {
        qsort(database, size, sizeof(Order), compareIdsAsc);
    }
    else if (strcmp(sort_by, "Id: high to low") == 0)
    {
        qsort(database, size, sizeof(Order), compareIdsDesc);
    }
    else if (strcmp(sort_by, "Product_name: A-Z") == 0)
    {
        qsort(database, size, sizeof(Order), compareProductNamesAsc);
    }
    else if (strcmp(sort_by, "Product_name: Z-A") == 0)
    {
        qsort(database, size, sizeof(Order), compareProductNamesDesc);
    }
    else
    {
        strcpy(sort_by, "State");
        qsort(database, size, sizeof(Order), compareStates);
    }

    int columnWidths[9] = {3, 8, 5, 7, 8, 12, 17, 17, 10};

    for (int i = 0; i < size; i++)
    {
        int idLength = snprintf(NULL, 0, "%d", database[i].id);
        if (idLength > columnWidths[0])
            columnWidths[0] = idLength;

        if (strlen(database[i].product_name) > columnWidths[1])
            columnWidths[1] = strlen(database[i].product_name);

        if (strlen(database[i].order_state) > columnWidths[2])
            columnWidths[2] = strlen(database[i].order_state);

        if (strlen(database[i].sender_name) > columnWidths[3])
            columnWidths[3] = strlen(database[i].sender_name);

        if (strlen(database[i].receiver_name) > columnWidths[4])
            columnWidths[4] = strlen(database[i].receiver_name);

        if (strlen(database[i].sender_phone_number) > columnWidths[5])
            columnWidths[5] = strlen(database[i].sender_phone_number);

        if (strlen(database[i].receiver_phone_number) > columnWidths[6])
            columnWidths[6] = strlen(database[i].receiver_phone_number);

        if (strlen(database[i].receiver_address) > columnWidths[7])
            columnWidths[7] = strlen(database[i].receiver_address);

        if (strlen(database[i].created_at) > columnWidths[8])
            columnWidths[8] = strlen(database[i].created_at);
    }

    printf("+");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < columnWidths[i] + 2; j++)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    printf("| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           columnWidths[0], "ID", columnWidths[1], "Package", columnWidths[2], "State",
           columnWidths[3], "Sender", columnWidths[4], "Receiver",
           columnWidths[5], "Sender Phone", columnWidths[6], "Receiver Phone",
           columnWidths[7], "Receiver Address", columnWidths[8], "Created");

    printf("+");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < columnWidths[i] + 2; j++)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    for (int i = 0; i < size; i++)
    {
        if (database[i].id == 0)
            continue;
        printf("| %-*d | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
               columnWidths[0], database[i].id,
               columnWidths[1], database[i].product_name,
               columnWidths[2], database[i].order_state,
               columnWidths[3], database[i].sender_name,
               columnWidths[4], database[i].receiver_name,
               columnWidths[5], database[i].sender_phone_number,
               columnWidths[6], database[i].receiver_phone_number,
               columnWidths[7], database[i].receiver_address,
               columnWidths[8], database[i].created_at);

        printf("+");
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < columnWidths[j] + 2; k++)
            {
                printf("-");
            }
            printf("+");
        }
        printf("\n");
    }
    printf("| Sort by: %s [ (s) Change ]\n\n", sort_by);
}

char showTabs(char current, int group_id)
{
    if (group_id > 2)
    {
        switch (current)
        {
        case 'a':
            printf(" __________\n| (a) Sent |   (b) Receive     (c) All orders  ");
            break;
        case 'b':
            printf("              _____________\n  (a) Sent   | (b) Receive |   (c) All orders  ");
            break;
        case 'c':
            printf("                              ________________\n  (a) Sent     (b) Receive   | (c) All orders |");
            break;
        default:
            printf("\n  (a) Sent     (b) Receive     (c) All orders  ");
            break;
        }
    }
    else
    {
        switch (current)
        {
        case 'a':
            printf(" __________\n| (a) Sent |   (b) Receive     ");
            break;
        case 'b':
            printf("              _____________\n  (a) Sent   | (b) Receive |   ");
            break;
        default:
            break;
        }
    }
    printf("\n");
}

int sort_by_choose()
{
    system("cls");
    int choice;
    printf("Sort by:\n");
    printf("1. State\n");
    printf("2. Id: low to high\n");
    printf("3. Id: high to low\n");
    printf("4. Product_name: A-Z\n");
    printf("5. Product_name: Z-A\n");

    do
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 5)
        {
            printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice < 1 || choice > 5);

    return choice;
}

void showMenu(int groupId)
{
    if (groupId > 2)
    {
        printf("+----------------------------------------------------------------------+----------+\n");
        printf("| [1] Look up/ Search  [2] Create an order   [3] Edit/Delete order     | [0] Exit |\n");
        printf("+----------------------------------------------------------------------+----------+\n");
    }
    else
    {
        printf("+-------------------------------------------+----------+\n");
        printf("| [1] Look up/ Search  [2] Create an order  | [0] Exit |\n");
        printf("+-------------------------------------------+----------+\n");
    }
}