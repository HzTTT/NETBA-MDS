#include"header.h"
int main()
{
    ADMIN admin;

    admin=admin_login();
    system("clear");

    if(admin.is_super_admin==true)
    {
        super_admin_menu(admin);
        system("clear");
    }
    else
    {
        admin_menu(admin);
        system("clear");
    }
    return 0;
}