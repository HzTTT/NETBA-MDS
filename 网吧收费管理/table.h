#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef struct TABLE {
  unsigned int row_num;
  unsigned int col_num;
  unsigned int *col_max_width;
  char ***content;
} table;

extern void format_table(table *t, char *formated_out);
void get_memory(table *t);
void close_memory(table *t);