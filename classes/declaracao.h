// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef DECLARACAO_H // include guard
#define DECLARACAO_H

#include "ast.h"
#include "util/print.h"
#include "util/symboltable.h"
#include <cstdlib>
#include <iostream>
#include <memory>
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
      : Ast(line, col), identifier(*identifier), type(*type), exp(exp) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Function *TheFunction = builder->GetInsertBlock()->getParent();

    AllocaInst *Alloca;
    if (type == "inteiro") {
      Alloca = CreateEntryBlockAlloca(TheFunction, identifier, context,
                                      Type::getInt64Ty(*context));
      builder->CreateLoad(Type::getInt64Ty(*context), Alloca,
                          identifier.c_str());
    } else {
      Alloca = CreateEntryBlockAlloca(TheFunction, identifier, context,
                                      Type::getDoubleTy(*context));
      builder->CreateLoad(Type::getDoubleTy(*context), Alloca,
                          identifier.c_str());
    }

    namedValues[identifier] = Alloca;

    Value *auxValor =
        exp->tradutor(context, builder, module, functions, namedValues);

    Value *v = builder->CreateStore(auxValor, Alloca);
    return v;
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "Declaracao(%s,%s,\n", identifier.c_str(), type.c_str());
    virgula(out, d);
    exp->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }

  /// CreateEntryBlockAlloca - Create an alloca instruction in the entry block
  /// of the function.  This is used for mutable variables etc.
  static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction,
                                            StringRef VarName,
                                            unique_ptr<LLVMContext> &context,
                                            Type *tipo) {
    IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                     TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(tipo, nullptr, VarName);
  }
};
} // namespace A

#endif /* DECLARACAO_H */