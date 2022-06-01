/*
 *函数名称：card_menu
 *函数功能：卡管理菜单
 *函数参数：无
 *函数返回值：无
 */
#include"header.h"
void card_menu()
{
    int choice = 0;
    table table_menu = {
        .col_num = 1,
        .row_num = 6,
    };
    char formated_out[2048];
    
    do{
        get_memory(&table_menu);
        table_menu.content[0][0]="卡管理菜单";
        table_menu.content[1][0]="【1】添加卡";
        table_menu.content[2][0]="【2】查询卡";
        table_menu.content[3][0]="【3】注销卡";
        table_menu.content[4][0]="【0】退出系统";
        table_menu.content[5][0]="【-1】返回上一级";

        format_table(&table_menu, formated_out);
        printf("%s", formated_out);
        close_memory(&table_menu);


        printf("请选择：");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                card_add();
                break;
            case 2:
                card_query();
                break;
            case 3:
                card_cancel();
                break;
            case 0:
                printf("系统退出成功！\n");
                exit(0);
                break;
            case -1:
                return;
                break;
            default:
                printf("输入错误，请重新输入！\n");
                break;
        }       
    }while(1);
}
//测试用例
/* int main()
{
    card_menu();
    return 0;
} */