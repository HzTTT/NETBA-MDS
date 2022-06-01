#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "table.h"
#define MAX_LENGTH 20
#define SUPER_ADMIN_USERNAME "admin01"
#define SUPER_ADMIN_PASSWORD "superadmin"
#define CARD_CONFIGURATION_AUTHORITY 0
#define CHARGE_STANDARD_CONFIGURATION_AUTHORITY 1
#define BILLING_AUTHORITY 2
#define FEE_AUTHORITY 3
#define QUERY_STATISTICS_AUTHORITY 4
#define SHOW_AUTHORITY_CONFIGURATION 0
//布尔值枚举定义
typedef enum Bool       
{
    false,
    true
} BOOL;

//卡状态枚举定义
typedef enum CardStatus
{
    online,     //在线
    offline,    //离线
    blocked,    //注销
} CARD_STATUS;

//管理员数据结构
typedef struct Admin 
{
    char number[MAX_LENGTH + 1];      //管理员账号   
    char password[MAX_LENGTH + 1];    //管理员密码
    BOOL is_authority[5];             //管理员权限
    BOOL is_super_admin;              //是否是超级管理员
} ADMIN;

//管理员数据链表
typedef struct AdminNode 
{
    ADMIN date;
    struct AdminNode *next;
} ADMIN_NODE;

//卡数据结构
typedef struct Card
{
    char number[MAX_LENGTH + 1];       //卡号
    char password[MAX_LENGTH + 1];     //卡密码
    char name[MAX_LENGTH + 1];         //卡用户名称
    float balance;                     //卡余额
    CARD_STATUS status;
} CARD;

//卡数据链表
typedef struct CardNode
{
    CARD date;
    struct CardNode *next;
} CARD_NODE;

//计费标准数据结构
typedef struct Standard
{
    int time_length;               //时长   
    float fee;                     //费用
} STANDARD;

//计费标准数据链表
typedef struct StandardNode
{
    STANDARD date;
    struct StandardNode *next;
} STANDARD_NODE;

//时间数据结构
typedef struct Time
{
    int year;                      //年
    int month;                     //月
    int day;                       //日
    int hour;                      //时
} TIME;

//消费记录数据结构
typedef struct Bill
{
    char number[MAX_LENGTH + 1];       //卡号
    int time_length;                   //时长
    float fee;                         //费用
    TIME start_time;                         //时间
    BOOL is_charge;                    //是否已经收费
} BILL;

//消费记录数据链表
typedef struct BillNode
{
    BILL date;
    struct BillNode *next;
} BILL_NODE;

//
//链表读取函数
ADMIN_NODE *admin_get_list();                                               //获取管理员数据链表函数
CARD_NODE *card_get_list();                                                 //获取卡数据链表函数
STANDARD_NODE* standard_get_list();                                         //获取计费标准数据链表函数
BILL_NODE *bill_get_list();                                                 //获取消费记录数据链表函数
//链表保存函数
void admin_save_list(ADMIN_NODE *head);                                     //保存管理员数据链表函数
void card_save_list(CARD_NODE *head_node);                                  //保存卡数据链表函数
void standard_save_list(STANDARD_NODE *head_node);                          //保存计费标准数据链表函数
void bill_save_list(BILL_NODE *head_node);                                  //保存消费记录数据链表函数
//菜单函数
ADMIN admin_login();                                                        //管理员登陆函数
void admin_menu(ADMIN admin);                                               //管理员菜单函数
void super_admin_menu(ADMIN super_admin);                                   //超级管理员菜单函数
void admin_configuration_menu();                                            //配置管理员菜单函数
void card_menu();                                                           //卡管理菜单函数
void fee_menu();                                                            //费用管理菜单函数
void standard_menu();                                                        //计费标准菜单函数
void query_menu();                                                           //查询统计菜单函数
void login_logout_menu();                                                    //上机下机菜单函数
/*----------------------------------------------------------------------————————————------————————————----------------------------------------------------------------------*/
//查重函数
BOOL admin_check_repeat(ADMIN_NODE* head_node,char *number);                //检查管理员是否重复函数
BOOL card_check_repeat(CARD_NODE *head_node, char *number);                 //检查卡是否重复函数
BOOL standard_check_repeat(STANDARD_NODE *head_node, int time_length);      //检查计费标准是否重复函数
//管理员配置功能函数
void admin_add();                                                           //添加管理员函数
void admin_delete();                                                        //删除管理员函数
void admin_modify();                                                        //配置管理员权限函数
//卡管理功能函数
void card_add();                                                            //添加卡函数
void card_cancel();                                                         //注销卡函数
void card_query();                                                          //查询卡函数
//费用管理功能函数
void fee_add();                                                             //充值卡函数
void fee_cancel();                                                          //退费卡函数
//计费标准功能函数
void standard_add();                                                         //添加计费标准函数
void standard_query();                                                       //查询计费标准函数
void standard_delete();                                                      //删除计费标准函数
void standard_modify();                                                      //修改计费标准函数
//消费记录功能函数
void login_card();                                                           //上机卡函数
void logout_card();                                                          //下机卡函数 
//查询统计功能函数
void query_all();                                                            //查询一段时间内的营业额函数
void query_bill();                                                           //查询一个卡的消费记录函数
void query_year();                                                           //查询一年的营业额函数