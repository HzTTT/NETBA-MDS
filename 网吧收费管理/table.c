#include "table.h"
#define CORNER_FLAG "+"
#define ROW_LINE "-"
#define COL_PADDING " "
#define COL_LINE "|"

/**
* 计算在控制台中输出的字符串长度
* str 字符串
**/
static int str_len(unsigned char *str)
{
  int len = 0;
  int offset = 2;
  int word_len = strlen((const char *)str);

  for (int i = 0; i < word_len; i++)
  {
    if (str[i] < 128)
    {
      len += 1;
    }
    else
    {
      len += 2;
      i += offset;
    }
  }
  return len;
}
/**
* 生成表格行边
* col_width 表格的列宽
* col_num 表格列数
* edge 保存行边字符串
**/
static void make_edge(const unsigned int *col_width, const unsigned int col_num, char edge[],int number)
{
  memset(edge, 0, sizeof(char)*number);
  strcat(edge, CORNER_FLAG);
  for (unsigned int col_line_counter = 0; col_line_counter < col_num; col_line_counter++)
  {
    strcat(edge, ROW_LINE);
    for (unsigned int row_line_counter = 0; row_line_counter < col_width[col_line_counter]; row_line_counter++)
    {
      strcat(edge, ROW_LINE);
    }
    strcat(edge, ROW_LINE);
    strcat(edge, CORNER_FLAG);
  }
  strcat(edge, "\n");
}

/**
* 根据表格一列的宽度值，求出该列中最大的宽度
* col_width 指向一列所有宽度值数组的指针
* row_num 表格行数
* return 最大宽度值
**/
static int get_max_col_width(int *col_width, const unsigned int row_num)
{
  int max_col_width = 0;
  for (unsigned int i = 0; i < row_num; i++)
  {
    if (max_col_width < col_width[i])
    {
      max_col_width = col_width[i];
    }
  }
  return max_col_width;
}

/**
* 根据表格列的宽度，求出每列最大的宽度
* col_width 指向表格所有列宽度二维数组的指针
* row_num 表格行数
* col_num 表格列数
* max_col_width 指向table结构体中的col_max_width的指针，用于保存表格每列最大的宽度
**/
static void get_max_col(int **col_width, const unsigned int row_num, const unsigned int col_num, int *max_col_width)
{

  for (unsigned int i = 0; i < col_num; i++)
  {
    int max_width[row_num];
    for (unsigned int j = 0; j < row_num; j++)
    {
      max_width[j] = *((int *)col_width + (j * col_num) + i);
    }
    max_col_width[i] = get_max_col_width(max_width, row_num);
  }
}

/**
* 得到表格中所有列的宽度值
* t 指向表格结构体的指针
* col_width 指向表格所有列宽度二维数组的指针，用于保存所有宽度值
**/
static void get_col_width(table *t, int **col_width)
{
  for (unsigned int i = 0; i < t->row_num; i++)
  {
    for (unsigned int j = 0; j < t->col_num; j++)
    {
      *((int *)col_width + i * t->col_num + j) = str_len((unsigned char *)t->content[i][j]);
    }
  }
}

/**
* 设置table结构体中col_max_width
* t 指向表格结构体的指针
**/
static void set_table_col_max_width(table *t)
{
  int col_width[t->row_num][t->col_num];
  get_col_width(t, (int **)col_width);
  get_max_col((int **)col_width, t->row_num, t->col_num, (int *)t->col_max_width);
}

/**
* 得到表格的总宽
* t 指向表格结构体的指针
**/
static int get_table_width(table *t)
{
  int col_padding_width = 2 * t->col_num;
  int col_line_width = t->col_num + 1;
  int col_width = 0;
  for (unsigned int i = 0; i < t->col_num; i++)
  {
    col_width += t->col_max_width[i];
  }
  return col_line_width + col_padding_width + col_width;
}

/**
* 设置格式化表格中的空格
* str 保存的字符串
* space_num 空格的数量
**/
static void set_space_txt(char *str, const unsigned int space_num)
{
  for (unsigned i = 0; i < space_num; i++)
  {
    strcat(str, " ");
  }
}

/**
* 生成表格行边
* row_id 行id
* t 指向表格结构体的指针
* row_txt 格式化输出的表格行边字符串
**/
static void make_row(const unsigned int row_id, table *t, char row_txt[])
{
  memset(row_txt, 0, sizeof(char) * strlen(row_txt));
  strcat(row_txt, COL_LINE);
  for (unsigned int i = 0; i < t->col_num; i++)
  {
    strcat(row_txt, COL_PADDING);
    int word_len = str_len((unsigned char *)t->content[row_id][i]);
    strcat(row_txt, t->content[row_id][i]);
    set_space_txt(row_txt, t->col_max_width[i] - word_len);
    strcat(row_txt, COL_PADDING);
    strcat(row_txt, COL_LINE);
  }
}

void get_memory(table *t)
{
  t->col_max_width = (unsigned int *)malloc(t->col_num * sizeof(unsigned int));
  t->content = (char ***)malloc(t->row_num * sizeof(char **));
  for (unsigned int i = 0; i < t->row_num; i++)
  {
    t->content[i] = (char **)malloc(t->col_num * sizeof(char *));
  }
}

void close_memory(table *t)
{
  for (unsigned int i = 0; i < t->row_num; i++)
  {
    free(t->content[i]);
  }
  free(t->content);
  free(t->col_max_width);
}

/**
* 格式化表格方法
* t 指向表格结构体的指针
* formated_out 格式化输出字符串
**/
void format_table(table *t, char *formated_out)
{
  memset(formated_out, 0, sizeof(char) * 2048);
  set_table_col_max_width(t);
  int col_width = get_table_width(t);
  char row_txt[col_width + t->col_num];

  make_edge(t->col_max_width, t->col_num, row_txt,col_width + t->col_num);
  strcat(formated_out, row_txt);

  for (unsigned int i = 0; i < t->row_num; i++)
  {
    make_row(i, t, row_txt);
    strcat(formated_out, row_txt);
    strcat(formated_out, "\n");
    make_edge(t->col_max_width, t->col_num, row_txt,col_width + t->col_num);
    strcat(formated_out, row_txt);
  }
}