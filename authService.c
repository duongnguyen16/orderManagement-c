#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#include "validateService.c"

bool isUsernameExist(const User *users, int count, const char *username)
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

Session authenticate(User *users, int count)
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

void registerUser(User *users, int *count)
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

        if (!validateUsername(username))
        {
            printf("Invalid username. Please try again.\n");
            continue;
        }

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

        if (!validatePhoneNumber(phoneNumber))
        {
            printf("Invalid phone number. Please try again.\n");
            continue;
        }

        break;
    }

    printf("> Address: ");
    scanf(" %[^\n]", address);
    int id = rand();

    User newUser;
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
