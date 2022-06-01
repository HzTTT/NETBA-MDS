/*
*函数名称：query_all
*函数功能：查询一段时间内的所有消费记录
*函数参数：无
*函数返回值：无
*/
#include "header.h"
void query_all()
{
    BILL_NODE *p_node = NULL;
    BILL_NODE *head_node = bill_get_list();
    BOOL is_exist = false;
    TIME start_time, end_time;
    table T_bill={
        .col_num=4,
        .row_num=1,
    };
    char formated_number[100][20];
    char formated_time[100][20];
    char formated_fee[100][10];
    char formated_length[100][10];
    char formated_out[2048];
    float fee=0;
    FILE *bill_file = fopen("date/bill.dat", "rb");
    if (bill_file == NULL)
    {
        printf("打开文件失败！\n");
        exit(0);
    }

    printf("请输入开始时间（年-月-日）：");
    while (scanf("%d-%d-%d", &start_time.year, &start_time.month, &start_time.day) != 3)
    {
        printf("输入格式错误，请重新输入！");
    }
    while (start_time.year <= 0 || start_time.month <= 0 || start_time.day <= 0)
    {
        printf("时间不能小于0，请重新输入！");
        while (scanf("%d-%d-%d", &start_time.year, &start_time.month, &start_time.day) != 3)
        {
            printf("输入格式错误，请重新输入！");
        }
    }

    printf("请输入结束时间（年-月-日）：");
    while (scanf("%d-%d-%d", &end_time.year, &end_time.month, &end_time.day) != 3)
    {
        printf("输入格式错误，请重新输入！");
    }
    while (end_time.year <= 0 || end_time.month <= 0 || end_time.day <= 0)
    {
        printf("时间不能小于0，请重新输入！");
        while (scanf("%d-%d-%d", &end_time.year, &end_time.month, &end_time.day) != 3)
        {
            printf("输入格式错误，请重新输入！");
        }
    }

    for(p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        if (((start_time.year-p_node->date.start_time.year) * 365 + (start_time.month-p_node->date.start_time.month) * 30 + (start_time.day-p_node->date.start_time.day) <= 0) || ((end_time.year-p_node->date.start_time.year) * 365 + (end_time.month-p_node->date.start_time.month) * 30 + (end_time.day-p_node->date.start_time.day) >= 0))
        {
            sprintf(formated_number[T_bill.row_num-1], "%s", p_node->date.number);
            sprintf(formated_time[T_bill.row_num-1], "%d-%d-%d", p_node->date.start_time.year, p_node->date.start_time.month, p_node->date.start_time.day);
            sprintf(formated_fee[T_bill.row_num-1], "%.2f", p_node->date.fee);
            sprintf(formated_length[T_bill.row_num-1], "%dh", p_node->date.time_length);
            T_bill.row_num++;
            fee+=p_node->date.fee;
            is_exist = true;
        }
    }

    if(is_exist==false)
    {
        printf("没有找到相关记录！");
        bill_save_list(head_node);
        return ;
    }

    get_memory(&T_bill);
    T_bill.content[0][0] = "number";
    T_bill.content[0][1] = "上机时间";
    T_bill.content[0][2] = "费用";
    T_bill.content[0][3] = "时长";

    for(unsigned int i=0;i<T_bill.row_num-1;i++)
    {
        T_bill.content[i+1][0] = formated_number[i];
        T_bill.content[i+1][1] = formated_time[i];
        T_bill.content[i+1][2] = formated_fee[i];
        T_bill.content[i+1][3] = formated_length[i];
    }
    format_table(&T_bill,formated_out);
    printf("%s", formated_out);
    close_memory(&T_bill);

    printf("总计营业额：%.2f¥\n", fee);
    bill_save_list(head_node);

}

//测试用例
/* int main()
{
    query_all();
    return 0;
} */
