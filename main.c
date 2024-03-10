#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 1000

// Define the struct for each Order
typedef struct
{
    int id;
    char product_name[50];
    char order_state[20];
    char sender_name[50];
    char receiver_name[50];
    char receiver_phone_number[20];
    char receiver_address[100];
    char estimated_delivery_time[50];
    char created_at[50];
} Order;

// Function to import the database from a file
void importDatabase(Order database[], int *size)
{
    FILE *file = fopen("database.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    *size = 0;
    while (fscanf(file, "%d %s %s %s %s %s %s %s %s",
                  &database[*size].id,
                  database[*size].product_name,
                  database[*size].order_state,
                  database[*size].sender_name,
                  database[*size].receiver_name,
                  database[*size].receiver_phone_number,
                  database[*size].receiver_address,
                  database[*size].estimated_delivery_time,
                  database[*size].created_at) == 9)
    {
        (*size)++;
    }

    fclose(file);
}

// Function to export the database to a file
void exportDatabase(Order database[], int size)
{
    FILE *file = fopen("database.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d %s %s %s %s %s %s %s %s\n",
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

    fclose(file);
}

void listAllOrders(Order database[], int size)
{
    char formatString[] = "%-5d | %-15s | %-15s | %-15s | %-15s | %-20s | %-30s | %-25s | %-20s\n";
    printf("ID    | Product Name    | Order State     | Sender Name     | Receiver Name   | Receiver Phone       | Receiver Address               | Estimated Delivery Time   | Created At            \n");

    // Sort the orders by ID
    // for (int i = 0; i < size - 1; i++)
    // {
    //     for (int j = 0; j < size - i - 1; j++)
    //     {
    //         if (database[j].id > database[j + 1].id)
    //         {
    //             Order temp = database[j];
    //             database[j] = database[j + 1];
    //             database[j + 1] = temp;
    //         }
    //     }
    // }

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
    getchar();
    getchar();
}
void lookupOrder(Order database[], int size)
{
    int id;
    printf("Enter the ID of the order: ");
    scanf("%d", &id);

    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (database[i].id == id)
        {
            char formatString[] = "%-5d | %-15s | %-15s | %-15s | %-15s | %-20s | %-30s | %-25s | %-20s\n";

            if (count == 0)
            {
                printf("ID    | Product Name    | Order State     | Sender Name     | Receiver Name   | Receiver Phone       | Receiver Address               | Estimated Delivery Time   | Created At            \n");
            }
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
            count += 1;
        }
    }
    if (count == 0)
    {
        printf("Order not found.\n");
    }
    else
    {
        printf("\nFound %d order(s).", count);
    }
}

void createNewOrder(Order database[], int *size)
{

    printf("Enter product name: ");
    scanf("%s", database[*size].product_name);

    printf("Enter sender name: ");
    scanf("%s", database[*size].sender_name);

    printf("Enter receiver name: ");
    scanf("%s", database[*size].receiver_name);

    printf("Enter receiver phone number: ");
    scanf("%s", database[*size].receiver_phone_number);

    printf("Enter receiver address: ");
    scanf("%s", database[*size].receiver_address);

    printf("Enter order state (pending/shipping/delivery): ");
    scanf("%s", database[*size].order_state);

    printf("Enter delivery time (5h, 1d, 1w): ");
    scanf("%s", database[*size].estimated_delivery_time);

    printf("Enter created at: ");
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    strftime(database[(*size)].created_at, sizeof(database[(*size)].created_at), "%Y-%m-%d %H:%M:%S", localTime);

    (*size)++;
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
    printf("Enter your choice (1-2): ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        // Code to edit the order
        // Example:
        printf("Enter product name: ");
        scanf("%s", database[index].product_name);

        printf("Enter order state: ");
        scanf("%s", database[index].order_state);

        printf("Enter sender name: ");
        scanf("%s", database[index].sender_name);

        printf("Enter receiver name: ");
        scanf("%s", database[index].receiver_name);

        printf("Enter receiver phone number: ");
        scanf("%s", database[index].receiver_phone_number);

        printf("Enter receiver address: ");
        scanf("%s", database[index].receiver_address);

        printf("Enter estimated delivery time: ");
        scanf("%s", database[index].estimated_delivery_time);

        printf("Enter created at: ");
        scanf("%s", database[index].created_at);
    }
    else if (choice == 2)
    {
        // Code to delete the order
        for (int i = index; i < size - 1; i++)
        {
            database[i] = database[i + 1];
        }
        size--;
    }
    else
    {
        printf("Invalid choice. Please try again.\n");
    }
}

int main()
{
    Order database[MAX_SIZE];
    int size = 0;

    // Import the database from file
    importDatabase(database, &size);

    // Export the database to file
    exportDatabase(database, size);

    int choice;
    do
    {
        printf("\n\n\n");
        printf("ORDER MANAGEMENT:\n");
        printf("1. List all orders in database\n");
        printf("2. Look up order\n");
        printf("3. Create a new order\n");
        printf("4. Edit/Delete order\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            importDatabase(database, &size);
            listAllOrders(database, size);
            break;
        case 2:
            lookupOrder(database, size);
            break;
        case 3:
            createNewOrder(database, &size);
            break;
        case 4:
            editDeleteOrder(database, size);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

        exportDatabase(database, size);
    } while (choice != 0);

    return 0;
}
