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

        virtual void print(FILE *out, int d) const = 0;
    };

    class FatorLiteral : public Fator
    {
    public:
        Literal *literal;
        FatorLiteral(Literal *literal) : Fator(LITERAL), literal(literal)
        {
            if (literal->type == Literal::Type::INTEIRO)
            {
                cout << "Nó fator literal: " << ((LiteralInteiro *)literal)->value << endl;
            }

            if (literal->type == Literal::Type::REAL)
            {
                cout << "Nó fator literal: " << ((LiteralReal *)literal)->value << endl;
            }

            if (literal->type == Literal::Type::CADEIA)
            {
                cout << "Nó fator literal: " << ((LiteralCadeia *)literal)->value << endl;
            }
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