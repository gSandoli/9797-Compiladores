// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef COMANDO_H // include guard
#define COMANDO_H

#include "ast.h"
#include "atribuicao.h"
#include "literal.h"
#include "util/print.h"
#include <cstddef>
#include <iostream>
#include <string>

using namespace std;

namespace A {
class Comando : public Ast {
public:
  enum Type { ATRIBUICAO, FUNCAO };
  Type type;

  Comando(int line, int col, Type type) : Ast(line, col), type(type) {}
};

class ComandoAtribuicao : public Comando {
public:
  Ast *atribuicao;
  ComandoAtribuicao(int line, int col, string *identifier, Ast *exp)
      : Comando(line, col, ATRIBUICAO),
        atribuicao(new Atribuicao(line, col, identifier, exp)){};

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    atribuicao->semanticAnalyze(semanticTableFunction);
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    return atribuicao->tradutor(context, builder, module, functions,
                                namedValues);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ComandoAtribuicao(\n");
    atribuicao->print(out, d + 1);
    fprintf(out, "\n");
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class ComandoChamadaFuncao : public Comando {
public:
  Ast *chamadaFuncao;
  ComandoChamadaFuncao(int line, int col, Ast *chamadaFuncao)
      : Comando(line, col, FUNCAO), chamadaFuncao(chamadaFuncao){};

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    chamadaFuncao->semanticAnalyze(semanticTableFunction);
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    return chamadaFuncao->tradutor(context, builder, module, functions,
                                   namedValues);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ComandoChamadaFuncao(\n");
    chamadaFuncao->print(out, d + 1);
    fprintf(out, "\n");
    indent(out, d);
    fprintf(out, ")\n");
  }
};
} // namespace A

#endif /* COMANDO_H */