#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    char userName[50];
    int groupId;
} Session;

typedef struct
{
    int id;
    char userName[50];
    char displayName[50];
    int groupId;
    char password[50];
    char phoneNumber[20];
    char address[100];
} Users;

typedef struct
{
    int id;
    int groupId;
    char perm[50];
} Permission;

char GROUP_NAME[][50] = {"Customer", "Shipper", "Manager", "Admin"};

char ORDERS_FILE_NAME[20] = "orders.txt";
char USERS_FILE_NAME[20] = "users.txt";
char GROUPS_FILE_NAME[20] = "groups.txt";
char PERM_FILE_NAME[20] = "perm.txt";
int MAX_ORDERS_AVAILABLE = 5000;

#include "handleDatabase.c"
#include "authService.c"
#include "orderService.c"
#include "uiService.c"
#include "customerService.c"
#include "shipperService.c"
#include "managerService.c"
#include "adminService.c"

int main()
{
    Session session;
    Users users[100];
    int count = 0;

    importUsers(users, &count);

    int choice;
    printf("Welcome to Delivery Management System!\n");
    printf("First, we need to know your identification:\n");
    printf("[1] Login\n");
    printf("[2] Register\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        session = authenticate(users, count);
        exportUsers(users, count);
        break;

    case 2:
        registerUser(users, &count);
        exportUsers(users, count);
        break;

    default:
        printf("Invalid choice.\n");
        exportUsers(users, count);
        break;
    }

    order_management_main(session);
    return 0;
}
