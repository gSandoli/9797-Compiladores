// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef AST_H // include guard
#define AST_H

#include <string>

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
        LiteralInt(int Val) : Val(Val) { printf("Criado um nó literal inteiro\n"); }
    };

    /// NumberExprAST - Expression class for numeric literals like "1.0".
    class LiteralReal : public Literal
    {
        double Val;

    public:
        LiteralReal(int Val) : Val(Val) { printf("Criado um nó literal real\n"); }
    };

    /// NumberExprAST - Expression class for numeric literals like "1.0".
    class LiteralStr : public Literal
    {
        std::string Val;

    public:
        LiteralStr(std::string Val) : Val(Val) { printf("Criado um nó literal str\n"); }
    };
}

#endif /* AST_H */