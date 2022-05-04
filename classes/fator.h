// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef FATOR_H // include guard
#define FATOR_H

#include "ast.h"
#include "literal.h"
#include "util/print.h"
#include <iostream>
#include <string>

using namespace std;

namespace A {
class Fator : public Ast {
public:
  enum Type { EXPRESSAO, LITERAL, NIL, FUNCAO, LOCAL_ARMAZENAMENTO };
  Type type;

  Fator(int line, int col, Type type) : Ast(line, col), type(type) {}
};

class FatorLiteral : public Fator {
public:
  Ast *literal;
  FatorLiteral(int line, int col, Ast *literal)
      : Fator(line, col, LITERAL), literal(literal) {
    Literal *fl = ((Literal *)literal);
    if (fl->type == Literal::Type::INTEIRO) {
      cout << "Construindo nó fator literal: " << ((LiteralInteiro *)fl)->value
           << endl;
    }

    if (fl->type == Literal::Type::REAL) {
      cout << "Construindo nó fator literal: " << ((LiteralReal *)fl)->value
           << endl;
    }

    if (fl->type == Literal::Type::CADEIA) {
      cout << "Construindo nó fator literal: " << ((LiteralCadeia *)fl)->value
           << endl;
    }
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó fator literal" << endl;
    literal->semanticAnalyze(variableTable, functionTable);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "FatorLiteral(\n");
    literal->print(out, d + 1);
    fprintf(out, "\n");
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class FatorExpressao : public Fator {
public:
  Ast *expressao;
  FatorExpressao(int line, int col, Ast *expressao)
      : Fator(line, col, EXPRESSAO), expressao(expressao) {
    cout << "Construindo nó fator expressão" << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó fator expressão" << endl;
    expressao->semanticAnalyze(variableTable, functionTable);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "FatorExpressao(\n");
    expressao->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class FatorFuncao : public Fator {
public:
  Ast *funcao;
  FatorFuncao(int line, int col, Ast *funcao)
      : Fator(line, col, FUNCAO), funcao(funcao) {
    cout << "Construindo nó fator função" << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó fator função" << endl;
    funcao->semanticAnalyze(variableTable, functionTable);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "FatorFuncao(\n");
    funcao->print(out, d + 1);
    fprintf(out, "\n");
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class FatorNil : public Fator {
public:
  FatorNil(int line, int col) : Fator(line, col, NIL) {
    cout << "Construindo nó fator nil" << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó fator nil" << endl;
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "FatorNil(NULL)\n");
  }
};
} // namespace A

#endif /* FATOR_H */