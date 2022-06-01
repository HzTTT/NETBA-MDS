/*
 *函数名称：super_admin_menu
 *函数功能：超级管理员菜单
 *函数参数：ADMIN super_admin 管理员信息
 *函数返回值：无
 */
#include"header.h"
void super_admin_menu(ADMIN super_admin)
{
    int choice = 0;
    table table_menu = {
        .col_num = 1,
        .row_num = 4,
    };
    char formated_out[2048];

    do
    {
        get_memory(&table_menu);
        table_menu.content[0][0]="超级管理员菜单";
        table_menu.content[1][0]="【1】管理员配置";
        table_menu.content[2][0]="【2】使用所有管理权限";
        table_menu.content[3][0]="【0】退出系统";

        format_table(&table_menu, formated_out);
        printf("%s", formated_out);
        close_memory(&table_menu);

        printf("请选择：");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                admin_configuration_menu();
                break;
            case 2:
                admin_menu(super_admin);
                break;
            case 0:
                printf("退出系统\n");
                exit(0);
                break;
            default:
                printf("输入错误，请重新输入！\n");
                break;

        }
    }while(1);
}

/* int main()
{
    ADMIN super_admin;
    super_admin_menu(super_admin);
    return 0;
} */