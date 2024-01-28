#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "h.h"
#define no_argument 0
#define required_argument 1
#define optional_argument 2
int main(int argc, char *argv[]) {
  if (argc == 1)
    printf(
        "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for "
        "more information.\n");
  else {
    FILE *fp;
    int eflags = 0;

    char *line_ = (char *)malloc(1025 * sizeof(char));
    // printf("Where?\n");
    Flags flag = parse_flags(argc, argv);  // parse flags
    int y = parse_pattern(argc, argv);     // parse pattern

    while (optind < argc) {
      if (open_file_and_i_flag(&fp, &flag, argv, &eflags) == 0) {
        optind++;
        continue;
      }

      grep(flag, fp, line_, argv, y);

      optind++;
    }
    if(optind==argc)printf("ERROR");
    // free(pattern);
    // free(e_ptrns);
    // fclose(fp);
    free(line_);
  }
  return 0;
}
