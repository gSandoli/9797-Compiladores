// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef EXPRESSAO_H // include guard
#define EXPRESSAO_H

#include <string>
#include <iostream>
#include "ast.h"
#include "literal.h"
#include "fator.h"
#include "util/print.h"

using namespace std;

namespace A
{
    class Expressao : public Ast
    {
    public:
        enum Type
        {
            SOMA,
            SUBTRACAO,
            DIVISAO,
            MULTIPLICACAO
        };
        Type type;
        Expressao(Type type) : type(type) {}
    };

    class ExpressaoAritmeticaDivisao : public Expressao
    {
    public:
        Ast *esquerda;
        Ast *direita;
        ExpressaoAritmeticaDivisao(Ast *esquerda, Ast *direita) : Expressao(DIVISAO), esquerda(esquerda), direita(direita)
        {
            cout << "Construindo nó expressão aritmética (divisão) " << endl;
        }

        void semanticAnalyze(VariableTable variableTable, FunctionTable functionTable) const
        {
            cout << "Análise semântica do nó expressão aritmética (divisão) " << endl;
            esquerda->semanticAnalyze(variableTable, functionTable);
            direita->semanticAnalyze(variableTable, functionTable);
        }

        void print(FILE *out, int d) const
        {
            indent(out, d);
            fprintf(out, "ExpressaoAritmeticaDivisao(\n");
            esquerda->print(out, d + 1);
            virgula(out, d);
            direita->print(out, d + 1);
            indent(out, d);
            fprintf(out, ")\n");
        }
    };

    class ExpressaoAritmeticaMultiplicacao : public Expressao
    {
    public:
        Ast *esquerda;
        Ast *direita;
        ExpressaoAritmeticaMultiplicacao(Ast *esquerda, Ast *direita) : Expressao(MULTIPLICACAO), esquerda(esquerda), direita(direita)
        {
            cout << "Construindo nó expressão aritmética (multiplicação) " << endl;
        }

        void semanticAnalyze(VariableTable variableTable, FunctionTable functionTable) const
        {
            cout << "Análise semântica do nó expressão aritmética (multiplicação) " << endl;
            esquerda->semanticAnalyze(variableTable, functionTable);
            direita->semanticAnalyze(variableTable, functionTable);
        }

        void print(FILE *out, int d) const
        {
            indent(out, d);
            fprintf(out, "ExpressaoAritmeticaMultiplicacao(\n");
            esquerda->print(out, d + 1);
            virgula(out, d);
            direita->print(out, d + 1);
            indent(out, d);
            fprintf(out, ")\n");
        }
    };

    class ExpressaoAritmeticaSoma : public Expressao
    {
    public:
        Ast *esquerda;
        Ast *direita;
        ExpressaoAritmeticaSoma(Ast *esquerda, Ast *direita) : Expressao(SOMA), esquerda(esquerda), direita(direita)
        {
            cout << "Construindo nó expressão aritmética (soma) " << endl;
        }

        void semanticAnalyze(VariableTable variableTable, FunctionTable functionTable) const
        {
            cout << "Análise semântica do nó expressão aritmética (soma) " << endl;
            esquerda->semanticAnalyze(variableTable, functionTable);
            direita->semanticAnalyze(variableTable, functionTable);
        }

        void print(FILE *out, int d) const
        {
            indent(out, d);
            fprintf(out, "ExpressaoAritmeticaSoma(\n");
            esquerda->print(out, d + 1);
            virgula(out, d);
            direita->print(out, d + 1);
            indent(out, d);
            fprintf(out, ")\n");
        }
    };

    class ExpressaoAritmeticaSubtracao : public Expressao
    {
    public:
        Ast *esquerda;
        Ast *direita;
        ExpressaoAritmeticaSubtracao(Ast *esquerda, Ast *direita) : Expressao(SUBTRACAO), esquerda(esquerda), direita(direita)
        {
            cout << "Construindo nó expressão aritmética (subtracao) " << endl;
        }

        void semanticAnalyze(VariableTable variableTable, FunctionTable functionTable) const
        {
            cout << "Análise semântica do nó expressão aritmética (subtracao) " << endl;
            esquerda->semanticAnalyze(variableTable, functionTable);
            direita->semanticAnalyze(variableTable, functionTable);
        }

        void print(FILE *out, int d) const
        {
            indent(out, d);
            fprintf(out, "ExpressaoAritmeticaSubtracao(\n");
            esquerda->print(out, d + 1);
            virgula(out, d);
            direita->print(out, d + 1);
            indent(out, d);
            fprintf(out, ")\n");
        }
    };
}
#endif /* EXPRESSAO_H */