/*
*函数名称：card_query
*函数功能：查询卡号
*输入参数：CARD_NODE *head_node
*返回值：无
*/
#include "header.h"
void card_query()
{
    CARD_NODE *p_node = NULL;
    CARD card;
    BOOL flag = false;
    table card_table = {
        .col_num = 4,
        .row_num = 2,
    };
    CARD_NODE *head_node = card_get_list();
    char balance[20];

    char formated_out[2048];
    get_memory(&card_table);

    printf("请输入要查询的卡号：");
    scanf("%s", card.number);
    while (strlen(card.number) > MAX_LENGTH || card_check_repeat(head_node, card.number) == false)           //判断账号长度
    {
        if(strlen(card.number) > MAX_LENGTH)
        {
            printf("卡号长度超过20个字符，请重新输入！\n");
        }
        else
        {
            printf("卡号不存在，请重新输入！\n");
        }
        scanf("%s", card.number);
    }

    printf("请输入要查询的卡密码：");
    scanf("%s", card.password);
    while (strlen(card.password) > MAX_LENGTH)
    {
        printf("密码长度超过20个字符，请重新输入！\n");
        scanf("%s", card.password);
    }


    for (p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        if (strcmp(p_node->date.number, card.number) == 0 && strcmp(p_node->date.password, card.password) == 0)
        {
            card_table.content[0][0] = "卡号";
            card_table.content[0][1] = "用户名";
            card_table.content[0][2] = "余额";
            card_table.content[0][3] = "状态";
            card_table.content[1][0] = p_node->date.number;
            card_table.content[1][1] = p_node->date.name;
            sprintf(balance, "%.2f", p_node->date.balance);
            card_table.content[1][2] = balance;
            switch (p_node->date.status)
            {
            case online:
                card_table.content[1][3] = "在线";
                break;
            case offline:
                card_table.content[1][3] = "离线";
                break;
            case blocked:
                card_table.content[1][3] = "注销";
                break;
            }
            format_table(&card_table, formated_out);
            printf("%s\n", formated_out);
            flag = true;
            break;
        }
    }
    if (flag == false)
    {
        printf("输入卡号的密码错误.\n");
    }

    close_memory(&card_table);
    card_save_list(head_node);
}

//测试用例
/* int main()
{
    CARD_NODE *head_node = NULL;
    head_node = card_get_list();
    card_query(head_node);
    return 0;
} */
