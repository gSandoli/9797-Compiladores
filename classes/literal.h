// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef LITERAL_H // include guard
#define LITERAL_H

#include <string>
#include <iostream>
#include "ast.h"

using namespace std;

namespace A
{
    class Literal : public Ast
    {
    public:
        Literal() {}
    };

    class LiteralInt : public Literal
    {
        int value;

    public:
        LiteralInt(int value) : value(value)
        {
            cout << "Nó literal (inteiro): " << value << endl;
        }
    };

    class LiteralReal : public Literal
    {
        double value;

    public:
        LiteralReal(double value) : value(value)
        {
            cout << "Nó literal (real): " << value << endl;
        }
    };

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