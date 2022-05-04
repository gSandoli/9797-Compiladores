// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef LITERAL_H // include guard
#define LITERAL_H

#include "ast.h"
#include "util/print.h"
#include <iostream>
#include <string>

using namespace std;
namespace A {
class Literal : public Ast {
public:
  enum Type { INTEIRO, REAL, CADEIA };

  Type type;

  Literal(int line, int col, Type type) : Ast(line, col), type(type) {}
};

class LiteralInteiro : public Literal {
public:
  int value;
  LiteralInteiro(int line, int col, int value)
      : Literal(line, col, INTEIRO), value(value) {
    cout << "Construindo nó literal (inteiro): " << value << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó literal (inteiro)" << endl;
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "LiteralInteiro(%d)", value);
  }
};

class LiteralReal : public Literal {
public:
  double value;
  LiteralReal(int line, int col, double value)
      : Literal(line, col, REAL), value(value) {
    cout << "Construindo nó literal (real): " << value << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {}

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "LiteralReal(%f)", value);
  }
};

class LiteralCadeia : public Literal {
public:
  string value;
  LiteralCadeia(int line, int col, string *value)
      : Literal(line, col, CADEIA), value(*value) {
    cout << "Construindo nó literal (string): " << *value << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {}

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "LiteralCadeia(%s)", value.c_str());
  }
};
} // namespace A

#endif /* LITERAL_H */