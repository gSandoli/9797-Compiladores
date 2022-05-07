// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef FUNCAO_H // include guard
#define FUNCAO_H

#include "ast.h"
#include "fator.h"
#include "literal.h"
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
class Funcao : public Ast {
public:
  string identifier;
  Ast *args;
  Funcao(int line, int col, string *identifier, Ast *args)
      : Ast(line, col), identifier(*identifier), args(args) {}

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    // validando se função existe
    if (!functionTable.exists(identifier)) {
      cerr << "[ERRO SEMÂNTICO] Função não existe: " << identifier;
      printPosition();
      exit(0);
    }

    // validando se função necessita de parâmetros
    if (functionTable.getArgs(identifier) != 0 && args == nullptr) {
      cerr << "[ERRO SEMÂNTICO] Parâmetros faltando: " << identifier;
      printPosition();
      exit(0);
    }

    if (args != nullptr) {
      args->semanticAnalyze(variableTable, functionTable);
      Fator *f = ((Fator *)args);
      if (f->type == Fator::LITERAL) {
        // fazendo cast para literal e verificando tipo de literal
        FatorLiteral *fl = ((FatorLiteral *)f);
        if (((Literal *)fl->literal)->type !=
            functionTable.getArgs(identifier)) {
          cerr << "[ERRO SEMÂNTICO] Tipo de parâmetro incorreto: "
               << identifier;
          printPosition();
          exit(0);
        }
      }
    }
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions) {
    Function *fn = functions.lookup(identifier);
    if (!fn) {
      cerr << "[ERRO DE GERAÇÃO DE CÓDIGO] Função não existe: " << identifier;
      printPosition();
      exit(0);
    }

    std::vector<Type *> Params;
    if (args != nullptr) {
      Fator *f((Fator *)args);
      FatorLiteral *fl = ((FatorLiteral *)f);
      Literal *literal = ((Literal *)fl->literal);

      // verificando tipo do parâmetro
      if (literal->type == Literal::Type::INTEIRO) {
        Params.push_back(Type::getInt64Ty(*context));
      } else if (literal->type == Literal::Type::REAL) {
        Params.push_back(Type::getDoubleTy(*context));
      } else if (literal->type == Literal::Type::CADEIA) {
        Params.push_back(PointerType::getUnqual(Type::getInt8Ty(*context)));
      }
      vector<Value *> ArgsV;
      ArgsV.push_back(fl->tradutor(context, builder, module));
      return builder->CreateCall(fn, ArgsV);
    }

    return builder->CreateCall(fn);
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