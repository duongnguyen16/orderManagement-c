#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#include "validation.c"

// typedef struct
// {
//     int id;
//     char userName[50];
//     char displayName[50];
//     int groupId;
//     char password[50];
//     char phoneNumber[20];
//     char address[100];
// } Users;

// typedef struct
// {
//     int id;
//     char userName[50];
//     int groupId;
// } Session;

bool isUsernameExist(const Users *users, int count, const char *username)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(users[i].userName, username) == 0)
        {
            return true;
        }
    }

    return false;
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

Session authenticate(Users *users, int count)
{
    char username[50];
    char password[50];
    printf("> Username: ");
    scanf("%s", username);

    int attempts = 0;
    while (!isUsernameExist(users, count, username))
    {
        printf("Invalid username. Please try again.\n");
        printf("> Username: ");
        scanf("%s", username);
    }

    while (attempts < 3)
    {
        printf("> Password: ");
        scanf("%s", password);

        for (int i = 0; i < count; i++)
        {
            if (strcmp(users[i].userName, username) == 0 && strcmp(users[i].password, password) == 0)
            {
                // Authentication successful, create a session
                Session session;
                session.id = users[i].id;
                strcpy(session.userName, users[i].userName);
                session.groupId = users[i].groupId;
                printf("Authentication successfully! Session: %d %s %d\n", session.id, session.userName, session.groupId);
                return session;
            }
        }

        printf("Incorrect password. Please try again.\n");
        attempts++;
    }

    printf("Authentication failed because maximum attempts exceeded. Exiting...\n");
    exit(1);
}

void registerUser(Users *users, int *count)
{
    char username[50];
    char password[50];
    char displayName[50];
    char phoneNumber[20];
    char address[100];

    while (1)
    {
        printf("> Username: ");
        scanf(" %[^\n]", username);

        // Check if username is valid
        if (!validateUsername(username))
        {
            printf("Invalid username. Please try again.\n");
            continue;
        }

        // Check if username already exists
        if (isUsernameExist(users, *count, username))
        {
            printf("Username already exists. Please try again.\n");
            continue;
        }

        break;
    }

    while (1)
    {
        printf("> Password: ");
        scanf(" %[^\n]", password);

        // Check if password is valid
        if (!validatePassword(password))
        {
            printf("Invalid password. Please try again.\n");
            continue;
        }

        break;
    }

    while (1)
    {
        printf("> Display name: ");
        scanf(" %[^\n]", displayName);

        // Check if display name is valid
        if (!validateDisplayName(displayName))
        {
            printf("Invalid display name. Please try again.\n");
            continue;
        }

        break;
    }

    while (1)
    {
        printf("> Phone number: ");
        scanf(" %[^\n]", phoneNumber);

        // Check if phone number is valid
        if (!validatePhoneNumber(phoneNumber))
        {
            printf("Invalid phone number. Please try again.\n");
            continue;
        }

        break;
    }

    printf("> Address: ");
    scanf(" %[^\n]", address);

    // Generate a unique user ID
    srand(time(NULL));
    int id = rand();

    // Create a new user with default group ID of 1
    Users newUser;
    newUser.id = id;
    strcpy(newUser.userName, username);
    strcpy(newUser.displayName, displayName);
    newUser.groupId = 1;
    strcpy(newUser.password, password);
    strcpy(newUser.phoneNumber, phoneNumber);
    strcpy(newUser.address, address);

    users[*count] = newUser;
    (*count)++;

    printf("User registered successfully.\n");
}
