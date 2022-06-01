/*
*函数名称：bill_get_list
*函数功能：获取账单链表
*函数参数：无
*函数返回值：BILL_NODE *head_node
*/
#include"header.h"
BILL_NODE *bill_get_list()
{
    BILL_NODE *head_node = NULL;
    BILL_NODE *tail_node = NULL;
    BILL_NODE *new_node = NULL;

    BILL bill;
    BOOL is_head=true;

    FILE *bill_file = fopen("date/bill.dat", "rb");
    if (bill_file == NULL)
    {
        printf("打开文件失败！\n");
        exit(0);
    }

    //读取文件中的数据放进链表
    while (fread(&bill, sizeof(BILL), 1, bill_file) == 1)
    {
        if ((new_node = malloc(sizeof(BILL_NODE))) == NULL)
        {
            printf("内存分配失败！\n");
            exit(0);
        }

        if (is_head == true)
        {
            head_node = new_node;
            is_head = false;
        }
        else
        {
            tail_node->next = new_node; //将新结点插入到链表的尾部
        }
        new_node->date = bill; //将数据放进结点
        new_node->next = NULL;     //新结点的下一个结点为空
        tail_node = new_node;      //更新尾结点
    }

    fclose(bill_file);
    return head_node;
}

//测试用例
/* int main()
{
    BILL_NODE *head_node = NULL;
    head_node = bill_get_list();
    while(head_node != NULL)
    {
        printf("%s ", head_node->date.number);
        printf("%d-%d-%d-%d ", head_node->date.start_time.year, head_node->date.start_time.month, head_node->date.start_time.day, head_node->date.start_time.hour);
        printf("%d ", head_node->date.time_length);
        printf("%.2f ", head_node->date.fee);
        printf("%d ", head_node->date.is_charge);
        head_node = head_node->next;
        printf("\n");
    }

    return 0;
} */