/*
 *函数名称：standard_menu
 *函数功能：计费标准管理菜单
 *函数参数：无
 *函数返回值：无
 */
#include"header.h"
void standard_menu()
{
    int choice = 0;
    table t_standard={
        .col_num=1,
        .row_num=7,
    };
    char formated_out[2048];

    while (1){
        
        get_memory(&t_standard);
        t_standard.content[0][0]="计费标准管理菜单";
        t_standard.content[1][0]="【1】添加新的计费标准";
        t_standard.content[2][0]="【2】删除计费标准";
        t_standard.content[3][0]="【3】修改计费标准";
        t_standard.content[4][0]="【4】查看计费标准";
        t_standard.content[5][0]="【0】退出系统";
        t_standard.content[6][0]="【-1】返回上一级";

        format_table(&t_standard,formated_out);
        printf("%s",formated_out);
        close_memory(&t_standard);

        printf("请选择：");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                standard_add();
                break;
            case 2:
                standard_delete();
                break;
            case 3:
                standard_modify();
                break;
            case 4:
                standard_query();
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

    }
}

//测试用例
/* int main()
{
    standard_menu();
    return 0;
} */