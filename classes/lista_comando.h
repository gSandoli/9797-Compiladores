// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef LISTA_COMANDO_H // include guard
#define LISTA_COMANDO_H

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
      : Ast(line, col), comando(comando), list(list) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    comando->semanticAnalyze(semanticTableFunction);
    if (list != 0) {
      list->semanticAnalyze(semanticTableFunction);
    }
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    comando->tradutor(context, builder, module, functions, namedValues);
    return list->tradutor(context, builder, module, functions, namedValues);
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
#endif /* LISTA_COMANDO_H */