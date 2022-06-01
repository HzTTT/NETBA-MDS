/*
 * 函数名称：login_card
 * 函数功能：用户登录
 * 函数参数：无
 * 函数返回值：无
 */
#include "header.h"
void login_card()
{
    CARD_NODE *p_card_node = NULL;
    BILL_NODE *p_bill_node = NULL;
    BILL_NODE *new_bill_node = NULL;
    CARD_NODE *card_head_node = card_get_list();
    BILL_NODE *bill_head_node = bill_get_list();
    TIME time;
    char card_number[MAX_LENGTH + 1];
    char card_password[MAX_LENGTH + 1];

    printf("请输入要上机的卡号：");
    scanf("%s", card_number);
    while (card_check_repeat(card_head_node, card_number) == false)
    {
        printf("卡号不存在，请重新输入！\n");
        scanf("%s", card_number);
    }

    printf("请输入密码：");
    scanf("%s", card_password);
    while (strlen(card_password) > MAX_LENGTH)
    {
        printf("密码长度超过20个字符，请重新输入！\n");
        scanf("%s", card_password);
    }

    for (p_card_node = card_head_node; p_card_node != NULL; p_card_node = p_card_node->next)
    {
        if (strcmp(p_card_node->date.number, card_number) == 0 && strcmp(p_card_node->date.password, card_password) == 0)
        {
            if (p_card_node->date.status == blocked)
            {
                printf("该卡号已经注销，无法上机！\n");
                bill_save_list(bill_head_node);
                card_save_list(card_head_node);
                return;
            }
            if (p_card_node->date.status == online)
            {
                printf("该卡号已上机，无法重复上机！\n");
                bill_save_list(bill_head_node);
                card_save_list(card_head_node);
                return;
            }
            break;
        }
    }

    if (p_card_node == NULL)
    {
        printf("密码错误，登录失败！\n");
        bill_save_list(bill_head_node);
        card_save_list(card_head_node);
        return;
    }

    printf("请输入上机时间（格式：年-月-日—时）：");
    while (scanf("%d-%d-%d-%d", &time.year, &time.month, &time.day, &time.hour) != 4)
    {
        printf("输入格式错误，请重新输入！\n");
    }
    while (time.year <= 0 || time.month <= 0 || time.day <= 0 || time.hour < 0)
    {
        printf("时间不能小于0，请重新输入！\n");
        while (scanf("%d-%d-%d-%d", &time.year, &time.month, &time.day, &time.hour) != 4)
        {
            printf("输入格式错误，请重新输入！\n");
        }
    }

    p_card_node->date.status = online;

    //创建新的账单节点
    new_bill_node = (BILL_NODE *)malloc(sizeof(BILL_NODE));
    if (new_bill_node == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    //初始化账单信息
    new_bill_node->date.start_time = time;           //登陆时间
    strcpy(new_bill_node->date.number, card_number); //卡号
    new_bill_node->date.is_charge = false;           //是否完成消费
    new_bill_node->next = NULL;                      //指针初始化
    new_bill_node->date.fee = 0;                     //消费金额
    new_bill_node->date.time_length = 0;             //消费时长

    //将账单信息插入链表
    if (bill_head_node == NULL)
    {
        bill_head_node = new_bill_node;
    }
    else
    {
        p_bill_node = bill_head_node;
        while (p_bill_node->next != NULL)
        {
            p_bill_node = p_bill_node->next;
        }
        p_bill_node->next = new_bill_node;
    }

    bill_save_list(bill_head_node);
    card_save_list(card_head_node);

    printf("用户：【%s】上机成功！\n", p_card_node->date.name);
    return;
}

//测试用例
/* int main()
{
    login_card();
    return 0;
} */
