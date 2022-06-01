/*
*函数名称：standard_query
*函数功能：查询计费标准
*函数参数：无
*函数返回值：无
*/
#include"header.h"
void standard_query()
{
    STANDARD_NODE *p_node = NULL;
    STANDARD_NODE *head_node = standard_get_list();
    int time_length = 0;

    printf("请输入要查询的时长：");
    scanf("%d", &time_length);
    while (time_length < 0) 
    {
        printf("时长不能小于0，请重新输入！\n");
        scanf("%d", &time_length);
    }

    for(p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        if(p_node->date.time_length == time_length)
        {
            printf("%d小时计费标准为：%.2f元\n", p_node->date.time_length, p_node->date.fee);
            standard_save_list(head_node);
            return;
        }
    }
    printf("查询失败，该时长不存在！\n");
    return;
}

//测试用例
/* int main()
{
    STANDARD_NODE *head_node = NULL;
    head_node = standard_get_list();
    standard_query(head_node);
    return 0;
} */