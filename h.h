#ifndef HEADERS_H
#define HEADERS_H
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int file;
  int o;
  int count;
  int f;
  char pattern[10000];
  int file_counter;
} Flags;

int regex(char pattern[], char line[], Flags);
int parse_pattern(int argc, char** argv);
int parse_file_amount(char** argv, int argc);
Flags parse_flags(int argc, char** argv);
int open_file_and_i_flag(FILE** fp, Flags* flag, char** argv, int* eflags);
void grep(Flags flag, FILE* fp, char* line_, char** argv, int y);
void multifileprint(Flags* flag, char* filename);
void flag_e(Flags flag, FILE* fp, int* count, char* line_, char** argv);
void flag_o(char* line_, char pattern[], Flags flag);
void pattern_from_file(char* line_, Flags* flag);
void flag_f(Flags flag, FILE* fp, int* f_count, char*** f_ptrns, int eflags,
            char* line_, char** argv, int file_amount);
void add_pattern(char* pattern, Flags* flag);
#endif
