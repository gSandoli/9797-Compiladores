// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef DECLARACAO_H // include guard
#define DECLARACAO_H

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
class Declaracao : public Ast {
public:
  string identifier;
  string type;
  Ast *exp;
  Declaracao(int line, int col, string *identifier, string *type, Ast *exp)
      : Ast(line, col), identifier(*identifier), type(*type), exp(exp) {
    cout << "criando declaração " << identifier << " do tipo " << type << endl;
  }

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions) const {
    return exp->tradutor(context, builder, module, functions);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "Declaracao(%s,\n", identifier.c_str());
    indent(out, d);
    fprintf(out, "%s\n", type.c_str());
    virgula(out, d);
    exp->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};
} // namespace A

#endif /* DECLARACAO_H */