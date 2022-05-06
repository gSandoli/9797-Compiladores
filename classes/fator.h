// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef FATOR_H // include guard
#define FATOR_H

#include "ast.h"
#include "literal.h"
#include "util/print.h"
#include <cstddef>
#include <iostream>
#include <llvm-13/llvm/IR/Constants.h>
#include <string>

using namespace std;

namespace A {
class Fator : public Ast {
public:
  enum Type { EXPRESSAO, LITERAL, NIL, FUNCAO, LOCAL_ARMAZENAMENTO };
  Type type;

  Fator(int line, int col, Type type) : Ast(line, col), type(type) {}
  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module);
};

class FatorLiteral : public Fator {
public:
  Ast *literal;
  FatorLiteral(int line, int col, Ast *literal)
      : Fator(line, col, LITERAL), literal(literal) {
    Literal *fl = ((Literal *)literal);
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    literal->semanticAnalyze(variableTable, functionTable);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "FatorLiteral(\n");
    literal->print(out, d + 1);
    fprintf(out, "\n");
    indent(out, d);
    fprintf(out, ")\n");
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder,
                  unique_ptr<Module> &module) {
    Value *v = ((Literal *)literal)->tradutor(context, builder, module);
    return v;
  }
};

class FatorExpressao : public Fator {
public:
  Ast *expressao;
  FatorExpressao(int line, int col, Ast *expressao)
      : Fator(line, col, EXPRESSAO), expressao(expressao) {}

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    expressao->semanticAnalyze(variableTable, functionTable);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "FatorExpressao(\n");
    expressao->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder,
                  unique_ptr<Module> &module) {
    // Value *v = ((Expressao *)expressao)->tradutor(context, builder, module);
    // return v;
    return nullptr;
  }
};

class FatorFuncao : public Fator {
public:
  Ast *funcao;
  FatorFuncao(int line, int col, Ast *funcao)
      : Fator(line, col, FUNCAO), funcao(funcao) {}

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    funcao->semanticAnalyze(variableTable, functionTable);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "FatorFuncao(\n");
    funcao->print(out, d + 1);
    fprintf(out, "\n");
    indent(out, d);
    fprintf(out, ")\n");
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder,
                  unique_ptr<Module> &module) {
    // Value *v = ((Funcao *)funcao)->tradutor(context, builder, module);
    // return v;
    return nullptr;
  }
};

class FatorNil : public Fator {
public:
  FatorNil(int line, int col) : Fator(line, col, NIL) {}

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {}

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "FatorNil(NULL)\n");
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder,
                  unique_ptr<Module> &module) {
    return ConstantPointerNull::get(
        PointerType::getUnqual(StructType::get(*context)));
  }
};
} // namespace A

#endif /* FATOR_H */