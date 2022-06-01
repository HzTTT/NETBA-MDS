/*
 *函数名称：admin_save_list
 *函数功能：保存管理员数据链表
 *函数参数：无
 *函数返回值：无
 */
#include "header.h"
void admin_save_list(ADMIN_NODE *head_node)
{
    ADMIN_NODE *p_node = NULL;
    ADMIN_NODE *p_free = NULL;
    FILE *admin_file = fopen("date/admin.dat", "wb");
    if (admin_file == NULL)
    {
        printf("打开文件失败！\n");
        exit(0);
    }

    for (p_node = head_node; p_node != NULL; p_node = p_node->next, free(p_free))
    {
        fwrite(&p_node->date, sizeof(ADMIN), 1, admin_file);
        p_free = p_node;
    }

    fclose(admin_file);
}