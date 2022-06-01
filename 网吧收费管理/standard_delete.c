/*
 *函数名称：standard_delete
 *函数功能：删除计费标准
 *函数参数：无
 *函数返回值：无
 */
#include"header.h"
void standard_delete()
{
    STANDARD_NODE *p_node = NULL;
    STANDARD_NODE *q_node = NULL;
    STANDARD_NODE *head_node = standard_get_list();
    int time_length = 0;
    
    printf("请输入要删除的计费时长：");
    scanf("%d", &time_length);
    while(time_length < 0)
    {
        printf("时长不能小于0，请重新输入！\n");
        scanf("%d", &time_length);
    }

    for(p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        if(p_node->date.time_length == time_length)
        {
            if(p_node == head_node)
            {
                head_node = p_node->next;
            }
            else
            {
                q_node->next = p_node->next;
            }
            free(p_node);
            standard_save_list(head_node);
            printf("删除成功！\n");
            return;
        }
        q_node = p_node;
    }
    printf("删除失败！\n");
    standard_save_list(head_node);
    return;
}

//测试用例
/* int main()
{
    STANDARD_NODE *head_node = NULL;
    head_node = standard_get_list();
    standard_delete(head_node);
    return 0;
} */


