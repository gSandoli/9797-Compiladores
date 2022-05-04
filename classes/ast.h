// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef AST_H // include guard
#define AST_H

#include "util/function_table.h"
#include "util/variable_table.h"
#include <iostream>
#include <string>

using namespace std;
using namespace T;

namespace A {
class Ast {
public:
  int line;
  int col;

  Ast(int line, int col) : line(line), col(col) {
    cout << line << ":" << col << " ";
  }

  virtual void print(FILE *out, int d) const = 0;
  virtual void semanticAnalyze(VariableTable variableTable,
                               FunctionTable functionTable) const = 0;
  void printPosition() const {
    cout << " (" << line << ":" << col << ")" << endl;
  };
};
} // namespace A

#endif /* AST_H */