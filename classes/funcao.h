// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef FUNCAO_H // include guard
#define FUNCAO_H

#include <string>
#include <iostream>
#include "ast.h"
#include "fator.h"
#include "literal.h"
#include "util/print.h"

using namespace std;

namespace A
{
    class Funcao : public Ast
    {
    public:
        string identifier;
        Ast *args;
        Funcao(string *identifier, Ast *args) : identifier(*identifier), args(args)
        {
            cout << "Construindo nó chamada de função: " << *identifier << endl;
        }

        void semanticAnalyze(VariableTable variableTable, FunctionTable functionTable) const
        {
            cout << "Análise semântica do nó chamada de função" << endl;
            if (!functionTable.exists(identifier))
            {
                cerr << "[ERRO SEMÂNTICO] Função não existe: " << identifier << endl;
            }
            if (args != nullptr)
            {
                args->semanticAnalyze(variableTable, functionTable);
            }
        }

        void print(FILE *out, int d) const
        {
            indent(out, d);
            if (args != nullptr)
            {
                fprintf(out, "Funcao(%s,\n", identifier.c_str());
                args->print(out, d + 1);
                indent(out, d);
                fprintf(out, ")\n");
            }
            else
            {
                fprintf(out, "Funcao(%s)", identifier.c_str());
            }
        }
    };
}

#endif /* FUNCAO_H */