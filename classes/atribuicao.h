// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef ATRIBUICAO_H // include guard
#define ATRIBUICAO_H

#include "classes/ast.h"
#include "classes/util/print.h"
#include <string>
using namespace std;
using namespace llvm;

namespace A {
class Atribuicao : public Ast {
public:
  string identifier;
  Ast *exp;

  Atribuicao(int line, int col, string *identifier, Ast *exp)
      : Ast(line, col), identifier(*identifier), exp(exp) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *v = exp->tradutor(context, builder, module, functions, namedValues);

    AllocaInst *A = namedValues[identifier];
    if (!A){
      cerr << "Variável não declarada: " << identifier;
      exit(0);
    }
    
    return builder->CreateStore(v, A);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "Atribuicao(%s,\n", identifier.c_str());
    exp->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};
} // namespace A

#endif /* LITERAL_H */