#ifndef S_21_GREP
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flags {
  int PatternOnly, IgnoreRegister, ShowNonPatternOnly, PatternCountOnly, PathPatternOnly, NumericPatternLines, DisablePathOut, SkipErrorMessage;
  char* pattern;
} flags;

flags flags_parser(int argc, char** argv);
void proccesFile(flags config, char* path, regex_t* reg, int argc);
#endif