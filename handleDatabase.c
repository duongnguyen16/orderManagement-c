#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void importDatabase(Order database[], int *size)
{
    FILE *file = fopen(ORDERS_FILE_NAME, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    *size = 0;
    while (fscanf(file, "%d\t%[^'\t']\t%[^'\t']\t%[^'\t']\t%[^'\t']\t%[^'\t']\t%[^'\t']\t%[^'\t']\t%[^\n]",
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

void exportDatabase(Order database[], int size)
{
    FILE *file = fopen(ORDERS_FILE_NAME, "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
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

Order *extractDataFromDatabase(Order database[], int size, char filter[100], char value[100])
{

    Order *result = malloc(size * sizeof(Order));
    if (result == NULL)
    {

        printf("Memory allocation failed.\n");
        return NULL;
    }

    int count = 0;

    for (int i = 0; i < size; i++)
    {
        int match = 0;

        if (strcmp(filter, "id") == 0 && database[i].id == atoi(value))
        {
            match = 1;
        }
        else if (strcmp(filter, "product_name") == 0 && strstr(database[i].product_name, value) != NULL)
        {
            match = 1;
        }
        else if (strcmp(filter, "order_state") == 0 && strstr(database[i].order_state, value) != NULL)
        {
            match = 1;
        }
        else if (strcmp(filter, "sender_name") == 0 && strstr(database[i].sender_name, value) != NULL)
        {
            match = 1;
        }
        else if (strcmp(filter, "receiver_name") == 0 && strstr(database[i].receiver_name, value) != NULL)
        {
            match = 1;
        }
        else if (strcmp(filter, "receiver_phone_number") == 0 && strstr(database[i].receiver_phone_number, value) != NULL)
        {
            match = 1;
        }
        else if (strcmp(filter, "receiver_address") == 0 && strstr(database[i].receiver_address, value) != NULL)
        {
            match = 1;
        }
        else if (strcmp(filter, "estimated_delivery_time") == 0 && strstr(database[i].estimated_delivery_time, value) != NULL)
        {
            match = 1;
        }
        else if (strcmp(filter, "") == 0 && strcmp(value, "") == 0)
        {
            match = 1;
        }
        if (match)
        {
            result[count] = database[i];
            count++;
        }
    }

    result = realloc(result, count * sizeof(Order));

    return result;
}

void importUsers(Users *users, int *count)
{
    FILE *file = fopen("./users.txt", "r");
    if (file == NULL)
    {
        printf("Failed to open user database.\n");
        exit(1);
    }

    *count = 0;
    while (fscanf(file, "%d:%[^:]:%[^:]:%d:%[^:]:%[^:]:%[^\n]\n", &users[*count].id, users[*count].userName, users[*count].displayName, &users[*count].groupId, users[*count].password, users[*count].phoneNumber, users[*count].address) != EOF)
    {
        (*count)++;
    }

    fclose(file);
}

void exportUsers(Users *users, int count)
{
    FILE *file = fopen("./users.txt", "w");
    if (file == NULL)
    {
        printf("Failed to open user database.\n");
        exit(1);
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d:%s:%s:%d:%s:%s:%s\n", users[i].id, users[i].userName, users[i].displayName, users[i].groupId, users[i].password, users[i].phoneNumber, users[i].address);
    }

    fclose(file);
}
