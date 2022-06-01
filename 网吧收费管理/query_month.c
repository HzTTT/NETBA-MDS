/*
*函数名称：query_year
*函数功能：查询一年的营业额
*函数参数：无
*函数返回值：无
*/
#include"header.h"
void query_year()
{
    BILL_NODE *p_bill_node = NULL;
    BILL_NODE *heard_bill_node = bill_get_list();
    table T_bill={
        .col_num=13,
        .row_num=3,
    };
    int year;
    int times[12] = {0};
    float money[12] = {0};
    float sum = 0;
    char formated_out[2048];
    char formated_times[12][10];
    char formated_money[12][10];
    FILE *fp_txt=fopen("date/bill.txt", "a");
    if(fp_txt==NULL)
    {
        printf("打开文件失败！\n");
        exit(1);
    }
    printf("请输入要查询的年份：");
    scanf("%d", &year);

    for(p_bill_node = heard_bill_node; p_bill_node != NULL; p_bill_node = p_bill_node->next)
    {
        if(p_bill_node->date.start_time.year == year)
        {
            times[p_bill_node->date.start_time.month - 1] += 1;
            money[p_bill_node->date.start_time.month - 1] += p_bill_node->date.fee;
            sum += p_bill_node->date.fee;
        }
    }

    printf("%d年的账单如下：\n", year);

    get_memory(&T_bill);
    T_bill.content[0][0] = "  ";
    T_bill.content[0][1] = "1月";
    T_bill.content[0][2] = "2月";
    T_bill.content[0][3] = "3月";
    T_bill.content[0][4] = "4月";
    T_bill.content[0][5] = "5月";
    T_bill.content[0][6] = "6月";
    T_bill.content[0][7] = "7月";
    T_bill.content[0][8] = "8月";
    T_bill.content[0][9] = "9月";
    T_bill.content[0][10] = "10月";
    T_bill.content[0][11] = "11月";
    T_bill.content[0][12] = "12月";
    T_bill.content[1][0] = "上机次数";
    T_bill.content[2][0] = "营业额";

    for(int i = 0; i < 12; i++)
    {
        sprintf(formated_times[i], "%d次", times[i]);
        sprintf(formated_money[i], "%.2f", money[i]);
        T_bill.content[1][i + 1] = formated_times[i];
        T_bill.content[2][i + 1] = formated_money[i];
    }

    format_table(&T_bill, formated_out);
    printf("%s", formated_out);
    close_memory(&T_bill);

    printf("\n总计：%.2f¥\n", sum);

    fprintf(fp_txt, "%d年的账单如下：\n", year);
    for(int i = 0; i < 12; i++)
    {
        fprintf(fp_txt, "%d月%d次 ", i + 1, times[i]);
    }
    fprintf(fp_txt, "\n总计：%.2f¥\n", sum);
    fclose(fp_txt);
    bill_save_list(heard_bill_node);
}

//测试用例
/* int main()
{
    query_year();
    return 0;
} */