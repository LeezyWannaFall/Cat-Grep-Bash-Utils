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
void proccesfile(flags* config, char* buffer, FILE* f, int empty_count, int nonempty_line_count, int line_count);
void process_single_file(flags* config, char* filename, int* nonempty_line_count, int* line_count);
FILE* open_file(const char* filename);
void process_file_contents(flags* config, FILE* f, char* buffer, int* empty_count, 
                         int* nonempty_line_count, int* line_count);
int is_empty_line(const char* buffer, size_t len);
void update_empty_count(int empty_line, int* empty_count);
int should_skip_line(flags* config, int empty_count);
void process_line(flags* config, char* buffer, size_t len, int empty_line, 
                 int* nonempty_line_count, int* line_count);
void print_line_with_number(int number, flags* config, char* buffer, size_t len);
#endif
