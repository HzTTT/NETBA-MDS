/*
*函数名称：admin_add
*函数功能：添加管理员
*函数参数：ADMIN_NODE *head_node
*函数返回值：无
*/
#include "header.h"
void admin_add()
{
    int choice;            //选择
    ADMIN_NODE *new_admin = NULL;
    ADMIN_NODE *p_node = NULL;
    ADMIN_NODE *head_node = admin_get_list();
    ADMIN admin={
        .number = "",
        .password = "",
        .is_authority = {false, false, false, false, false},
        .is_super_admin = false
    };
    table T_ADMIN={
        .col_num=1,
        .row_num=7,
    };
    char formated_out[2048];

    printf("请输入管理员账号(不大于20个字符)：");
    scanf("%s", admin.number);
    while (strlen(admin.number) > MAX_LENGTH || admin_check_repeat(head_node,admin.number) == true)           //判断账号长度
    {
        if(strlen(admin.number) > MAX_LENGTH)
        {
            printf("账号长度超过20个字符，请重新输入！\n");
        }
        else
        {
            printf("账号已存在，请重新输入！\n");
        }
        scanf("%s", admin.number);
    }

    printf("请输入管理员密码(不大于20个字符)：");           
    scanf("%s", admin.password);
    while (strlen(admin.password) > MAX_LENGTH)         //判断密码长度
    {
        printf("密码长度超过20个字符，请重新输入！\n");
        scanf("%s", admin.password);
    }

    get_memory(&T_ADMIN);
    T_ADMIN.content[0][0] = "管理员权限配置菜单";
    T_ADMIN.content[1][0] = "【1】卡管理权限";
    T_ADMIN.content[2][0] = "【2】计费标准管理权限";
    T_ADMIN.content[3][0] = "【3】计费管理权限";
    T_ADMIN.content[4][0] = "【4】费用管理权限";
    T_ADMIN.content[5][0] = "【5】查询统计权限";
    T_ADMIN.content[6][0] = "【0】授权完成";

    format_table(&T_ADMIN, formated_out);
    printf("%s", formated_out);
    close_memory(&T_ADMIN);

    do
    {
        printf("请选择：");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            admin.is_authority[CARD_CONFIGURATION_AUTHORITY] = true;
            printf("【卡管理】权限已授权\n");
            break;
        case 2:
            admin.is_authority[CHARGE_STANDARD_CONFIGURATION_AUTHORITY] = true;
            printf("【计费标准管理】权限已授权\n");
            break;
        case 3:
            admin.is_authority[BILLING_AUTHORITY] = true;
            printf("【计费管理】权限已授权\n");
            break;
        case 4:
            admin.is_authority[FEE_AUTHORITY] = true;
            printf("【费用管理】权限已授权\n");
            break;
        case 5:
            admin.is_authority[QUERY_STATISTICS_AUTHORITY] = true;
            printf("【查询统计】权限已授权\n");
            break;
        case 0:
            printf("授权完成\n");
            break;
        default:
            printf("输入错误，请重新输入！\n");
            break;
        }
    } 
    while (choice!= 0);

    if((new_admin=malloc(sizeof(ADMIN_NODE))) == NULL){
        printf("内存分配失败！\n");
        exit(1);
    }

    new_admin->date = admin;            
    new_admin->next = NULL;

    if(head_node == NULL){
        head_node = new_admin;
    }
    else{
        p_node = head_node;
        while(p_node->next != NULL){    //找到最后一个节点
            p_node = p_node->next;
        }
        p_node->next = new_admin;       //插入到链表的最后
    }

    admin_save_list(head_node);         //保存管理员数据链表
}

//测试用
/* int main()
{
    ADMIN_NODE *head = NULL;
    head = admin_get_list();
    admin_add();
    return 0;
} */
