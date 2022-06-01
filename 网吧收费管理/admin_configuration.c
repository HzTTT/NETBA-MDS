/*
*函数名称：admin_configuration_menu
*函数功能：管理员配置菜单
*函数参数：无
*函数返回值：无
*/
#include"header.h"
void admin_configuration_menu()
{
    int choice;
    table admin_table={
        .col_num=1,
        .row_num=6,
    };
    char formated_out[2048];

    while (1){

        get_memory(&admin_table);
        admin_table.content[0][0]="管理员配置菜单";
        admin_table.content[1][0]="【1】添加管理员";
        admin_table.content[2][0]="【2】删除管理员";
        admin_table.content[3][0]="【3】修改管理员权限";
        admin_table.content[4][0]="【0】退出系统";
        admin_table.content[5][0]="【-1】返回上一级";

        format_table(&admin_table,formated_out);
        printf("%s",formated_out);
        close_memory(&admin_table);

        
        printf("请选择：");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                admin_add();
                break;
            case 2:
                admin_delete();
                break;
            case 3:
                admin_modify();
                break;
            case -1:
                return;
            case 0:
                exit(0);
                break;
            default:
                printf("输入错误，请重新输入！\n");
                break;
        }
    }
}

//测试用例
/* int main()
{
    admin_configuration_menu();
    return 0;
} */