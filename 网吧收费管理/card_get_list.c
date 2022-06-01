/*
*函数名称：card_get_list
*函数功能：获取卡数据链表
*函数参数：无
*函数返回值：CARD_NODE *head
*/
#include"header.h"
CARD_NODE *card_get_list()
{
    CARD_NODE *head_node = NULL;
    CARD_NODE *tail_node = NULL;
    CARD_NODE *new_node = NULL;
    BOOL is_head=true;                  //是否是头结点
    CARD card;
    FILE *card_file = fopen("date/card.dat", "rb");

    if (card_file == NULL)
    {
        printf("打开文件失败！\n");
        exit(0);
    }

    while(fread(&card, sizeof(CARD), 1, card_file)==1)
    {
        new_node = (CARD_NODE *)malloc(sizeof(CARD_NODE));
        if (new_node == NULL)
        {
            printf("内存分配失败！\n");
            exit(0);
        }

        if (is_head == true)
        {
            head_node = new_node;           //设置头结点
            is_head = false;
        }
        else
        {
            tail_node->next = new_node;     //将新结点插入到链表的尾部
        }
        new_node->date = card;              //将数据放进结点
        new_node->next = NULL;              //新结点的下一个结点为空
        tail_node = new_node;               //更新尾结点
    }
    fclose(card_file);

    return head_node;
}

//测试用例
/* int main()
{
    CARD_NODE *head_node = NULL;
    head_node = card_get_list();
    while (head_node != NULL)
    {
        printf("%s ", head_node->date.number);
        printf("%s ", head_node->date.password);
        printf("%s ", head_node->date.name);
        printf("%f ", head_node->date.balance);
        printf("%d\n", head_node->date.status);
        head_node = head_node->next;
    }
    return 0;
} */



