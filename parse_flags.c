#include <string.h>

#include "h.h"
static struct option long_options[] = {{"number-nonblank", no_argument, 0, 'b'},
                                       {0, 0, 0, 0}};
Flags parse_flags(int argc, char **argv) {
  int c;
  Flags flag = {0};
  int option_index = 0;
  if (argc > 1) {
    while (1) {
      c = getopt_long(argc, argv, "e:ivclnhsf:o", long_options, &option_index);
      // printf("optind=%d on argv[%s]\n", optind, argv[optind]);
      if (c == -1) break;

      switch (c) {
        case 'e':
          flag.e = 1;
          add_pattern(optarg, &flag);
          break;
        case 'i':
          flag.i = 1;
          break;
        case 'v':
          flag.v = 1;
          break;
        case 'c':
          flag.c = 1;
          break;
        case 'l':
          flag.l = 1;
          break;
        case 'n':
          flag.n = 1;
          break;
        case 'h':
          flag.h = 1;
          break;
        case 's':
          flag.s = 1;
          break;
        case 'f':
          flag.f = 1;
          pattern_from_file(optarg, &flag);
          // (*e_count)++;
          break;
        case 'o':
          flag.o = 1;
          break;
      }
    }
  }

  flag.file_counter = argc - optind;
  if (!flag.e && !flag.f) {
    if (argc > optind) {
      add_pattern(argv[optind], &flag);
    }

    flag.file_counter--;
  }
  if (flag.v && flag.o) flag.o = 0;
  if (flag.e && flag.o) flag.e = 0;

  return flag;
}
int parse_pattern(int argc, char **argv) {
  int i;
  int pattern;
  for (i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      pattern = i;
      break;
    }

    //             e_ptrns[*count]=argv[i+1];//argv не важно какой
    //             // индекс если мы читаем оттуда, не должно быть segfault?
    //            // printf("argv[%d]=%s\n", i+1, argv[i+1]);
    //             (*count)++;
    //             x=realloc(e_ptrns, *count*(1025*sizeof(char)));
    //             if(x==NULL)printf("Realloc failed");else e_ptrns=x;
    //                                 }

    //     if(argv[i][0]!='-'&&pattern_found==0/*&&strcmp(argv[i-1],
    //     "-e")!=0*/){ pattern=i;pattern_found=1;}
    //     //else if(argv[i][0]=='-')

    // }
  }
  return pattern;
}
int parse_file_amount(char **argv, int argc) {
  int i;
  int y = 0;
  FILE *fptemp;
  for (i = 1; i < argc; i++) {
    fptemp = fopen(argv[i], "r");
    if (fptemp != NULL)
      // if(i==argc-1)
      y++;
  }
  fclose(fptemp);
  // printf("File_name=%s argv index of File_name is %d\n", argv[i], i);
  return y;
}
