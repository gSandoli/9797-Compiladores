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
        enum Type
        {
            INTEIRO,
            REAL,
            CADEIA
        };

        Type type;
        Literal(Type type) : type(type) {}
    };

    class LiteralInteiro : public Literal
    {
    public:
        int value;
        LiteralInteiro(int value) : Literal(INTEIRO), value(value)
        {
            cout << "Nó literal (inteiro): " << value << endl;
        }
    };

    class LiteralReal : public Literal
    {
    public:
        double value;
        LiteralReal(double value) : Literal(REAL), value(value)
        {
            cout << "Nó literal (real): " << value << endl;
        }
    };

    class LiteralCadeia : public Literal
    {
    public:
        string value;
        LiteralCadeia(string *value) : Literal(CADEIA), value(*value)
        {
            cout << "Nó literal (string): " << *value << endl;
        }
    };
}

#endif /* LITERAL_H */