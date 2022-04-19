// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef FUNCAO_H // include guard
#define FUNCAO_H

#include <string>
#include <iostream>
#include "ast.h"

using namespace std;

namespace A
{
    class Funcao : public Ast
    {
        string identifier;

    public:
        Funcao(string identifier) : identifier(identifier)
        {
            cout << "Nó chamada de função: " << identifier.c_str() << endl;
        }

        void test()
        {
            cout << "Hello World!\n";
        }
    };
}

#endif /* FUNCAO_H */