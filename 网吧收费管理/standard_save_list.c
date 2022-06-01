/*
 *函数名称：standard_save_list
 *函数功能：保存计费标准链表
 *函数参数：STANDARD_NODE *head_node 指向计费标准链表的头结点
 *函数返回值：无
 */
#include "header.h"
void standard_save_list(STANDARD_NODE *head_node)
{
    STANDARD_NODE *p_node = NULL;
    STANDARD_NODE *p_free = NULL;
    FILE *standard_file = fopen("date/standard.dat", "wb");
    if (standard_file == NULL)
    {
        printf("打开文件失败！\n");
        exit(0);
    }

    for (p_node = head_node; p_node != NULL; p_node = p_node->next, free(p_free))
    {
        fwrite(&p_node->date, sizeof(STANDARD), 1, standard_file);
        p_free = p_node;
    }

    fclose(standard_file);
}