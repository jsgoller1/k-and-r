#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "tabber.h"

int main(int argc, char** argv) {
  int len = 0;                  // current line length
  char line[MAXLEN] = {0};      // current input line
  char* processed_line = NULL;  // line after entabing / detabing
  int* tab_stops = NULL;        // list of tab stops
  int tab_stops_len = 0;
  char* (*behavior)(const char* const, const int, const int* const,
                    const int);  // detab or entab, depending on flags

  // handle input
  switch (parse_flags(argc, argv, &tab_stops, &tab_stops_len)) {
    case USE_ENTAB:
      behavior = entab;
      break;
    case USE_DETAB:
      behavior = detab;
      break;
    default:
      if (tab_stops != NULL) {
        free(tab_stops);
      }
      return -1;
  }

  // do the thing
  while ((len = mygetline(line, MAXLEN)) > 0) {
    processed_line = behavior(line, len, tab_stops, tab_stops_len);
    printf("%s\n", processed_line);
    free(processed_line);
  }

  free(tab_stops);
  return 0;
}
