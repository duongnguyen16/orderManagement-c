#include <stdbool.h>
#include <string.h>

bool validateUsername(const char *username)
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

bool validatePassword(const char *password)
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

bool validatePhoneNumber(const char *phoneNumber)
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

bool validateDisplayName(const char *displayName)
{

    if (strlen(displayName) == 0)
    {
        return false;
    }

    return true;
}