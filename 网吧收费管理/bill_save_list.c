/*
 *函数名称：bill_get_list
 *函数功能：获取账单链表
 *函数参数：无
 *函数返回值：BILL_NODE *head_node
 */
#include "header.h"
void bill_save_list(BILL_NODE *head_node)
{
    BILL_NODE *p_node = NULL;
    BILL_NODE *p_free = NULL;
    FILE *bill_file = fopen("date/bill.dat", "wb");
    if (bill_file == NULL)
    {
        printf("打开文件失败！\n");
        exit(0);
    }

    for (p_node = head_node; p_node != NULL; p_node = p_node->next, free(p_free))
    {
        fwrite(&p_node->date, sizeof(BILL), 1, bill_file);
        p_free = p_node;
    }

    fclose(bill_file);
}