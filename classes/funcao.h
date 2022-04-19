// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef FUNCAO_H // include guard
#define FUNCAO_H

#include <string>
#include <iostream>
#include "ast.h"
#include "fator.h"
#include "literal.h"

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
            Fator *f = ((Fator *)args);
            FatorLiteral *fl = ((FatorLiteral *)f);
            LiteralInteiro *li = ((LiteralInteiro *)fl->literal);

            cout << "Nó chamada de função:" << endl;
            cout << "\tChamada: " << *identifier << endl;
            cout << "\tArgs: " << li->value << endl;
        }
    };
}

#endif /* FUNCAO_H */