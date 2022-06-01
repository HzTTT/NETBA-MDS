/*
*函数名称：admin_delete
*函数功能：删除管理员
*函数参数：ADMIN_NODE *head_node
*函数返回值：无
*/
#include"header.h"
void admin_delete()
{
    ADMIN_NODE *p_node = NULL;
    ADMIN_NODE *q_node = NULL;
    ADMIN_NODE *head_node = admin_get_list();
    char admin_number[MAX_LENGTH];
    char admin_password[MAX_LENGTH];

    printf("请输入删除的管理员账号(不大于20个字符)：");
    scanf("%s", admin_number);
    while (strlen(admin_number) > MAX_LENGTH) //判断账号长度
    {
        printf("账号长度超过20个字符，请重新输入！\n");
        scanf("%s", admin_number);
    }

    printf("请输入删除的管理员密码(不大于20个字符)：");
    scanf("%s", admin_password);
    while (strlen(admin_password) > MAX_LENGTH) //判断密码长度
    {
        printf("密码长度超过20个字符，请重新输入！\n");
        scanf("%s", admin_password);
    }

    for(p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        if(strcmp(p_node->date.number, admin_number) == 0 && strcmp(p_node->date.password, admin_password) == 0)
        {
            if(p_node == head_node)     
            {
                head_node = p_node->next;
            }                   //删除头节点
            else
            {
                q_node->next = p_node->next;
            }                  //删除中间节点或尾巴节点
            free(p_node);
            admin_save_list(head_node);
            printf("删除成功！\n");
            return;
        }

        q_node = p_node;
    }
    printf("输入账号密码有误\n");
    printf("删除失败！\n");
    admin_save_list(head_node);
}

//测试用例
/* int main()
{
    ADMIN_NODE *head_node = NULL;
    head_node = admin_get_list();
    admin_delete(head_node);
    return 0;
} */