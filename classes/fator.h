// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef FATOR_H // include guard
#define FATOR_H

#include <string>
#include <iostream>
#include "ast.h"
#include "literal.h"
#include "util/print.h"

using namespace std;

namespace A
{
    class Fator : public Ast
    {
    public:
        enum Type
        {
            EXPRESSAO,
            LITERAL,
            NIL,
            FUNCAO,
            LOCAL_ARMAZENAMENTO
        };
        Type type;

        Fator(Type type) : type(type) {}
    };

    class FatorLiteral : public Fator
    {
    public:
        Ast *literal;
        FatorLiteral(Ast *literal) : Fator(LITERAL), literal(literal)
        {
            Literal *fl = ((Literal *)literal);
            if (fl->type == Literal::Type::INTEIRO)
            {
                cout << "Construindo nó fator literal: " << ((LiteralInteiro *)fl)->value << endl;
            }

            if (fl->type == Literal::Type::REAL)
            {
                cout << "Construindo nó fator literal: " << ((LiteralReal *)fl)->value << endl;
            }

            if (fl->type == Literal::Type::CADEIA)
            {
                cout << "Construindo nó fator literal: " << ((LiteralCadeia *)fl)->value << endl;
            }
        }

        void semanticAnalyze(VariableTable variableTable, FunctionTable functionTable) const
        {
            cout << "Análise semântica do nó fator literal" << endl;
            literal->semanticAnalyze(variableTable, functionTable);
        }

        void print(FILE *out, int d) const
        {
            indent(out, d);
            fprintf(out, "FatorLiteral(\n");
            literal->print(out, d + 1);
            fprintf(out, "\n");
            indent(out, d);
            fprintf(out, ")\n");
        }
    };

    class FatorExpressao : public Fator
    {
    public:
        Ast *expressao;
        FatorExpressao(Ast *expressao) : Fator(EXPRESSAO), expressao(expressao)
        {
            cout << "Construindo nó fator expressão" << endl;
        }

        void semanticAnalyze(VariableTable variableTable, FunctionTable functionTable) const
        {
            cout << "Análise semântica do nó fator expressão" << endl;
            expressao->semanticAnalyze(variableTable, functionTable);
        }

        void print(FILE *out, int d) const
        {
            indent(out, d);
            fprintf(out, "FatorExpressao(\n");
            expressao->print(out, d + 1);
            indent(out, d);
            fprintf(out, ")\n");
        }
    };

    class FatorFuncao : public Fator
    {
    public:
        Ast *funcao;
        FatorFuncao(Ast *funcao) : Fator(FUNCAO), funcao(funcao)
        {
            cout << "Construindo nó fator função" << endl;
        }

        void semanticAnalyze(VariableTable variableTable, FunctionTable functionTable) const
        {
            cout << "Análise semântica do nó fator função" << endl;
            funcao->semanticAnalyze(variableTable, functionTable);
        }

        void print(FILE *out, int d) const
        {
            indent(out, d);
            fprintf(out, "FatorFuncao(\n");
            funcao->print(out, d + 1);
            fprintf(out, "\n");
            indent(out, d);
            fprintf(out, ")\n");
        }
    };

    class FatorNil : public Fator
    {
    public:
        FatorNil() : Fator(NIL)
        {
            cout << "Construindo nó fator nil" << endl;
        }

        void semanticAnalyze(VariableTable variableTable, FunctionTable functionTable) const
        {
            cout << "Análise semântica do nó fator nil" << endl;
        }

        void print(FILE *out, int d) const
        {
            indent(out, d);
            fprintf(out, "FatorNil(NULL)\n");
        }
    };
}

#endif /* FATOR_H */