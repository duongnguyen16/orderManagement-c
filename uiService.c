void spam_something(char *str, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s", str);
    }
    printf("\n");
}

// the temp_size will not work after release
void showTable(Order database[], int size, const char *noOrderMessage)
{
    // int size = sizeof(database) / sizeof(database[0]);

    if (size == 0)
    {
        printf("%s\n", noOrderMessage);
        return;
    }

    // Calculate column widths
    int columnWidths[9] = {3, 13, 5, 12, 15, 16, 16, 3, 12}; // Initial widths for columns (including ID)
    for (int i = 0; i < size; i++)
    {
        // Update ID width if necessary
        int idLength = snprintf(NULL, 0, "%d", database[i].id);
        if (idLength > columnWidths[0])
            columnWidths[0] = idLength;

        // Update other column widths
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
    }

    // Print table header
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

    // Print table rows
    printf("| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           columnWidths[0], "ID", columnWidths[1], "Product Name", columnWidths[2], "State",
           columnWidths[3], "Sender Name", columnWidths[4], "Receiver Name",
           columnWidths[5], "Receiver Phone", columnWidths[6], "Receiver Address",
           columnWidths[7], "EDT", columnWidths[8], "Created At");

    // Print table separator
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

    // Print table data
    for (int i = 0; i < size; i++)
    {
        printf("| %-*d | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
               columnWidths[0], database[i].id, columnWidths[1], database[i].product_name,
               columnWidths[2], database[i].order_state, columnWidths[3],
               database[i].sender_name, columnWidths[4], database[i].receiver_name,
               columnWidths[5], database[i].receiver_phone_number, columnWidths[6],
               database[i].receiver_address, columnWidths[7], database[i].estimated_delivery_time,
               columnWidths[8], database[i].created_at);
    }

    // Print bottom border
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
}
