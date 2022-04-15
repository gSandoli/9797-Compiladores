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

    class Fator : public ExprAST
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
        LiteralInt(int Val) : Val(Val) { cout << "Criado um nó literal inteiro: " << Val << endl; }
    };

    /// NumberExprAST - Expression class for numeric literals like "1.0".
    class LiteralReal : public Literal
    {
        double Val;

    public:
        LiteralReal(double Val) : Val(Val) { cout << "Criado um nó literal real: " << Val << endl; }
    };

    /// NumberExprAST - Expression class for numeric literals like "1.0".
    class LiteralStr : public Literal
    {
        std::string Val;

    public:
        LiteralStr(std::string Val) : Val(Val) { cout << "Criado um nó literal string: " << Val << endl; }
    };
}

#endif /* AST_H */