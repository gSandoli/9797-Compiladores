// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef EXPRESSAO_H // include guard
#define EXPRESSAO_H

#include "ast.h"
#include "fator.h"
#include "literal.h"
#include "util/print.h"
#include <iostream>
#include <string>

using namespace std;

namespace A {
class Expressao : public Ast {
public:
  enum Type { SOMA, SUBTRACAO, DIVISAO, MULTIPLICACAO };
  Type type;
  Expressao(int line, int col, Type type) : Ast(line, col), type(type) {}
};

class ExpressaoAritmeticaDivisao : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoAritmeticaDivisao(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, DIVISAO), esquerda(esquerda), direita(direita) {
    cout << "Construindo nó expressão aritmética (divisão) " << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó expressão aritmética (divisão) " << endl;
    esquerda->semanticAnalyze(variableTable, functionTable);
    direita->semanticAnalyze(variableTable, functionTable);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoAritmeticaDivisao(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class ExpressaoAritmeticaMultiplicacao : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoAritmeticaMultiplicacao(int line, int col, Ast *esquerda,
                                   Ast *direita)
      : Expressao(line, col, MULTIPLICACAO), esquerda(esquerda),
        direita(direita) {
    cout << "Construindo nó expressão aritmética (multiplicação) " << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó expressão aritmética (multiplicação) "
         << endl;
    esquerda->semanticAnalyze(variableTable, functionTable);
    direita->semanticAnalyze(variableTable, functionTable);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoAritmeticaMultiplicacao(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class ExpressaoAritmeticaSoma : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoAritmeticaSoma(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, SOMA), esquerda(esquerda), direita(direita) {
    cout << "Construindo nó expressão aritmética (soma) " << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó expressão aritmética (soma) " << endl;
    esquerda->semanticAnalyze(variableTable, functionTable);
    direita->semanticAnalyze(variableTable, functionTable);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoAritmeticaSoma(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class ExpressaoAritmeticaSubtracao : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoAritmeticaSubtracao(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, SUBTRACAO), esquerda(esquerda), direita(direita) {
    cout << "Construindo nó expressão aritmética (subtracao) " << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó expressão aritmética (subtracao) " << endl;
    esquerda->semanticAnalyze(variableTable, functionTable);
    direita->semanticAnalyze(variableTable, functionTable);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoAritmeticaSubtracao(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};
} // namespace A
#endif /* EXPRESSAO_H */