/*
*函数名称：standard_add
*函数功能：添加计费标准
*函数参数：无
*函数返回值：无
*/
#include"header.h"
void standard_add()
{
    STANDARD_NODE *new_node = NULL;
    STANDARD_NODE *p_node = NULL;
    STANDARD_NODE *head_node = standard_get_list();
    STANDARD standard = {
        .fee = 0,
        .time_length = 0,
    };

    printf("请输入计费时长（单位小时）：");
    scanf("%d", &standard.time_length);
    while (standard.time_length < 0) 
    {
        printf("时长不能小于0，请重新输入！\n");
        scanf("%d", &standard.time_length);
    }
    while (standard_check_repeat(head_node, standard.time_length))
    {
        printf("该时长已存在，请重新输入！\n");
        scanf("%d", &standard.time_length);
    }

    printf("请输入计费金额(单位元）：");
    scanf("%f", &standard.fee);
    while (standard.fee < 0) 
    {
        printf("金额不能小于0，请重新输入！\n");
        scanf("%f", &standard.fee);
    }

    if((new_node = (STANDARD_NODE *)malloc(sizeof(STANDARD_NODE))) == NULL)
    {
        printf("内存分配失败！\n");
        exit(1);
    }
    
    new_node->date = standard;
    new_node->next = NULL;
    if(head_node == NULL)
    {
        head_node = new_node;
    }
    else
    {
        p_node = head_node;
        while(p_node->next != NULL)
        {
            p_node = p_node->next;
        }
        p_node->next = new_node;
    }
    standard_save_list(head_node);
    printf("新的计费标准添加成功！\n");
}

//测试用例
/* int main()
{
    STANDARD_NODE *head_node = NULL;
    head_node = standard_get_list();
    standard_add(head_node);
    return 0;
} */

