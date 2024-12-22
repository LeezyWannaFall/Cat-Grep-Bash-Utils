#include "s21_grep.h"

int main(int argc, char** argv) {
  flags config = flags_parser(argc, argv);
  parserError(config);
  regex_t re;
  int error = regcomp(&re, config.pattern, config.IgnoreRegister);
  regexError(error, config);
  for (int i = optind; i < argc; i++) {
    proccesFile(config, argv[i], &re, argc);
  }
  regfree(&re);
  return 0;
}

flags flags_parser(int argc, char** argv) {
  flags config = {0};
  int opt;
  while ((opt = getopt_long(argc, argv, "e:ivclnhs", NULL, NULL)) != -1) {
    switch (opt) {
      case 'e':
        config.PatternOnly = 1;
        config.pattern = optarg;
        break;
      case 'i':
        config.IgnoreRegister = REG_ICASE;
        break;
      case 'v':
        config.ShowNonPatternOnly = 1;
        break;
      case 'c':
        config.PatternCountOnly = 1;
        break;
      case 'l':
        config.PathPatternOnly = 1;
        break;
      case 'n':
        config.NumericPatternLines = 1;
        break;
      case 'h':
        config.DisablePathOut = 1;
        break;
      case 's':
        config.SkipErrorMessage = 1;
        break;
      default:
        break;
    }
  }
  if (config.pattern == NULL) {
    config.pattern = argv[optind];
    optind++;
  }
  return config;
}

void parserError(flags config) {
  if (!config.pattern) {
    fprintf(stderr, "Error: No pattern provided.\n");
  }
}

void regexError(int error, flags config) {
  if (error) {
    perror("Error compiling regex");
    free(config.pattern);
  }
}

void proccesFile(flags config, char* path, regex_t* reg, int argc) {
  FILE* f = fopen(path, "r");
  if (!f) {
    if (!config.SkipErrorMessage) perror(path);
    return;
  }
  char lineBuffer[2048];
  int line_counter = 0;
  int match_count = 0;
  while (fgets(lineBuffer, sizeof(lineBuffer), f)) {
    line_counter++;
    optionsProccesFile(config, lineBuffer, reg, line_counter, &match_count, path, argc);
  }
  otherFlags(config, path, match_count, argc);
}

void optionsProccesFile(flags config, char* lineBuffer, regex_t* reg, int line_counter, int* match_count, char* path, int argc) {
  size_t len = strlen(lineBuffer);
  int match = regexec(reg, lineBuffer, 0, NULL, 0);
  if (len > 0 && lineBuffer[len - 1] == '\n') lineBuffer[len - 1] = '\0';
  if ((match == 0 && !config.ShowNonPatternOnly) || (match != 0 && config.ShowNonPatternOnly)) {
    (*match_count)++;
    if (config.PatternCountOnly || config.PathPatternOnly) return;
    if (config.NumericPatternLines) {
      if (!config.DisablePathOut && argc > 4) {
        printf("%s:", path);
      }
      printf("%d:", line_counter);
    }
    if ((config.IgnoreRegister || config.PatternOnly || config.SkipErrorMessage || config.ShowNonPatternOnly) && argc > 4) {
      printf("%s:", path);
    }
    printf("%s\n", lineBuffer);
  }
}

void otherFlags(flags config, char* path, int match_count, int argc) {
  if (config.PatternCountOnly) {
    if (!config.DisablePathOut && argc > 4) {
      printf("%s:", path);
    }
    printf("%d\n", match_count);
  }
  if (config.PathPatternOnly && match_count > 0) {
    printf("%s\n", path);
  }
}