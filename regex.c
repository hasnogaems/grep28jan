#include <regex.h>
#include <stdio.h>

#include "h.h"
int regex(char pattern[], char line[], Flags flag) {
  // printf("%d", eflags);// тут лезли нули
  regex_t regex={0};
  int return_value =
      regcomp(&regex, pattern, REG_EXTENDED | (flag.i ? REG_ICASE : 0));
  if (return_value) {
    printf("Could not compile regular expression.\n");
  }

  return_value = regexec(&regex, line, 0, NULL, 0);
  if (!return_value) {
  } else {
    // printf("%dNo match.\n",return_value);
  }

  regfree(&regex);
  return return_value;
}
