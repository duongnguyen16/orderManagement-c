#include <stdbool.h>
#include <string.h>

bool validateUsername(const char *username)
{
    // Check for spaces
    if (strchr(username, ' ') != NULL)
    {
        return false;
    }

    // Check for special characters
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
    // Check for spaces
    if (strchr(password, ' ') != NULL)
    {
        return false;
    }

    // Check length
    if (strlen(password) < 6)
    {
        return false;
    }

    return true;
}

bool validatePhoneNumber(const char *phoneNumber)
{
    // Check if all characters are digits
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
    // Check if empty
    if (strlen(displayName) == 0)
    {
        return false;
    }

    return true;
}