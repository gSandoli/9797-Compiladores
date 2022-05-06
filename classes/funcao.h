// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef FUNCAO_H // include guard
#define FUNCAO_H

#include "ast.h"
#include "fator.h"
#include "literal.h"
#include "util/print.h"
#include <iostream>
#include <string>
#include <type_traits>

#include "llvm/ADT/APFloat.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"

using namespace std;
using namespace llvm;

namespace A {
class Funcao : public Ast {
public:
  string identifier;
  Ast *args;
  Funcao(int line, int col, string *identifier, Ast *args)
      : Ast(line, col), identifier(*identifier), args(args) {
    cout << "Construindo nó chamada de função: " << *identifier << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó chamada de função" << endl;
    if (!functionTable.exists(identifier)) {
      cerr << "[ERRO SEMÂNTICO] Função não existe: " << identifier << " ";
      printPosition();
      exit(0);
    }
    if (args != nullptr) {
      args->semanticAnalyze(variableTable, functionTable);
    }
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder,
                  unique_ptr<Module> &module) {
    cout << "Tradutor do nó Chamada de Função" << endl;

    // std::vector<Type *> Ints(1, Type::getInt64Ty(*context));
    std::vector<Type *> Doubles(1, Type::getDoubleTy(*context));
    FunctionType *FT =
        FunctionType::get(Type::getVoidTy(*context), Doubles, false);

    Function *F = Function::Create(FT, Function::ExternalLinkage, "imprimer",
                                   module.get());

    /* Cria um novo vetor de Value com os argumentos*/
    vector<Value *> ArgsV;
    Fator *f((Fator *)args);
    FatorLiteral *fl = ((FatorLiteral *)f);
    LiteralReal *li = ((LiteralReal *)fl->literal);
    ArgsV.push_back(li->tradutor(context, builder, module));
    // cout << "vl: " << vl->getType()->getTypeID() << endl;
    // ArgsV.push_back(vl);

    // retorna a chamada de função
    Value *v = builder->CreateCall(F, ArgsV);
    return v;
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    if (args != nullptr) {
      fprintf(out, "Funcao(%s,\n", identifier.c_str());
      args->print(out, d + 1);
      indent(out, d);
      fprintf(out, ")\n");
    } else {
      fprintf(out, "Funcao(%s)", identifier.c_str());
    }
  }
};
} // namespace A

#endif /* FUNCAO_H */