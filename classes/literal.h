// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef LITERAL_H // include guard
#define LITERAL_H

#include <string>
#include <iostream>
#include "ast.h"
#include "util/print.h"
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

        virtual void print(FILE *out, int d) const = 0;
    };

    class LiteralInteiro : public Literal
    {
    public:
        int value;
        LiteralInteiro(int value) : Literal(INTEIRO), value(value)
        {
            cout << "Nó literal (inteiro): " << value << endl;
        }

        void print(FILE *out, int d) const
        {
            indent(out, d);
            fprintf(out, "LiteralInteiro(%d)", value);
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

        void print(FILE *out, int d) const
        {
            indent(out, d);
            fprintf(out, "LiteralReal(%f)", value);
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

        void print(FILE *out, int d) const
        {
            indent(out, d);
            fprintf(out, "LiteralCadeia(%s)", value.c_str());
        }
    };
}

#endif /* LITERAL_H */