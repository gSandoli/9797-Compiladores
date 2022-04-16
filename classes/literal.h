// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef LITERAL_H // include guard
#define LITERAL_H

#include <string>
#include <iostream>
#include "ast.h"
#include "fator.h"

using namespace std;

namespace AST
{
    class Literal : public Fator
    {
    public:
        Literal() {}
    };

    /// NumberExprAST - Expression class for numeric literals like "1.0".
    class LiteralInt : public Literal
    {
        int value;

    public:
        LiteralInt(int value) : value(value)
        {
            cout << "Nó literal (inteiro): " << value << endl;
        }
    };

    /// NumberExprAST - Expression class for numeric literals like "1.0".
    class LiteralReal : public Literal
    {
        double value;

    public:
        LiteralReal(double value) : value(value)
        {
            cout << "Nó literal (real): " << value << endl;
        }
    };

    /// NumberExprAST - Expression class for numeric literals like "1.0".
    class LiteralStr : public Literal
    {
        string value;

    public:
        LiteralStr(string *value) : value(*value)
        {
            cout << "Nó literal (string): " << *value << endl;
        }
    };
}

#endif /* LITERAL_H */