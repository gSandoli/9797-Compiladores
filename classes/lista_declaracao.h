// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef LISTA_DECLARACAO_H // include guard
#define LISTA_DECLARACAO_H

#include "ast.h"
#include "declaracao.h"
#include "util/print.h"
#include <iostream>
#include <string>

using namespace std;

namespace A {
class ListaDeclaracao : public Ast {
public:
  Declaracao *declaracao;
  Ast *list;
  ListaDeclaracao(int line, int col, string *identifier, string *type, Ast *exp,
                  Ast *list)
      : Ast(line, col),
        declaracao(new Declaracao(line, col, identifier, type, exp)),
        list(list) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    declaracao->semanticAnalyze(semanticTableFunction);
    if (list != 0) {
      list->semanticAnalyze(semanticTableFunction);
    }
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    declaracao->tradutor(context, builder, module, functions, namedValues);
    return list->tradutor(context, builder, module, functions, namedValues);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ListDeclaracao(\n");
    declaracao->print(out, d + 1);
    virgula(out, d);
    list->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};
} // namespace A
#endif /* LISTA_DECLARACAO_H */