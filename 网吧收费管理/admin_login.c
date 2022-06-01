/*
*函数名称：admin_login
*函数功能：管理员登录
*函数参数：无   
*函数返回值：ADMIN * admin
*/
#include "header.h"
ADMIN admin_login()
{
    ADMIN admin;
    ADMIN_NODE *p_node = NULL;
    ADMIN_NODE *head_node = NULL;
    head_node = admin_get_list();

    printf("请输入管理员账号(不大于20个字符)：");
    scanf("%s", admin.number);
    while (strlen(admin.number) > MAX_LENGTH) //判断账号长度
    {
        printf("账号长度超过20个字符，请重新输入！\n");
        scanf("%s", admin.number);
    }

    printf("请输入管理员密码(不大于20个字符)：");
    scanf("%s", admin.password);
    while (strlen(admin.password) > MAX_LENGTH) //判断密码长度
    {
        printf("密码长度超过20个字符，请重新输入！\n");
        scanf("%s", admin.password);
    }

    //判断账号是否存在
    for (p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        if (strcmp(p_node->date.number, admin.number) == 0 && strcmp(p_node->date.password, admin.password) == 0)
        {
            admin=p_node->date;
            admin_save_list(head_node);
            return admin; 
        }
    }
    printf("输入账号密码有误\n");
    printf("登录失败！\n");
    admin_save_list(head_node);
    exit(0);
}


//测试用例
/* int main()
{
    ADMIN *admin = NULL;
    admin = admin_login();
    if (admin != NULL)
    {
        printf("登录成功！\n");
        printf("账号：%s\n", admin->number);
        printf("密码：%s\n", admin->password);
    }
    else
    {
        printf("登录失败！\n");
    }
    return 0;
} */
