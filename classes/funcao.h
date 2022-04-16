// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef FUNCAO_H // include guard
#define FUNCAO_H

#include <string>
#include <iostream>
#include "ast.h"

using namespace std;

namespace AST
{
    class ChamadaFuncao : public Comando
    {
        string identifier;

    public:
        ChamadaFuncao(string identifier) : identifier(identifier)
        {
            cout << "Nó chamada de função: " << identifier.c_str() << endl;
        }
    };

    class ArgsChamada : public ChamadaFuncao
    {
    public:
        ArgsChamada() : ChamadaFuncao("") {}
    };
}

#endif /* FUNCAO_H */