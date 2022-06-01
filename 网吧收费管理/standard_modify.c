/*
*函数名称：standard_modify
*函数功能：修改计费标准
*函数参数：无
*函数返回值：无
*/
#include"header.h"
void standard_modify()
{
    STANDARD_NODE *p_node = NULL;
    STANDARD_NODE *head_node = standard_get_list();
    int time_length;
    printf("请输入要修改的计费时长：");
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
            printf("请输入新的计费标准：");
            scanf("%f", &p_node->date.fee);
            while (p_node->date.fee < 0) 
            {
                printf("金额不能小于0，请重新输入！\n");
                scanf("%f", &p_node->date.fee);
            }
            standard_save_list(head_node);
            printf("修改成功！\n");
            return;
        }
    }
    printf("该时长不存在\n");
    standard_save_list(head_node);
    return;
}

//测试用例
/* int main()
{
    STANDARD_NODE *head_node = NULL;
    head_node = standard_get_list();
    standard_modify(head_node);
    return 0;
} */