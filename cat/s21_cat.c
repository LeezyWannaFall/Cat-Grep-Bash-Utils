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
        process_single_file(config, argv[file_index], &nonempty_line_count, &line_count);
    }
}
#
void process_single_file(flags* config, char* filename, int* nonempty_line_count, int* line_count) {
    FILE* f = open_file(filename);
    if (!f) return;
    
    char buffer[1024];
    int empty_count = 0;
    process_file_contents(config, f, buffer, &empty_count, nonempty_line_count, line_count);
    fclose(f);
}

FILE* open_file(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        perror("Error opening file");
    }
    return f;
}

void process_file_contents(flags* config, FILE* f, char* buffer, int* empty_count, 
                         int* nonempty_line_count, int* line_count) {
    while (fgets(buffer, 1024, f)) {
        size_t len = strlen(buffer);
        int empty_line = is_empty_line(buffer, len);
        
        update_empty_count(empty_line, empty_count);
        if (should_skip_line(config, *empty_count)) continue;
        
        process_line(config, buffer, len, empty_line, nonempty_line_count, line_count);
    }
}

int is_empty_line(const char* buffer, size_t len) {
    return (len == 1 && buffer[0] == '\n');
}

void update_empty_count(int empty_line, int* empty_count) {
    if (empty_line) {
        (*empty_count)++;
    } else {
        *empty_count = 0;
    }
}

int should_skip_line(flags* config, int empty_count) {
    return (config->SkipEmptyLines && empty_count > 1);
}

void process_line(flags* config, char* buffer, size_t len, int empty_line, 
                 int* nonempty_line_count, int* line_count) {
    if (config->NumericNonemptyLines && !empty_line) {
        print_line_with_number(++(*nonempty_line_count), config, buffer, len);
    } else if (config->NumericAllLines && !config->NumericNonemptyLines) {
        print_line_with_number((*line_count)++, config, buffer, len);
    } else {
        outline(config, buffer, len);
    }
}

void print_line_with_number(int number, flags* config, char* buffer, size_t len) {
    printf("%6d\t", number);
    outline(config, buffer, len);
}