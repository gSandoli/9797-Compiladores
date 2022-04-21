// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef AST_H // include guard
#define AST_H

#include <string>
#include <iostream>
#include "util/function_table.h"
#include "util/variable_table.h"

using namespace std;
using namespace T;

namespace A
{
    class Ast
    {
    public:
        Ast() {}

        virtual void print(FILE *out, int d) const = 0;
        virtual void semanticAnalyze(VariableTable variableTable, FunctionTable functionTable) const = 0;
    };
}

#endif /* AST_H */