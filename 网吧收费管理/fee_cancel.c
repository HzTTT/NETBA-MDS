/*
*函数名称：fee_cancel
*函数功能：退款
*函数参数：无
*函数返回值：无
*/
#include"header.h"
void fee_cancel()
{
    CARD_NODE *p_node = NULL;
    CARD_NODE *head_node = card_get_list();
    float refund_fee = 0;
    char card_number[20];
    char card_password[20];

    printf("请输入要退款的卡号：");
    scanf("%s", card_number);
    while (strlen(card_number) > MAX_LENGTH || card_check_repeat(head_node, card_number) == false)           //判断账号长度
    {
        if(strlen(card_number) > MAX_LENGTH)
        {
            printf("卡号长度超过20个字符，请重新输入！\n");
        }
        else
        {
            printf("卡号不存在，请重新输入！\n");
        }
        scanf("%s", card_number);
    }

    printf("请输入要退款的卡密码：");
    scanf("%s", card_password);
    while (strlen(card_password) > MAX_LENGTH)
    {
        printf("密码长度超过20个字符，请重新输入！\n");
        scanf("%s", card_password);
    }

    for (p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        if (strcmp(p_node->date.number, card_number) == 0 && strcmp(p_node->date.password, card_password) == 0)
        {
            if(p_node->date.status == blocked )
            {
                printf("该卡已注销，无法退款！\n");
                card_save_list(head_node);
                return;
            }

            printf("请输入退款金额：");
            scanf("%f", &refund_fee);
            if(refund_fee > p_node->date.balance)
            {
                printf("余额不足，无法退款！\n");
                card_save_list(head_node);
                return;
            }
            p_node->date.balance -= refund_fee;
            printf("剩余余额：%.2f，退款成功！\n", p_node->date.balance);
            card_save_list(head_node);
            return;
        }
    }

    printf("密码错误，退款失败！\n");
    card_save_list(head_node);
}

//测试用例
/* int main()
{
    CARD_NODE *head_node = NULL;
    head_node = card_get_list();
    fee_cancel();
    return 0;
} */
