// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef LOCAL_ARMAZENAMENTO_H // include guard
#define LOCAL_ARMAZENAMENTO_H

#include "ast.h"
#include "literal.h"
#include "util/print.h"
#include <cstddef>
#include <iostream>
#include <llvm-13/llvm/IR/Constants.h>
#include <string>

using namespace std;

namespace A {
class LocalArmazenamento : public Ast {
public:
  enum Type { VARIAVEL, STRUCT, VETOR };
  Type type;

  LocalArmazenamento(int line, int col, Type type)
      : Ast(line, col), type(type) {}
};

class VariavelLocalArmazenamento : public LocalArmazenamento {
public:
  string identifier;
  VariavelLocalArmazenamento(int line, int col, string *identifier)
      : LocalArmazenamento(line, col, VARIAVEL), identifier(*identifier) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    // Look this variable up in the function.
    AllocaInst *A = namedValues[identifier];
    if (!A) {
      cerr << "Variável não declarada: " << identifier;
      exit(0);
    }
    // Load the value.
    return builder->CreateLoad(A->getAllocatedType(), A, identifier);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "VariavelLocalArmazenamento(%s)", identifier.c_str());
  }
};

} // namespace A

#endif /* LOCAL_ARMAZENAMENTO_H */