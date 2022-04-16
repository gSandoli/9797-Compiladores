// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef AST_H // include guard
#define AST_H

#include <string>
#include <iostream>
using namespace std;

namespace AST
{
    class ExprAST
    {
    public:
        virtual ~ExprAST() {}
    };

    class Program : public ExprAST
    {
    public:
        Program() {}
    };

    class ListaComando : public Program
    {
    public:
        ListaComando() {}
    };

    class Comando : public ListaComando
    {
    public:
        Comando() {}
    };
}

#endif /* AST_H */