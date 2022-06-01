/*
*函数名称：standard_check_repeat
*函数功能：检查计费标准是否存在
*函数参数：无
*函数返回值：Bool型，true表示存在，false表示不存在
*/
#include"header.h"
BOOL standard_check_repeat(STANDARD_NODE *head_node, int time_length)
{
    STANDARD_NODE *p_node = NULL;

    for (p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        if (p_node->date.time_length == time_length)
        {
            return true;
        }
    }

    return false;
}
