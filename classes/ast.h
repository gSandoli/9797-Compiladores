// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef AST_H // include guard
#define AST_H

#include <string>
#include <iostream>
using namespace std;

namespace A
{
    class Ast
    {
    public:
        Ast() {}

        virtual void print(FILE *out, int d) const = 0;
    };
}

#endif /* AST_H */