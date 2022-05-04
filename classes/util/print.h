#ifndef PRINT_HELPER_H
#define PRINT_HELPER_H
#include <stdio.h>

inline void indent(FILE *out, int d) {
  for (int i = 0; i <= d; i++)
    fprintf(out, "  ");
}
inline void virgula(FILE *out, int d) {
  indent(out, d);
  fprintf(out, "  ,\n");
}
#endif