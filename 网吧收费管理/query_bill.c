/*
 * 函数名称：query_bill
 * 函数功能：查询一个卡的消费记录
 * 函数参数：无
 * 返回值：无
 */
#include"header.h"
void query_bill()
{
    BILL_NODE *head_node = bill_get_list();
    BILL_NODE *p_node = NULL;
    BILL_NODE *new_head_node = NULL;
    BILL_NODE *new_tail_node = NULL;
    BILL_NODE *new_node = NULL;
    CARD_NODE *card_head = card_get_list();
    BOOL is_head=true;
    TIME start_time, end_time;
    table T_bill={
        .col_num=3,
        .row_num=1,
    };
    char formated_out[2048];
    char formated_start_time[100][20];
    char formated_fee[100][1000];
    char formated_time_length[100][1000];
    int row=1;

    char card_number[MAX_LENGTH + 1];

    printf("请输入要查询的卡号：");
    scanf("%s", card_number);
    while(card_check_repeat(card_head,card_number) == false)
    {
        printf("卡号不存在，请重新输入！\n");
        scanf("%s", card_number);
    }

    printf("请输入开始时间（格式：年-月-日）：");
    while(scanf("%d-%d-%d", &start_time.year, &start_time.month, &start_time.day) != 3)
    {
        printf("输入格式错误，请重新输入！\n");
    }
    while(start_time.year < 0 || start_time.month < 0 || start_time.day < 0 || start_time.month > 12 || start_time.day > 31)
    {
        printf("输入日期错误，请重新输入！\n");
        printf("请输入开始时间（格式：年-月-日）：");
        while(scanf("%d-%d-%d", &start_time.year, &start_time.month, &start_time.day) != 3)
        {
            printf("输入格式错误，请重新输入！\n");
        }
    }
    
    printf("请输入结束时间（格式：年-月-日）：");
    while(scanf("%d-%d-%d", &end_time.year, &end_time.month, &end_time.day) != 3)
    {
        printf("输入格式错误，请重新输入！\n");
    }
    while((end_time.year < 0 || end_time.month < 0 || end_time.day < 0 || end_time.month > 12 || end_time.day > 31) && (end_time.year-start_time.year) * 365 + (end_time.month-start_time.month) * 30 + (end_time.day-start_time.day) <= 0)
    {
        if((end_time.year-start_time.year) * 365 + (end_time.month-start_time.month) * 30 + (end_time.day-start_time.day) <= 0)
        {
            printf("输入结束日期小于开始日期，请重新输入！\n");
        }
        else
        {
            printf("输入日期错误，请重新输入！\n");
        }
        while(scanf("%d-%d-%d", &end_time.year, &end_time.month, &end_time.day) != 3)
        {
            printf("输入格式错误，请重新输入！\n");
        }
    }

    for(p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        // 如果卡号相同且完成消费，则将其添加到新的链表中
        if(strcmp(p_node->date.number, card_number) == 0 && p_node->date.is_charge == true )
        {
            // 如果时间不在查询范围内，则跳出循环
            if(((start_time.year-p_node->date.start_time.year) * 365 + (start_time.month-p_node->date.start_time.month) * 30 + (start_time.day-p_node->date.start_time.day) > 0) || ((end_time.year-p_node->date.start_time.year) * 365 + (end_time.month-p_node->date.start_time.month) * 30 + (end_time.day-p_node->date.start_time.day) < 0))
            {
                break;                         
            }
 
            new_node = (BILL_NODE *)malloc(sizeof(BILL_NODE));
            if(new_node == NULL)
            {
                printf("内存分配失败！\n");
                exit(1);
            }
            new_node->date = p_node->date;
            if(is_head)
            {
                new_head_node = new_node;
                is_head = false;
            }
            else
            {
                new_tail_node->next = new_node;
            }
            new_tail_node = new_node;
            new_tail_node->next = NULL;

            T_bill.row_num++;
        }
    }
    if(is_head==true)
    {
        printf("该卡号没有消费记录！\n");
        bill_save_list(head_node);
        return;
    }

    printf("账号：%s在%d年%d月%d日到%d年%d月%d日的消费记录如下：\n", card_number, start_time.year, start_time.month, start_time.day, end_time.year, end_time.month, end_time.day);

    // 格式化输出
    get_memory(&T_bill);
    T_bill.content[0][0] = "消费时间";
    T_bill.content[0][1] = "消费时长";
    T_bill.content[0][2] = "消费金额";

    for(p_node = new_head_node; p_node != NULL; p_node = p_node->next)
    {
        sprintf(formated_start_time[row-1], "%d-%d-%d", p_node->date.start_time.year, p_node->date.start_time.month, p_node->date.start_time.day);
        T_bill.content[row][0] = formated_start_time[row-1];
        sprintf(formated_time_length[row-1], "%dh", p_node->date.time_length);
        T_bill.content[row][1] = formated_time_length[row-1];
        sprintf(formated_fee[row-1], "%.2f", p_node->date.fee);
        T_bill.content[row][2] = formated_fee[row-1];
        row++;
    }

    // 打印输出
    format_table(&T_bill,formated_out);
    printf("%s", formated_out);
    close_memory(&T_bill);

    return;
}

//测试用例
/* int main()
{
    query_bill();
    return 0;
} */