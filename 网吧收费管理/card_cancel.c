/*
*函数名称：card_check_repeat
*函数功能：检查卡号是否重复
*函数参数：head_node：链表头指针；number：卡号
*函数返回值：true：重复；false：不重复
*/

#include"header.h"
void card_cancel()
{
    CARD_NODE *p_node = NULL;
    CARD_NODE *head_node = card_get_list();
    char number[MAX_LENGTH+1];
    char password[MAX_LENGTH+1];

    //定义一个变量，用来记录是否有重复的卡号
    


    printf("请输入要注销的卡号：");
    scanf("%s", number);
    while(card_check_repeat(head_node,number) == false)
    {
        printf("卡号不存在，请重新输入！\n");
        scanf("%s", number);
    }

    printf("请输入要注销的密码：");
    scanf("%s", password);

    for(p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        if(strcmp(p_node->date.number,number) == 0 && strcmp(p_node->date.password,password) == 0)
        {
            p_node->date.status = blocked;
            card_save_list(head_node);
            printf("注销成功！\n");
            return;
        }
    }
    printf("密码错误，注销失败！\n");
    card_save_list(head_node);
    return;
}

//测试用例
/* int main()
{
    CARD_NODE *head_node = NULL;
    head_node = card_get_list();
    card_cancel(head_node);
    return 0;
} */
