import os
import time
from tabulate import tabulate
import subprocess


def read_orders():
    orders = []
    with open('./output/orders.txt', 'r') as file:
        for line in file:
            data = line.strip().split('\t')
            order = {
                'id': int(data[0]),
                'product_name': data[1],
                'order_state': data[2],
                'sender_name': data[3],
                'receiver_name': data[4],
                'receiver_phone_number': data[5],
                'receiver_address': data[6],
                'estimated_delivery_time': data[7],
                'created_at': data[8]
            }
            orders.append(order)
    return orders


def read_users():
    users = []
    with open('./output/users.txt', 'r') as file:
        for line in file:
            data = line.strip().split(':')
            user = {
                'id': int(data[0]),
                'userName': data[1],
                'displayName': data[2],
                'groupId': int(data[3]),
                'password': data[4],
                'phoneNumber': data[5],
                'address': data[6]
            }
            users.append(user)
    return users


def read_groups():
    groups = []
    with open('./output/group.txt', 'r') as file:
        for line in file:
            data = line.strip().split(':')
            group = {
                'id': int(data[0]),
                'name': data[1]
            }
            groups.append(group)
    return groups


def read_permissions():
    permissions = []
    with open('./output/perm.txt', 'r') as file:
        for line in file:
            data = line.strip().split(':')
            permission = {
                'id': int(data[0]),
                'groupId': int(data[1]),
                'perm': data[2]
            }
            permissions.append(permission)
    return permissions


def update_data():
    orders = read_orders()
    users = read_users()
    groups = read_groups()
    permissions = read_permissions()

    orders_last_modified = os.path.getmtime('./output/orders.txt')
    users_last_modified = os.path.getmtime('./output/users.txt')
    groups_last_modified = os.path.getmtime('./output/group.txt')
    permissions_last_modified = os.path.getmtime('./output/perm.txt')

    while True:
        isUpdate = False
        time.sleep(1)

        if os.path.getmtime('./output/orders.txt') > orders_last_modified:
            orders = read_orders()
            print('Orders updated')
            isUpdate = True

            print(tabulate(orders, headers='keys', tablefmt='grid'))
            orders_last_modified = os.path.getmtime(
                './output/orders.txt')

        if os.path.getmtime('./output/users.txt') > users_last_modified:
            users = read_users()
            print('Users updated')
            isUpdate = True
            print(tabulate(users, headers='keys', tablefmt='grid'))
            users_last_modified = os.path.getmtime(
                './output/users.txt')

        if os.path.getmtime('./output/group.txt') > groups_last_modified:
            groups = read_groups()
            print('Groups updated')
            isUpdate = True
            print(tabulate(groups, headers='keys', tablefmt='grid'))
            groups_last_modified = os.path.getmtime(
                './output/group.txt')

        if os.path.getmtime('./output/perm.txt') > permissions_last_modified:
            permissions = read_permissions()
            print('Permissions updated')
            isUpdate = True
            print(tabulate(permissions, headers='keys', tablefmt='grid'))
            permissions_last_modified = os.path.getmtime(
                './output/perm.txt')

        if isUpdate:
            os.system('cls' if os.name == 'nt' else 'clear')

            print('Orders:')
            print(tabulate(orders, headers='keys', tablefmt='grid'))
            print('Users:')
            print(tabulate(users, headers='keys', tablefmt='grid'))
            print('Groups:')
            print(tabulate(groups, headers='keys', tablefmt='grid'))
            print('Permissions:')
            print(tabulate(permissions, headers='keys', tablefmt='grid'))


update_data()
