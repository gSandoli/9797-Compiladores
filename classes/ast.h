// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef AST_H // include guard
#define AST_H

#include "util/semantic_table_function.h"
#include "util/symboltable.h"
#include <iostream>
#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

using namespace std;
using namespace llvm;

namespace A {
class Ast {
public:
  int line;
  int col;

  Ast(int line, int col) : line(line), col(col) {}

  void printPosition() const {
    cout << " (" << line << ":" << col << ")" << endl;
  };

  virtual Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const = 0;

  virtual Value *tradutor(unique_ptr<LLVMContext> &context,
                          unique_ptr<IRBuilder<>> &builder,
                          unique_ptr<Module> &module,
                          SymbolTable<Function> &functions,
                          map<string, AllocaInst *> &namedValues) const = 0;

  virtual void print(FILE *out, int d) const = 0;
};
} // namespace A

#endif /* AST_H */