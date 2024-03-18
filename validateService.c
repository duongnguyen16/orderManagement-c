#include <stdbool.h>
#include <string.h>

bool validateUsername(char *username)
{

    if (strchr(username, ' ') != NULL)
    {
        return false;
    }

    for (int i = 0; i < strlen(username); i++)
    {
        if (!isalnum(username[i]))
        {
            return false;
        }
    }

    return true;
}

bool validatePassword(char *password)
{

    if (strchr(password, ' ') != NULL)
    {
        return false;
    }

    if (strlen(password) < 6)
    {
        return false;
    }

    return true;
}

bool validatePhoneNumber(char *phoneNumber)
{

    for (int i = 0; i < strlen(phoneNumber); i++)
    {
        if (!isdigit(phoneNumber[i]))
        {
            return false;
        }
    }

    return true;
}

bool validateDisplayName(char *displayName)
{

    if (strlen(displayName) == 0)
    {
        return false;
    }

    return true;
}