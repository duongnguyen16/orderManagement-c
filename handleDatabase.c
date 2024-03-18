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
                  database[*size].sender_phone_number,
                  database[*size].receiver_name,
                  database[*size].receiver_phone_number,
                  database[*size].receiver_address,
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
                database[i].sender_phone_number,
                database[i].receiver_name,
                database[i].receiver_phone_number,
                database[i].receiver_address,
                database[i].created_at);
    }

    fclose(file);
    
}

Orders extractDataFromDatabase(Order database[], int size, char filter[100], char value[100], int exactly)
{
    
    Orders result;
    result.size = 0;

    for (int i = 0; i < size; i++)
    {
        int match = 0;

        if (strcmp(filter, "") == 0 && strcmp(value, "") == 0)
        {
            match = 1;
        }
        else if (strcmp(filter, "id") == 0 && database[i].id == atoi(value))
        {
            match = 1;
        }
        else if (strcmp(filter, "product_name") == 0)
        {
            if (exactly)
            {
                if (strcmp(database[i].product_name, value) == 0)
                    match = 1;
            }
            else
            {
                if (strstr(database[i].product_name, value) != NULL)
                    match = 1;
            }
        }
        else if (strcmp(filter, "order_state") == 0)
        {
            if (exactly)
            {
                if (strcmp(database[i].order_state, value) == 0)
                    match = 1;
            }
            else
            {
                if (strstr(database[i].order_state, value) != NULL)
                    match = 1;
            }
        }
        else if (strcmp(filter, "sender_name") == 0)
        {
            if (exactly)
            {
                if (strcmp(database[i].sender_name, value) == 0)
                    match = 1;
            }
            else
            {
                if (strstr(database[i].sender_name, value) != NULL)
                    match = 1;
            }
        }
        else if (strcmp(filter, "sender_phone_number") == 0)
        {
            if (exactly)
            {
                if (strcmp(database[i].sender_phone_number, value) == 0)
                    match = 1;
            }
            else
            {
                if (strstr(database[i].sender_phone_number, value) != NULL)
                    match = 1;
            }
        }
        else if (strcmp(filter, "receiver_name") == 0)
        {
            if (exactly)
            {
                if (strcmp(database[i].receiver_name, value) == 0)
                    match = 1;
            }
            else
            {
                if (strstr(database[i].receiver_name, value) != NULL)
                    match = 1;
            }
        }
        else if (strcmp(filter, "receiver_phone_number") == 0)
        {
            if (exactly)
            {
                if (strcmp(database[i].receiver_phone_number, value) == 0)
                    match = 1;
            }
            else
            {
                if (strstr(database[i].receiver_phone_number, value) != NULL)
                    match = 1;
            }
        }
        else if (strcmp(filter, "receiver_address") == 0)
        {
            if (exactly)
            {
                if (strcmp(database[i].receiver_address, value) == 0)
                    match = 1;
            }
            else
            {
                if (strstr(database[i].receiver_address, value) != NULL)
                    match = 1;
            }
        }

        if (match)
        {
            result.orders[result.size] = database[i];
            result.size++;
        }
    }

    
    return result;
}

void importUsers(User *users, int *count)
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

void exportUsers(User *users, int count)
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

User getUserByUsername(User *users, int count, char *username)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(users[i].userName, username) == 0)
        {
            User user;
            user.id = users[i].id;
            strcpy(user.userName, users[i].userName);
            strcpy(user.displayName, users[i].displayName);
            user.groupId = users[i].groupId;
            strcpy(user.password, users[i].password);
            strcpy(user.phoneNumber, users[i].phoneNumber);
            strcpy(user.address, users[i].address);
            return user;
        }
    }

    User user;
    user.id = -1;
    return user;
}

User getUserByPhoneNumber(User *users, int count, char *phoneNumber)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(users[i].phoneNumber, phoneNumber) == 0)
        {
            User user;
            user.id = users[i].id;
            strcpy(user.userName, users[i].userName);
            strcpy(user.displayName, users[i].displayName);
            user.groupId = users[i].groupId;
            strcpy(user.password, users[i].password);
            strcpy(user.phoneNumber, users[i].phoneNumber);
            strcpy(user.address, users[i].address);
            
            return user;
        }
    }
    
    User user;
    user.id = -1;
    return user;
}

int isIdValid(Order database[], int size, int id)
{
    for (int i = 0; i < size; i++)
    {
        if (database[i].id == id)
        {
            return 1;
        }
    }
    return 0;
}

void addOrder(Order database[], int *size, Order newOrder)
{
    database[*size] = newOrder;
    (*size)++;
}