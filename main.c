#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct
{
    int id;
    char product_name[50];
    char order_state[20];
    char sender_name[50];
    char sender_phone_number[20];
    char receiver_name[50];
    char receiver_phone_number[20];
    char receiver_address[100];
    char created_at[50];
} Order;

typedef struct
{
    int size;
    char sort_by[100];
    Order orders[400];
} Orders;

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
} User;

char GROUP_NAME[][50] = {"Invalid", "Customer", "Shipper", "Manager", "Admin", ""};

char ORDERS_FILE_NAME[20] = "orders.txt";
char USERS_FILE_NAME[20] = "users.txt";

int MAX_ORDERS_AVAILABLE = 1000;

#include "uiService.c"
#include "handleDatabase.c"
#include "authService.c"
#include "orderService.c"
#include "managerController.c"
#include "userController.c"

int main()
{
    srand(time(NULL));
    Session session;
    system("cls");

    User users[100];
    int count = 0;
    importUsers(users, &count);

    int choice;
    printf("Welcome to Delivery Management System!\n");
    printf("First, we need to know your identity: \n");
    printf("[1] Login\n");
    printf("[2] Register\n");
    printf("> Enter: ");
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
        main();
        break;

    default:
        printf("Invalid choice.\n");
        exportUsers(users, count);
        main();
        break;
    }

    order_management_main(session);
    return 0;
}
