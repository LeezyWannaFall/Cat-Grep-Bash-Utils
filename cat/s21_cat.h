#ifndef S21_CAT
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE

typedef struct flags {
  int NumericNonemptyLines, NumericAllLines, SkipEmptyLines, PrintDollar, PrintTabs, InvisibleSymbols;
} flags;

flags argument_parser(int argc, char* argv[]);
char flag_v(char ch);
void outline(flags* arg, char* line, size_t len);
void output(flags* arg, char* argv[], int argc);
void FlagsProcces(flags* config, int empty_count, int empty_line, int nonempty_line_count, int line_count, char buffer[], size_t len);
#endif