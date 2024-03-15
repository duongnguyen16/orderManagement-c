void spam_something(char *str, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s", str);
    }
    printf("\n");
}

void showTable(Orders orders, const char *noOrderMessage)
{
    int size = orders.size;
    Order *database = orders.orders;

    if (size == 0)
    {
        printf("%s\n", noOrderMessage);
        return;
    }

    int columnWidths[10] = {3, 13, 12, 12, 15, 18, 18, 18, 6, 19};

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
        if (strlen(database[i].receiver_phone_number) > columnWidths[5])
            columnWidths[5] = strlen(database[i].receiver_phone_number);
        if (strlen(database[i].receiver_address) > columnWidths[6])
            columnWidths[6] = strlen(database[i].receiver_address);
        if (strlen(database[i].estimated_delivery_time) > columnWidths[7])
            columnWidths[7] = strlen(database[i].estimated_delivery_time);
        if (strlen(database[i].created_at) > columnWidths[8])
            columnWidths[8] = strlen(database[i].created_at);
        if (strlen(database[i].sender_phone_number) > columnWidths[9])
            columnWidths[9] = strlen(database[i].sender_phone_number);
    }

    printf("+");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < columnWidths[i] + 2; j++)
        {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    printf("| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           columnWidths[0], "ID", columnWidths[1], "Package", columnWidths[2], "State",
           columnWidths[3], "Sender", columnWidths[4], "Receiver",
           columnWidths[9], "Sender Phone", columnWidths[5], "Receiver Phone",
           columnWidths[6], "Receiver Address", columnWidths[7], "EDT",
           columnWidths[8], "Created");

    printf("+");
    for (int i = 0; i < 10; i++)
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
        printf("| %-*d | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
               columnWidths[0], database[i].id,
               columnWidths[1], database[i].product_name,
               columnWidths[2], database[i].order_state,
               columnWidths[3], database[i].sender_name,
               columnWidths[4], database[i].receiver_name,
               columnWidths[9], database[i].sender_phone_number,
               columnWidths[5], database[i].receiver_phone_number,
               columnWidths[6], database[i].receiver_address,
               columnWidths[7], database[i].estimated_delivery_time,
               columnWidths[8], database[i].created_at);

        printf("+");
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < columnWidths[j] + 2; k++)
            {
                printf("-");
            }
            printf("+");
        }
        printf("\n");
    }
}

char showTabs(char tab, char current)
{
    if (tab == current)
        return '|';
    else
        return ' ';
}
