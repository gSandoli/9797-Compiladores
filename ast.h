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

    class ChamadaFuncao : public Comando
    {
    public:
        ChamadaFuncao() {}
    };

    class ArgsChamada : public ChamadaFuncao
    {
    public:
        ArgsChamada() {}
    };

    class Expr : public ArgsChamada
    {
    public:
        Expr() {}
    };

    class Fator : public Expr
    {
    public:
        Fator() {}
    };

    class Literal : public Fator
    {
    public:
        Literal() {}
    };

    /// NumberExprAST - Expression class for numeric literals like "1.0".
    class LiteralInt : public Literal
    {
        int Val;

    public:
        LiteralInt(int Val) : Val(Val) { cout << "Nó literal (inteiro): " << Val << endl; }
    };

    /// NumberExprAST - Expression class for numeric literals like "1.0".
    class LiteralReal : public Literal
    {
        double Val;

    public:
        LiteralReal(double Val) : Val(Val) { cout << "Nó literal (real): " << Val << endl; }
    };

    /// NumberExprAST - Expression class for numeric literals like "1.0".
    class LiteralStr : public Literal
    {
        string Val;

    public:
        LiteralStr(string Val) : Val(Val) { cout << "Nó literal (string): " << Val << endl; }
    };
}

#endif /* AST_H */