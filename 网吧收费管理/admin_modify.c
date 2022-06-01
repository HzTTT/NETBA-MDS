/*
*函数名称：admin_modify
*函数功能：配置管理员权限
*函数参数：ADMIN_NODE *head_node
*函数返回值：无
*/
#include "header.h"
void admin_modify()
{
    ADMIN_NODE *p_node = NULL;
    ADMIN_NODE *head_node = admin_get_list();
    BOOL is_target = false;
    BOOL is_open;
    table T_ADMIN={
        .col_num=1,
        .row_num=7,
    };
    char formated_out[2048];
    
    int choice;
    char admin_number[MAX_LENGTH];
    char admin_password[MAX_LENGTH];

    printf("请输入的管理员账号(不大于20个字符)：");
    scanf("%s", admin_number);
    while (admin_check_repeat(head_node, admin_number) == false) //判断账号长度
    {
        printf("账号不存在，请重新输入！\n");
        scanf("%s", admin_number);
    }

    printf("请输入的管理员密码(不大于20个字符)：");
    scanf("%s", admin_password);
    while (strlen(admin_password) > MAX_LENGTH) //判断密码长度
    {
        printf("密码长度超过20个字符，请重新输入！\n");
        scanf("%s", admin_password);
    }

    for (p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        if (strcmp(p_node->date.number, admin_number) == 0 && strcmp(p_node->date.password, admin_password) == 0)
        {
            if(p_node->date.is_super_admin== true)
            {
                printf("超级管理员不能被修改！\n");
                return;
            }
       
            is_target = true;
            break;
        }
    }

    if (is_target)
    {
        get_memory(&T_ADMIN);
        T_ADMIN.content[0][0] = "管理员权限修改菜单";
        T_ADMIN.content[1][0] = "【1】卡管理权限";
        T_ADMIN.content[2][0] = "【2】计费标准管理权限";
        T_ADMIN.content[3][0] = "【3】计费管理权限";
        T_ADMIN.content[4][0] = "【4】费用管理权限";
        T_ADMIN.content[5][0] = "【5】查询统计权限";
        T_ADMIN.content[6][0] = "【0】权限修改完成";

        format_table(&T_ADMIN, formated_out);
        printf("%s", formated_out);
        close_memory(&T_ADMIN);

        do
        {   
            printf("请选择：");
            scanf("%d", &choice);
            if (choice != 0)
            {
                printf("开启请按【1】，关闭请按【0】：");
                scanf("%d", &is_open);
                while (is_open != 0 && is_open != 1)
                {
                    printf("输入错误，请重新输入！\n");
                    printf("开启请按【1】，关闭请按【0】：");
                    scanf("%d", &is_open);
                }
            }
            switch (choice)
            {
            case 1:
                p_node->date.is_authority[CARD_CONFIGURATION_AUTHORITY] = is_open;
                printf("【卡管理】权限修改完成\n");
                break;
            case 2:
                p_node->date.is_authority[CHARGE_STANDARD_CONFIGURATION_AUTHORITY] = is_open;
                printf("【计费标准管理】权限修改完成\n");
                break;
            case 3:
                p_node->date.is_authority[BILLING_AUTHORITY] = is_open;
                printf("【计费管理】权限修改完成\n");
                break;
            case 4:
                p_node->date.is_authority[FEE_AUTHORITY] = is_open;
                printf("【费用管理】权限修改完成\n");
                break;
            case 5:
                p_node->date.is_authority[QUERY_STATISTICS_AUTHORITY] = is_open;
                printf("【查询统计】权限修改完成\n");
                break;
            case 0:
                printf("授权完成\n");
                break;
            default:
                printf("输入错误，请重新输入！\n");
                break;
            }
        } while (choice != 0);
        admin_save_list(head_node);
        return;
    }
    else
    {
        printf("账号或密码错误\n");
    }
    admin_save_list(head_node);
    return;
}

//测试用例
/* int main()
{
    ADMIN_NODE *head_node = NULL;
    head_node = admin_get_list();
    admin_modify(head_node);
    return 0;
} */