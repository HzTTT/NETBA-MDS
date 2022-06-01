/*
*函数名称：get_super_admin
*函数功能：获取超级管理员
*函数参数：无
*函数返回值：无
*/
#include"header.h"
void get_super_admin()
{
    ADMIN admin={
        .is_authority={true,true,true,true,true},
        .is_super_admin=true,
    };
    ADMIN_NODE *head_node=admin_get_list();
    ADMIN_NODE *p_node=head_node;
    printf("请输入管理员账号(不大于20个字符)：");
    scanf("%s",admin.number);

    printf("请输入管理员密码(不大于20个字符)：");
    scanf("%s",admin.password);
    if(p_node==NULL)
    {
        head_node=(ADMIN_NODE*)malloc(sizeof(ADMIN_NODE));
        head_node->date=admin;
        head_node->next=NULL;
    }
    else
    {
        while(p_node->next!=NULL)
        {
            p_node=p_node->next;
        }
        p_node->next=(ADMIN_NODE*)malloc(sizeof(ADMIN_NODE));
        p_node->next->date=admin;
        p_node->next->next=NULL;
    }
    admin_save_list(head_node);
}

//测试用例
/* int main()
{
    get_super_admin();
    return 0;
} */