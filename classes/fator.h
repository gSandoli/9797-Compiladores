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
};

class FatorLiteral : public Fator {
public:
  Ast *literal;
  FatorLiteral(int line, int col, Ast *literal)
      : Fator(line, col, LITERAL), literal(literal) {
    Literal *fl = ((Literal *)literal);
  }

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    literal->semanticAnalyze(semanticTableFunction);
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions) const {
    return literal->tradutor(context, builder, module, functions);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "FatorLiteral(\n");
    literal->print(out, d + 1);
    fprintf(out, "\n");
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class FatorExpressao : public Fator {
public:
  Ast *expressao;
  FatorExpressao(int line, int col, Ast *expressao)
      : Fator(line, col, EXPRESSAO), expressao(expressao) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    expressao->semanticAnalyze(semanticTableFunction);
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions) const {
    return expressao->tradutor(context, builder, module, functions);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "FatorExpressao(\n");
    expressao->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class FatorFuncao : public Fator {
public:
  Ast *funcao;
  FatorFuncao(int line, int col, Ast *funcao)
      : Fator(line, col, FUNCAO), funcao(funcao) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    funcao->semanticAnalyze(semanticTableFunction);
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions) const {
    return funcao->tradutor(context, builder, module, functions);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "FatorFuncao(\n");
    funcao->print(out, d + 1);
    fprintf(out, "\n");
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class FatorNil : public Fator {
public:
  FatorNil(int line, int col) : Fator(line, col, NIL) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions) const {
    return ConstantPointerNull::get(
        PointerType::getUnqual(StructType::get(*context)));
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "FatorNil(NULL)\n");
  }
};

class FatorLocalArmazenamento : public Fator {
public:
  Ast *localDeArmazenamento;
  FatorLocalArmazenamento(int line, int col, Ast *localDeArmazenamento)
      : Fator(line, col, LOCAL_ARMAZENAMENTO),
        localDeArmazenamento(localDeArmazenamento) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions) const {
    return ConstantPointerNull::get(
        PointerType::getUnqual(StructType::get(*context)));
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "FatorLocalArmazenamento(\n");
    localDeArmazenamento->print(out, d + 1);
    fprintf(out, "\n");
    indent(out, d);
    fprintf(out, ")\n");
  }
};
} // namespace A

#endif /* FATOR_H */