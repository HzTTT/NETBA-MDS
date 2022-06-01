/*
*函数名称：fee_menu
*函数功能：费用管理菜单
*函数参数：无
*函数返回值：无
*/
#include"header.h"
void fee_menu()
{
    table T_balance = {
        .row_num = 5,
        .col_num = 1,
    };
    int choice = 0;
    char formated_out[2048];

    do
    {   
        get_memory(&T_balance);
        T_balance.content[0][0]="费用管理菜单";
        T_balance.content[1][0]="【1】充值费用";
        T_balance.content[2][0]="【2】退回费用";
        T_balance.content[3][0]="【0】退出系统";
        T_balance.content[4][0]="【-1】返回上一级";

        format_table(&T_balance, formated_out);
        printf("%s", formated_out);
        close_memory(&T_balance);

        printf("请选择：");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                fee_add();
                break;
            case 2:
                fee_cancel();
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
    fee_menu();
    return 0;
} */