/*
*函数名称：logout_card
*函数功能：退出卡
*函数参数：无
*函数返回值：无
*/
#include"header.h"
void logout_card() 
{
    CARD_NODE *p_card_node = NULL;
    BILL_NODE *p_bill_node = NULL;
    STANDARD_NODE *p_standard_node = NULL;
    STANDARD_NODE *standard_head_node = standard_get_list();
    CARD_NODE *card_head_node = card_get_list();
    BILL_NODE *bill_head_node = bill_get_list();
    TIME start_time, end_time;
    table table_data={
        .row_num=2,
        .col_num=7,
    };
    char formated_out[2048];
    char formated_start_time[20];
    char formated_end_time[20];
    char formated_fee[1000];
    char formated_balance[1000];
    char formated_time_length[1000];

    int time_length;
    char card_number[MAX_LENGTH+1];
    char card_password[MAX_LENGTH+1];

    printf("请输入要下机的卡号：");
    scanf("%s", card_number);
    while(card_check_repeat(card_head_node,card_number) == false)
    {
        printf("卡号不存在，请重新输入！\n");
        scanf("%s", card_number);
    }

    printf("请输入密码：");
    scanf("%s", card_password);

    //查找卡号
    for(p_card_node = card_head_node; p_card_node != NULL; p_card_node = p_card_node->next)
    {
        if(strcmp(p_card_node->date.number,card_number) == 0 && strcmp(p_card_node->date.password,card_password) == 0)
        {
            if(p_card_node->date.status == blocked)
            {
                printf("卡号已注销，无法下机！\n");
                bill_save_list(bill_head_node);
                card_save_list(card_head_node);
                standard_save_list(standard_head_node);
                return;
            }
            if(p_card_node->date.status == offline)
            {
                printf("卡号没有上机，无法下机！\n");
                bill_save_list(bill_head_node);
                card_save_list(card_head_node);
                standard_save_list(standard_head_node);
                return;
            
            }
            break;
        }
    }
    
    if(p_card_node == NULL)
    {
        printf("密码错误，下机失败！\n");
        return;
    }

    //查找上机时间
    for(p_bill_node = bill_head_node; p_bill_node != NULL; p_bill_node = p_bill_node->next)
    {
        if(strcmp(p_bill_node->date.number,card_number) == 0 && p_bill_node->date.is_charge == false)
        {
            start_time = p_bill_node->date.start_time;
            printf("上机时间：%d-%d-%d-%d\n",start_time.year,start_time.month,start_time.day,start_time.hour);
            break;
        }
    }

    //获取下机时间
    printf("请输入下机时间（格式：年-月-日—时）：");
    while(scanf("%d-%d-%d-%d", &end_time.year, &end_time.month, &end_time.day, &end_time.hour) != 4)
    {
        printf("时间格式错误，请重新输入！\n");
    }
    while(end_time.year<0 || end_time.month<0 || end_time.day<0 || end_time.hour<0)
    {
        printf("时间不能小于0，请重新输入！\n");
        while(scanf("%d-%d-%d-%d", &end_time.year, &end_time.month, &end_time.day, &end_time.hour) != 4)
        {
            printf("时间格式错误，请重新输入！\n");
        }
    }

    //计算上机时长
    time_length = (end_time.day-start_time.day)*24 + (end_time.hour-start_time.hour);
    if(time_length < 0)
    {
        printf("下机时间输入错误，下机失败\n");
        bill_save_list(bill_head_node);
        card_save_list(card_head_node);
        standard_save_list(standard_head_node);
        return;
    }
    
  

    //计算费用
    for(p_standard_node = standard_head_node; p_standard_node != NULL; p_standard_node = p_standard_node->next)
    {
        if(p_standard_node->date.time_length == time_length)
        {
            p_bill_node->date.fee = p_standard_node->date.fee;
            p_card_node->date.balance -= p_bill_node->date.fee;
            if(p_card_node->date.balance < 0)
            {
                printf("余额不足，下机失败！\n");
                bill_save_list(bill_head_node);
                card_save_list(card_head_node);
                standard_save_list(standard_head_node);
                return;
            }
            break;
        }
    }
    if(p_standard_node == NULL)
    {
        p_bill_node->date.fee = time_length*5;
        p_card_node->date.balance -= p_bill_node->date.fee;
        if(p_card_node->date.balance < 0)
        {
            printf("余额不足，下机失败！\n");
            bill_save_list(bill_head_node);
            card_save_list(card_head_node);
            standard_save_list(standard_head_node);
            return;
        }
    }

    //更改卡状态
    p_card_node->date.status = offline;   
    //设置为已缴费
    p_bill_node->date.is_charge = true;
    //设置上网时长
    p_bill_node->date.time_length = time_length;

    //输出账单
    printf("以下是您的账单：\n");

    get_memory(&table_data);
    sprintf(formated_start_time, "%d-%d-%d-%d", start_time.year, start_time.month, start_time.day, start_time.hour);
    sprintf(formated_end_time, "%d-%d-%d-%d", end_time.year, end_time.month, end_time.day, end_time.hour);
    sprintf(formated_fee, "%.2f", p_bill_node->date.fee);
    sprintf(formated_balance, "%.2f", p_card_node->date.balance);
    sprintf(formated_time_length, "%d", time_length);

    table_data.content[0][0] = "number";
    table_data.content[0][1] = "name";
    table_data.content[0][2] = "开机";
    table_data.content[0][3] = "下机";
    table_data.content[0][4] = "时间";
    table_data.content[0][5] = "费用";
    table_data.content[0][6] = "余额";
    table_data.content[1][0] = card_number;
    table_data.content[1][1] = p_card_node->date.name;
    table_data.content[1][2] = formated_start_time;
    table_data.content[1][3] = formated_end_time;
    table_data.content[1][4] = formated_time_length;
    table_data.content[1][5] = formated_fee;
    table_data.content[1][6] = formated_balance;
    
    format_table(&table_data, formated_out);
    printf("%s", formated_out);
    close_memory(&table_data);

    //保存数据
    card_save_list(card_head_node);
    bill_save_list(bill_head_node);
    standard_save_list(standard_head_node);

    printf("下机成功！\n");
    return;
}

//测试用例
/* int main()
{
    logout_card();
    return 0;
} */