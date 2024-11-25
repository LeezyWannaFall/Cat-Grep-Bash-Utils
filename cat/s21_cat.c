#include "s21_cat.h"

int main(int argc, char* argv[]) {
  flags config = argument_parser(argc, argv);
  output(&config, argv, argc);
  return 0;
}

flags argument_parser(int argc, char* argv[]) {
  flags config = {0};
  struct option long_options[] = {{"number", no_argument, NULL, 'n'},
                                  {"number-nonblank", no_argument, NULL, 'b'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {0, 0, 0, 0}};
  int opt;
  while ((opt = getopt_long(argc, argv, "+bnseETt", long_options, 0)) != -1) {
    switch (opt) {
      case 'b':
        config.NumericNonemptyLines = 1;
        break;
      case 'n':
        config.NumericAllLines = 1;
        break;
      case 's':
        config.SkipEmptyLines = 1;
        break;
      case 'e':
        config.PrintDollar = 1;
        config.InvisibleSymbols = 1;
        break;
      case 'E':
        config.PrintDollar = 1;
        break;
      case 't':
        config.PrintTabs = 1;
        config.InvisibleSymbols = 1;
        break;
      case 'T':
        config.PrintTabs = 1;
        break;
      default:
        break;
    }
  }
  return config;
}

char flag_v(char ch) {
  if (ch == '\n' || ch == '\t') return ch;
  if (ch > 0 && ch <= 31 && ch != 9 && ch != 10) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}

void outline(flags* config, char* line, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (config->PrintTabs && line[i] == '\t') {
      printf("^I");
      continue;
    }
    if (config->PrintDollar && line[i] == '\n') {
      putchar('$');
    }
    if (config->InvisibleSymbols) line[i] = flag_v(line[i]);
    putchar(line[i]);
  }
}

void output(flags* config, char* argv[], int argc) {
  int nonempty_line_count = 0;
  int line_count = 1;
  for (int file_index = optind; file_index < argc; file_index++) {
    FILE* f = fopen(argv[file_index], "r");
    if (!f) {
      perror("Error opening file");
      continue;
    }
    char buffer[1024];
    int empty_count = 0;
    while (fgets(buffer, sizeof(buffer), f)) {
      size_t len = strlen(buffer);
      int empty_line = (len == 1 && buffer[0] == '\n');
      if (empty_line) {
        empty_count++;
      } else {
        empty_count = 0;
      }
      if (config->SkipEmptyLines && empty_count > 1) continue;
      if (config->NumericNonemptyLines && !empty_line) {
        printf("%6d\t", ++nonempty_line_count);
        outline(config, buffer, len);
      } else if (config->NumericAllLines && !config->NumericNonemptyLines) {
        printf("%6d\t", line_count++);
        outline(config, buffer, len);
      } else {
        outline(config, buffer, len);
      }
    }
    fclose(f);
  }
}

