/*
 *函数名称：card_save_list
 *函数功能：保存卡数据链表
 *函数参数：CARD_NODE *head_node
 *函数返回值：无
 */
#include "header.h"
void card_save_list(CARD_NODE *head_node)
{
    CARD_NODE *p_node = NULL;
    CARD_NODE *p_free = NULL;
    FILE *card_file = fopen("date/card.dat", "wb");
    if (card_file == NULL)
    {
        printf("打开文件失败！\n");
        exit(0);
    }

    for (p_node = head_node; p_node != NULL; p_node = p_node->next, free(p_free))
    {
        fwrite(&p_node->date, sizeof(CARD), 1, card_file);
        p_free = p_node;
    }

    fclose(card_file);
}

