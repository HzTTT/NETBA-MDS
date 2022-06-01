/*
*函数名称 ：card_menu
*函数功能 ：卡管理菜单
*函数参数 ：ADMIN admin 
*函数返回值：无
*/
#include"header.h"
void admin_menu(ADMIN admin)
{
    int choice = 0;
    table table_menu = {
        .col_num = 1,
        .row_num = 8,
    };
    char formated_out[2048];

    do
    {
        get_memory(&table_menu);
        table_menu.content[0][0]="管理员菜单";
        table_menu.content[1][0]="【1】卡管理";
        table_menu.content[2][0]="【2】计费标准管理";
        table_menu.content[3][0]="【3】计费管理";
        table_menu.content[4][0]="【4】费用管理";
        table_menu.content[5][0]="【5】查询管理";
        table_menu.content[6][0]="【0】退出系统";
        table_menu.content[7][0]="【-1】返回上一级";

        format_table(&table_menu, formated_out);
        printf("%s", formated_out);
        close_memory(&table_menu);

        printf("您拥有的权限为：");
        if(admin.is_authority[0] == true)
        {
            printf("【1】卡管理");
        }
        if(admin.is_authority[1] == true)
        {
            printf("【2】计费标准管理");
        }
        if(admin.is_authority[2] == true)
        {
            printf("【3】计费管理");
        }
        if(admin.is_authority[3] == true)
        {
            printf("【4】费用管理");
        }
        if(admin.is_authority[4] == true)
        {
            printf("【5】查询管理");
        }
        printf("\n");

        printf("请选择：");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                if(admin.is_authority[0]==true)
                {
                    card_menu();
                }
                else
                {
                    printf("没有卡管理权限！\n");
                }
                break;
            case 2:
                if(admin.is_authority[1]==true)
                {
                    standard_menu();
                }
                else
                {
                    printf("没有计费标准管理权限！\n");
                }
                break;
            case 3:
                if(admin.is_authority[2]==true)
                {
                    login_logout_menu();
                }
                else
                {
                    printf("没有计费管理权限！\n");
                }
                break;
            case 4:
                if(admin.is_authority[3]==true)
                {
                    fee_menu();
                }
                else
                {
                    printf("没有费用管理权限！\n");
                }
                break;
            case 5:
                if(admin.is_authority[4]==true)
                {
                    query_menu();
                }
                else
                {
                    printf("没有查询管理权限！\n");
                }
                break;
            case 0:
                exit(0);
                break;
            case -1:
                return;
                break;
            default:
                printf("输入错误，请重新输入！\n");
                break;
        }
    } while (1);

}

//测试用例
/* int main()
{
    ADMIN admin=admin_login();
    admin_menu(admin);
    return 0;
} */