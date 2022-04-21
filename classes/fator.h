// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef FATOR_H // include guard
#define FATOR_H

#include <string>
#include <iostream>
#include "ast.h"
#include "literal.h"
#include "util/print.h"

using namespace std;

namespace A
{
    class Fator : public Ast
    {
    public:
        enum Type
        {
            EXPRESSSAO,
            LITERAL,
            NIL,
            FUNCAO,
            LOCAL_ARMAZENAMENTO
        };
        Type type;

        Fator(Type type) : type(type) {}
    };

    class FatorLiteral : public Fator
    {
    public:
        Literal *literal;
        FatorLiteral(Literal *literal) : Fator(LITERAL), literal(literal)
        {
            if (literal->type == Literal::Type::INTEIRO)
            {
                cout << "Construindo nó fator literal: " << ((LiteralInteiro *)literal)->value << endl;
            }

            if (literal->type == Literal::Type::REAL)
            {
                cout << "Construindo nó fator literal: " << ((LiteralReal *)literal)->value << endl;
            }

            if (literal->type == Literal::Type::CADEIA)
            {
                cout << "Construindo nó fator literal: " << ((LiteralCadeia *)literal)->value << endl;
            }
        }

        void semanticAnalyze(VariableTable variableTable, FunctionTable functionTable) const
        {
            cout << "Análise semântica do nó fator literal" << endl;
            literal->semanticAnalyze(variableTable, functionTable);
        }

        void print(FILE *out, int d) const
        {
            indent(out, d);
            fprintf(out, "FatorLiteral(%d,\n", type);
            literal->print(out, d + 1);
            fprintf(out, ")");
        }
    };
}

#endif /* FATOR_H */