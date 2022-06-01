/*
 *函数名称：login_logout_menu
 *函数功能：收费菜单
 *函数参数：无
 *函数返回值：无
 */
#include"header.h"
void login_logout_menu()
{
    table T_log = {
        .row_num = 5,
        .col_num = 1,
    };
    int choice = 0;
    char formated_out[2048];

    do
    {
        get_memory(&T_log);
        T_log.content[0][0]="计费管理菜单";
        T_log.content[1][0]="【1】上机";
        T_log.content[2][0]="【2】下机";
        T_log.content[3][0]="【0】退出系统";
        T_log.content[4][0]="【-1】返回上一级";

        format_table(&T_log, formated_out);
        printf("%s", formated_out);
        close_memory(&T_log);

        printf("请选择：");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                login_card();
                break;
            case 2:
                logout_card();
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
    login_logout_menu();
    return 0;
} */
