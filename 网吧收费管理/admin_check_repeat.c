/*
*函数名称：admin_check_repeat
*函数功能：检查管理员账号是否重复
*函数参数：CARD_NODE* head_node,char *number
*函数返回值：BOOL
*/
#include "header.h"
BOOL admin_check_repeat(ADMIN_NODE *head_node, char *number)
{
    ADMIN_NODE *p_node = NULL;

    for (p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        if (strcmp(p_node->date.number, number) == 0)
        {
            return true;
        }
    }

    return false;
}
