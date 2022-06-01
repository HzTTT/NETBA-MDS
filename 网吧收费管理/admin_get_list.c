/*
*函数名称：admin_get_list
*函数功能：获取管理员数据链表
*函数参数：无
*函数返回值：ADMIN_NODE *head
*/
#include"header.h"
ADMIN_NODE *admin_get_list()
{
    ADMIN_NODE *head_node = NULL;
    ADMIN_NODE *tail_node = NULL;
    ADMIN_NODE *new_node = NULL;

    ADMIN admin;
    BOOL is_head=true;                  //是否是头结点


    FILE *admin_file = fopen("date/admin.dat", "rb");
    if(admin_file == NULL)
    {
        printf("打开文件失败！\n");
        exit(0);
    }

    //读取文件中的数据放进链表
    while(fread(&admin, sizeof(ADMIN), 1, admin_file) == 1){
        if((new_node=malloc(sizeof(ADMIN_NODE))) == NULL){
            printf("内存分配失败！\n");
            exit(0);
        }

        if(is_head == true){
            head_node = new_node;       //设置头结点
            is_head = false;
        }
        else{
            tail_node->next = new_node; //将新结点插入到链表的尾部
        }
        new_node->date = admin;         //将数据放进结点
        new_node->next = NULL;         //新结点的下一个结点为空
        tail_node = new_node;           //更新尾结点
    }

    fclose(admin_file);
    return head_node;
}
//测试用例
/* int main()
{
    ADMIN_NODE *head = NULL;
    head=admin_get_list();
    while(head != NULL){
        printf("%s ", head->date.number);
        printf("%s ", head->date.password);
        printf("%d ",head->date.is_super_admin);
        for(int i=0;i<5;i++){
            printf("%d ",head->date.is_authority[i]);
        }
        printf("\n");
        head = head->next;
    }
    return 0;
} */
