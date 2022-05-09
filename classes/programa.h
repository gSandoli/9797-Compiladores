// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef PROGRAMA_H // include guard
#define PROGRAMA_H

#include "ast.h"
#include "util/print.h"
#include "util/symboltable.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <type_traits>

#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"

using namespace std;
using namespace llvm;

namespace A {
class Programa : public Ast {
public:
  Ast *declaracoes;
  Ast *acoes;
  Programa(int line, int col, Ast *declaracoes, Ast *acoes)
      : Ast(line, col), declaracoes(declaracoes), acoes(acoes) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    if (declaracoes) {
      declaracoes->tradutor(context, builder, module, functions, namedValues);
    }
    return acoes->tradutor(context, builder, module, functions, namedValues);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "Programa(\n");
    indent(out, d);
    if (declaracoes) {
      declaracoes->print(out, d + 1);
      virgula(out, d);
    }
    acoes->print(out, d + 1);
    fprintf(out, ")\n");
  }
};
} // namespace A

#endif /* PROGRAMA_H */