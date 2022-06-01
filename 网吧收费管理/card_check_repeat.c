/*
*函数名称：card_check_repeat
*函数功能：检查卡号是否重复
*函数参数：CARD_NODE* head_node,char *number
*函数返回值：BOLL
*/
#include "header.h"
BOOL card_check_repeat(CARD_NODE *head_node, char *number)
{
    CARD_NODE *p_node = NULL;

    for (p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        if (strcmp(p_node->date.number, number) == 0)
        {
            return true;
        }
    }

    return false;
}