/*
*函数名称：card_add
*函数功能：添加卡片
*函数参数：CARD_NODE *head_node
*函数返回值：无
*/
#include"header.h"
void card_add()
{
    CARD_NODE *new_node = NULL;
    CARD_NODE *p_node = NULL;
    CARD_NODE *head_node = card_get_list();
    CARD card = {
        .number = "",
        .password = "",
        .balance = 0,
        .status = offline,
        .name = ""
    };

    printf("请输入新开卡的卡号(不大于20个字符)：");
    scanf("%s", card.number);
    while (strlen(card.number) > MAX_LENGTH) 
    {
        printf("卡号长度超过20个字符，请重新输入！\n");
        scanf("%s", card.number);
    }
    while(card_check_repeat(head_node,card.number) == true)
    {
        printf("卡号已存在，请重新输入！\n");
        scanf("%s", card.number);
    }

    printf("请输入新开卡的密码(不大于20个字符)：");
    scanf("%s", card.password);
    while (strlen(card.password) > MAX_LENGTH) 
    {
        printf("密码长度超过20个字符，请重新输入！\n");
        scanf("%s", card.password);
    }

    printf("请输入开卡人姓名(不大于20个字符)：");
    scanf("%s", card.name);
    while (strlen(card.name) > MAX_LENGTH) 
    {
        printf("姓名长度超过20个字符，请重新输入！\n");
        scanf("%s", card.name);
    }

    printf("请输入开卡金额：");
    scanf("%f", &card.balance);
    while (card.balance < 0) 
    {
        printf("金额不能小于0，请重新输入！\n");
        scanf("%f", &card.balance);
    }

    if((new_node = (CARD_NODE *)malloc(sizeof(CARD_NODE))) == NULL)
    {
        printf("内存分配失败！\n");
        exit(1);
    }

    new_node->date = card;
    new_node->next = NULL;

    if (head_node == NULL)
    {
        head_node = new_node;
    }
    else
    {
        p_node = head_node;
        while (p_node->next != NULL)
        {
            p_node = p_node->next;
        }
        p_node->next = new_node;
    }
    printf("开卡成功\n");
    card_save_list(head_node);
}

//测试用例
/* int main()
{
    CARD_NODE *head_node = NULL;
    head_node = card_get_list();
    card_add();
    return 0;
} */