#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "handleDatabase.c"

void listAllOrders(Order database[], int size)
{
    if (size == 0)
    {
        printf("No orders found.\n");
        return;
    }
    char formatString[] = "%-5d | %-15s | %-15s | %-15s | %-15s | %-20s | %-30s | %-25s | %-20s\n";
    printf("ID    | Product Name    | Order State     | Sender Name     | Receiver Name   | Receiver Phone       | Receiver Address               | Estimated Delivery Time   | Created At            \n");

    for (int i = 0; i < size; i++)
    {
        printf(formatString,
               database[i].id,
               database[i].product_name,
               database[i].order_state,
               database[i].sender_name,
               database[i].receiver_name,
               database[i].receiver_phone_number,
               database[i].receiver_address,
               database[i].estimated_delivery_time,
               database[i].created_at);
    }
}
void lookupOrder(Order database[], int size)
{
    int option;
    printf("Search by:\n");
    printf("1. ID\n");
    printf("2. Product Name\n");
    printf("3. Sender Name\n");
    printf("4. Receiver Name\n");
    printf("5. Receiver Phone Number\n");
    printf("6. Receiver Address\n");
    printf("Enter your choice: ");
    scanf("%d", &option);

    char searchValue[100];
    printf("Enter the search value: ");
    scanf(" %[^\n]s", searchValue);

    int count = 0;
    int matchingIndices[size];
    int matchingIndex = 0;

    for (int i = 0; i < size; i++)
    {
        switch (option)
        {
        case 1:
            if (database[i].id == atoi(searchValue))
            {
                matchingIndices[matchingIndex] = i;
                matchingIndex++;
                count++;
            }
            break;
        case 2:
            if (strstr(database[i].product_name, searchValue) != NULL)
            {
                matchingIndices[matchingIndex] = i;
                matchingIndex++;
                count++;
            }
            break;
        case 3:
            if (strstr(database[i].sender_name, searchValue) != NULL)
            {
                matchingIndices[matchingIndex] = i;
                matchingIndex++;
                count++;
            }
            break;
        case 4:
            if (strstr(database[i].receiver_name, searchValue) != NULL)
            {
                matchingIndices[matchingIndex] = i;
                matchingIndex++;
                count++;
            }
            break;
        case 5:
            if (strstr(database[i].receiver_phone_number, searchValue) != NULL)
            {
                matchingIndices[matchingIndex] = i;
                matchingIndex++;
                count++;
            }
            break;
        case 6:
            if (strstr(database[i].receiver_address, searchValue) != NULL)
            {
                matchingIndices[matchingIndex] = i;
                matchingIndex++;
                count++;
            }
            break;
        default:
            printf("Invalid option.\n");
            return;
        }
    }

    if (count == 0)
    {
        printf("Order not found.\n");
    }
    else
    {
        printf("\nFound %d order(s).\n", count);
        if (count > 0)
        {
            printf("ID    | Product Name    | Order State     | Sender Name     | Receiver Name   | Receiver Phone       | Receiver Address               | Estimated Delivery Time   | Created At            \n");
        }

        for (int i = 0; i < matchingIndex; i++)
        {
            char formatString[] = "%-5d | %-15s | %-15s | %-15s | %-15s | %-20s | %-30s | %-25s | %-20s\n";
            int index = matchingIndices[i];
            printf(formatString,
                   database[index].id,
                   database[index].product_name,
                   database[index].order_state,
                   database[index].sender_name,
                   database[index].receiver_name,
                   database[index].receiver_phone_number,
                   database[index].receiver_address,
                   database[index].estimated_delivery_time,
                   database[index].created_at);
            count += 1;
        }
        printf("\n");
    }
}

void createNewOrder(Order database[], int *size)
{
    getchar();

    Order temp;
    char confirm;

    printf("Enter product name:\n> ");
    scanf(" %[^\n]s", temp.product_name);

    printf("Enter sender name:\n> ");
    scanf(" %[^\n]s", temp.sender_name);

    printf("Enter receiver name:\n> ");
    scanf(" %[^\n]s", temp.receiver_name);

    printf("Enter receiver phone number:\n> ");
    scanf(" %[^\n]s", temp.receiver_phone_number);

    printf("Enter receiver address:\n> ");
    scanf(" %[^\n]s", temp.receiver_address);

    printf("Enter order state:\n");
    int choice;
    printf("1 - Pending\n");
    printf("2 - Shipping\n");
    printf("3 - Delivery\n");
    printf("4 - Completed\nYour choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        strcpy(temp.order_state, "Pending");
        break;
    case 2:
        strcpy(temp.order_state, "Shipping");
        break;
    case 3:
        strcpy(temp.order_state, "Delivery");
        break;
    case 4:
        strcpy(temp.order_state, "Completed");
        break;
    default:
        printf("Invalid option. Setting order state to 'Invalid'.\n");
        strcpy(temp.order_state, "Invalid");
        break;
    }

    printf("Enter delivery time (5h, 1d, 1w):\n> ");
    scanf(" %[^\n]s", temp.estimated_delivery_time);

    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    strftime(temp.created_at, sizeof(temp.created_at), "%Y-%m-%d %H:%M:%S", localTime);
    printf("Created at: %s (AUTO GENERATED)\n", temp.created_at);

    temp.id = database[*size - 1].id + 1;

    printf("\n|PLEASE RECHECK THE INFORMATION:\n");
    printf("ID:\n> %d\n", temp.id);
    printf("Product Name:\n> %s\n", temp.product_name);
    printf("Sender Name:\n> %s\n", temp.sender_name);
    printf("Receiver Name:\n> %s\n", temp.receiver_name);
    printf("Receiver Phone Number:\n> %s\n", temp.receiver_phone_number);
    printf("Receiver Address:\n> %s\n", temp.receiver_address);
    printf("Order State:\n> %s\n", temp.order_state);
    printf("Estimated Delivery Time:\n> %s\n", temp.estimated_delivery_time);
    printf("Created At:\n> %s\n", temp.created_at);

    printf("\nConfirm? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y')
    {

        database[*size] = temp;
        (*size)++;
        printf("Order created successfully.\n");
    }
    else
    {
        printf("Canceled.\n");
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
            char formatString[] = "%-5d | %-15s | %-15s | %-15s | %-15s | %-20s | %-30s | %-25s | %-20s\n";

            printf("ID    | Product Name    | Order State     | Sender Name     | Receiver Name   | Receiver Phone       | Receiver Address               | Estimated Delivery Time   | Created At            \n");
            printf(formatString,
                   database[i].id,
                   database[i].product_name,
                   database[i].order_state,
                   database[i].sender_name,
                   database[i].receiver_name,
                   database[i].receiver_phone_number,
                   database[i].receiver_address,
                   database[i].estimated_delivery_time,
                   database[i].created_at);
            break;
        }
    }

    if (index == -1)
    {
        printf("Order not found.\n");
        return;
    }

    int choice;
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
        printf("3. Receiver Name: %s\n", database[index].receiver_name);
        printf("4. Receiver Phone Number: %s\n", database[index].receiver_phone_number);
        printf("5. Receiver Address: %s\n", database[index].receiver_address);
        printf("6. Order State: %s\n", database[index].order_state);
        printf("7. Estimated Delivery Time: %s\n", database[index].estimated_delivery_time);
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
            printf("Enter new receiver name: ");
            scanf(" %[^\n]s", database[index].receiver_name);
            break;
        case 4:
            printf("Enter new receiver phone number: ");
            scanf(" %[^\n]s", database[index].receiver_phone_number);
            break;
        case 5:
            printf("Enter new receiver address: ");
            scanf(" %[^\n]s", database[index].receiver_address);
            break;
        case 6:
            printf("Enter new order state (pending/shipping/delivery): ");
            scanf(" %[^\n]s", database[index].order_state);
            break;
        case 7:
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
        printf("Cancelled.1\n");
    }
    exportDatabase(database, size);
}

void deleteAllData(Order database[], int *size)
{
    *size = 0;
    exportDatabase(database, *size);
    printf("All data has been erased.\n");
}

int main()
{
    Order database[MAX_ORDERS_AVAILABLE];
    int size = 0;

    importDatabase(database, &size);
    exportDatabase(database, size);

    int choice;
    do
    {
        system("cls");
        printf("\n\n\n");
        printf("ORDER MANAGEMENT:\n");
        printf("1. List all orders in database\n");
        printf("2. Look up order\n");
        printf("3. Create a new order\n");
        printf("4. Edit/Delete order\n");
        printf("5. Erase all data (Danger)\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            system("cls");
            importDatabase(database, &size);
            listAllOrders(database, size);
            getchar();
            printf("Press [Enter] to continue...");
            getchar();
            break;
        case 2:
            system("cls");
            lookupOrder(database, size);
            getchar();
            printf("\nPress [Enter] to continue...");
            getchar();
            break;
        case 3:
            system("cls");
            createNewOrder(database, &size);
            getchar();
            getchar();
            printf("Press [Enter] to continue...");
            getchar();
            break;
        case 4:
            system("cls");
            editDeleteOrder(database, size);
            getchar();
            printf("Press [Enter] to continue...");
            getchar();
            break;
        case 5:
            system("cls");
            deleteAllData(database, &size);
            getchar();
            printf("Press [Enter] to continue...");
            getchar();
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

        exportDatabase(database, size);
    } while (choice != 0);

    return 0;
}
