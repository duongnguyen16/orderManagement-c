
void route(Session session)
{
    int group_id = session.groupId;
    char group_name[100] = GROUP_NAME[group_id];
    if (group_id == 1)
    {
        routeCustomer(session);
    }
    else if (group_id == 2)
    {
        routeShipper(session);
    }
    else if (group_id == 3)
    {
        routeManager(session);
    }
    else if (group_id == 4)
    {
        routeAdmin(session);
    }
    else
    {
        printf("Invalid group name: %s\n", group_name);
    }
}