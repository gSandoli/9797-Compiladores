// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef COMANDO_H // include guard
#define COMANDO_H

#include "ast.h"
#include "util/print.h"
#include <iostream>
#include <string>

using namespace std;

namespace A {
class ListaComando : public Ast {
public:
  Ast *comando;
  Ast *list;
  ListaComando(int line, int col, Ast *comando, Ast *list)
      : Ast(line, col), comando(comando), list(list) {
    cout << "Construindo nó lista de comando" << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó lista de comando" << endl;
    comando->semanticAnalyze(variableTable, functionTable);
    list->semanticAnalyze(variableTable, functionTable);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ListaComando(\n");
    comando->print(out, d + 1);
    virgula(out, d);
    list->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};
} // namespace A
#endif /* COMANDO_H */