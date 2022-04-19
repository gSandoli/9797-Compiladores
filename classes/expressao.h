// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef EXPRESSAO_H // include guard
#define EXPRESSAO_H

#include <string>
#include <iostream>
#include "ast.h"
#include "literal.h"
#include "fator.h"

using namespace std;

namespace A
{
    class Expressao : public Ast
    {
    public:
        Expressao() {}
    };

    class ExpressaoAritmetica_Fator : public Ast
    {
    public:
        Ast *fator;
        ExpressaoAritmetica_Fator(Ast *fator) : fator(fator)
        {
            Fator *f = ((Fator *)fator);
            FatorLiteral *fl = ((FatorLiteral *)fator);
            LiteralInteiro *li = ((LiteralInteiro *)fl->literal);
            cout << "Nó expressao aritmetica_: " << li->value << endl;
        }
    };
}
#endif /* EXPRESSAO_H */