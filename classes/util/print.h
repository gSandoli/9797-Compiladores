#ifndef PRINT_HELPER_H
#define PRINT_HELPER_H
inline void indent(FILE *out, int d)
{
    for (int i = 0; i <= d; i++)
        fprintf(out, " ");
}
#endif