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
    };

    class Program : public Ast
    {
    public:
        Program() {}
    };

    class ListaComando : public Ast
    {
    public:
        ListaComando() {}
    };

    class Comando : public Ast
    {
    public:
        Comando() {}
    };
}

#endif /* AST_H */