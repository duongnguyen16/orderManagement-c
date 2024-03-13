#include <stdio.h>

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

typedef struct
{
    int id;
    char username[50];
    int group_id;
    char role[50];
} Session;

typedef struct
{
    int id;
    char username[50];
    int group_id;
    char password[50];
} Users;

typedef struct
{
    int id;
    char name[50];
} Group;

typedef struct
{
    int id;
    int group_id;
    char perm[50];
} Permission;

char ORDERS_FILE_NAME[20] = "orders.txt";
char USERS_FILE_NAME[20] = "users.txt";
char GROUPS_FILE_NAME[20] = "groups.txt";
char PERM_FILE_NAME[20] = "perm.txt";
int MAX_ORDERS_AVAILABLE = 5000;
