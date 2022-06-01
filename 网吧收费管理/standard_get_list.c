/*
*函数名称：standard_get_list
*函数功能：获取计费标准链表
*函数参数：无
*函数返回值：STANDARD_NODE *head_node 指向计费标准链表的头结点
*/
#include "header.h"
STANDARD_NODE *standard_get_list()
{
    STANDARD_NODE *head_node = NULL;
    STANDARD_NODE *tail_node = NULL;
    STANDARD_NODE *new_node = NULL;
    BOOL is_head = true;
    STANDARD standard;
    FILE *standard_file = fopen("date/standard.dat", "rb");

    if (standard_file == NULL)
    {
        printf("打开文件失败！\n");
        exit(0);
    }

    //读取文件中的数据放进链表
    while (fread(&standard, sizeof(STANDARD), 1, standard_file) == 1)
    {
        if ((new_node = malloc(sizeof(STANDARD_NODE))) == NULL)
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
        new_node->date = standard; //将数据放进结点
        new_node->next = NULL;     //新结点的下一个结点为空
        tail_node = new_node;      //更新尾结点
    }
    fclose(standard_file);

    return head_node;
}
//测试用例
/* int main()
{
    STANDARD_NODE *head_node = NULL;
    STANDARD_NODE *p_node = NULL;
    head_node = standard_get_list();
    for (p_node = head_node; p_node != NULL; p_node = p_node->next)
    {
        printf("%d小时的费用：%.2f元\n", p_node->date.time_length,p_node->date.fee);
    }
    return 0;
}
 */