// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef FATOR_H // include guard
#define FATOR_H

#include <string>
#include <iostream>
#include "ast.h"
#include "literal.h"

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
            cout << "Nó fator literal: " << ((LiteralInteiro *)literal)->value << endl;
        }
    };
}

#endif /* FATOR_H */