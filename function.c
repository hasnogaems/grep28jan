#include "h.h"
void add_pattern(char* pattern, Flags* flag) {
  if (strlen(flag->pattern) > 0) strcat(flag->pattern, "|");
  strcat(flag->pattern, pattern);
}

int open_file_and_i_flag(FILE** fp, Flags* flag, char** argv, int* eflags) {
  // printf("in open_file argv[%d]=%s\n", optind, argv[optind]);
  (*fp) = fopen(argv[optind], "r");  // opening file
  if ((*fp) == NULL) {
    //printf("Error opening %s file.\n", argv[optind]);
    return 0;  // debug
  }
  // here we store line from our file we grabbed with fgets
  if (flag->i == 1) {  // no distinction between upper and lowercase characters
    (*eflags) = REG_ICASE;
    // printf("EFLAGS IN MAIN=%d\n", eflags);
  }
  return 1;
}
/* grep_file(){

} */

void pattern_from_file(char* line_, Flags* flag) {
  FILE* pt = NULL;
  pt = fopen(optarg, "r");
  if (pt == NULL)
    printf("in function pattern_file file is not read! optarg=%s", optarg);
  if (pt != NULL) {
    // char string[1024];
    while (fgets(line_, 1024, pt) != NULL) {
      if (line_[strlen(line_) - 1] == '\n') line_[strlen(line_) - 1] = '\0';

      add_pattern(line_, flag);
    }
  } else {
    printf("s21_grep: %s: No such file or directory\n", optarg);
  }
  fclose(pt);
}

void grep(Flags flag, FILE* fp, char* line_, char** argv, int y) {
  if(fp==NULL)
   printf("hello?\n");
  int x = 0;
  int printl=0;
  int c_count = 0;
  int string_counter = 0;

  while (fgets(line_, 1024, fp)) {
    string_counter++;
    x = regex(flag.pattern, line_, flag);
    if (flag.v ? x : !x) {
      c_count++;

      // printf("%d\n", c_count); it enters here only when regex is triggered

      if (flag.l == 1 && flag.c != 1) {
        printf("%s\n", argv[optind]);
        break;
      } else if (flag.l == 1 && flag.c == 1) {
        printl = optind;
      }
      if (flag.o == 1 && flag.c != 1) {
        flag_o(line_, argv[y], flag);
        continue;
      }
      if (flag.c != 1) {
        multifileprint(&flag, argv[optind]);
        if (flag.n == 1) printf("%d:", string_counter);

        printf("%s", line_);
        if (line_[strlen(line_) - 1] != '\n')
          printf("\n");  //если строка из конца файла добавляем \n
      }
    }
  }
  if (flag.c == 1) {
    multifileprint(&flag, argv[optind]);
    printf("%d\n", (flag.l ? 1 : c_count));
  }
  if (flag.c == 1 && flag.l == 1) {
    printf("%s\n", argv[printl]);
  }
  c_count = 0;
  string_counter = 0;

  fclose(fp);
}

void multifileprint(Flags* flag, char* filename) {
  if (flag->file_counter > 1 && flag->h == 0) printf("%s:", filename);
}

void flag_e(Flags flag, FILE* fp, int* count, char* line_, char** argv) {
  // fseek(fp, 0, SEEK_SET);
  int x;
  while (fgets(line_, 1024, fp)) {  // print e patterns
    int loop_count = (*count);
    // while (loop_count > 0) {
    // printf("e_ptrns[loop_count-1]=%s\n", e_ptrns[loop_count-1]);
    x = regex(flag.pattern, line_, flag);
    loop_count--;
    // printf("X in E loop=%d\n", x);
    if (!x) {
      multifileprint(&flag, argv[optind]);
      printf("%s", line_);
    }
  }
  fclose(fp);
}

void flag_o(char* line_, char pattern[], Flags flag) {
  regex_t regex;
  regmatch_t matches[1];

  int return_value =
      regcomp(&regex, pattern, REG_EXTENDED | (flag.i ? REG_ICASE : 0));
  if (return_value) {
    printf("Could not compile regular expression.\n");
  }
  while ((regexec(&regex, line_, 1, matches, 0) == 0)) {
    printf("%.*s\n", (int)(matches[0].rm_eo - matches[0].rm_so),
           line_ + matches[0].rm_so);
    line_ += matches[0].rm_eo;
  }  //первый аргумент это длина паттерна, а второй сдвигает указатель в строке
     //чтобы от стоял на первом чаре, и потом печатает как раз длину паттерна.
     regfree(&regex); //тут был leak
}
