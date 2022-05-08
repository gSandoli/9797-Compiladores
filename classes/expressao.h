// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef EXPRESSAO_H // include guard
#define EXPRESSAO_H

#include "ast.h"
#include "classes/chamada_funcao.h"
#include "fator.h"
#include "literal.h"
#include "util/print.h"
#include "llvm/IR/Type.h"
#include <iostream>
#include <string>

using namespace std;

namespace A {
class Expressao : public Ast {
public:
  enum Type {
    FATOR,
    SOMA,
    SUBTRACAO,
    DIVISAO,
    MULTIPLICACAO,
    IGUAL_IGUAL,
    DIFERENTE,
    MAIOR,
    MENOR,
    MAIOR_IGUAL,
    MENOR_IGUAL,
    E,
    OU
  };
  Type type;
  Expressao(int line, int col, Type type) : Ast(line, col), type(type) {}
};

class ExpressaoFator : public Expressao {
public:
  Ast *fator;
  ExpressaoFator(int line, int col, Ast *fator)
      : Expressao(line, col, FATOR), fator(fator) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    fator->semanticAnalyze(semanticTableFunction);
    return ((Ast *)this);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoFator(\n");
    fator->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    return fator->tradutor(context, builder, module, functions, namedValues);
  }
};

class ExpressaoAritmeticaDivisao : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoAritmeticaDivisao(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, DIVISAO), esquerda(esquerda), direita(direita) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoAritmeticaDivisao(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *L =
        esquerda->tradutor(context, builder, module, functions, namedValues);
    Value *R =
        direita->tradutor(context, builder, module, functions, namedValues);
    Value *RL = builder->CreateSIToFP(L, llvm::Type::getDoubleTy(*context));
    Value *DL = builder->CreateSIToFP(R, llvm::Type::getDoubleTy(*context));
    Value *divF = builder->CreateFDiv(RL, DL, "divftmp");
    if (L->getType()->getTypeID() == llvm::Type::IntegerTyID &&
        R->getType()->getTypeID() == llvm::Type::IntegerTyID) {
      return builder->CreateFPToSI(divF, llvm::Type::getInt64Ty(*context),
                                   "divtmp");
    } else {
      return divF;
    }
  }
};

class ExpressaoAritmeticaMultiplicacao : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoAritmeticaMultiplicacao(int line, int col, Ast *esquerda,
                                   Ast *direita)
      : Expressao(line, col, MULTIPLICACAO), esquerda(esquerda),
        direita(direita) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoAritmeticaMultiplicacao(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *L =
        esquerda->tradutor(context, builder, module, functions, namedValues);
    Value *R =
        direita->tradutor(context, builder, module, functions, namedValues);
    if (L->getType()->getTypeID() == llvm::Type::IntegerTyID &&
        R->getType()->getTypeID() == llvm::Type::IntegerTyID) {
      return builder->CreateMul(L, R, "multmp");
    } else {
      return builder->CreateFMul(L, R, "mulftmp");
    }
  }
};

class ExpressaoAritmeticaSoma : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoAritmeticaSoma(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, SOMA), esquerda(esquerda), direita(direita) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *L =
        esquerda->tradutor(context, builder, module, functions, namedValues);
    Value *R =
        direita->tradutor(context, builder, module, functions, namedValues);
    if (L->getType()->getTypeID() == llvm::Type::IntegerTyID &&
        R->getType()->getTypeID() == llvm::Type::IntegerTyID) {
      return builder->CreateAdd(L, R, "addtmp");
    } else {
      return builder->CreateFAdd(L, R, "addftmp");
    }
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoAritmeticaSoma(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class ExpressaoAritmeticaSubtracao : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoAritmeticaSubtracao(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, SUBTRACAO), esquerda(esquerda), direita(direita) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *L =
        esquerda->tradutor(context, builder, module, functions, namedValues);
    Value *R =
        direita->tradutor(context, builder, module, functions, namedValues);
    if (L->getType()->getTypeID() == llvm::Type::IntegerTyID &&
        R->getType()->getTypeID() == llvm::Type::IntegerTyID) {
      return builder->CreateSub(L, R, "subtmp");
    } else {
      return builder->CreateFSub(L, R, "subftmp");
    }
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoAritmeticaSubtracao(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};
class ExpressaoRelacionalIgual : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoRelacionalIgual(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, IGUAL_IGUAL), esquerda(esquerda),
        direita(direita) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *L =
        esquerda->tradutor(context, builder, module, functions, namedValues);
    Value *R =
        direita->tradutor(context, builder, module, functions, namedValues);
    return builder->CreateZExt(builder->CreateICmpEQ(L, R, "cmptmp"),
                               llvm::Type::getInt64Ty(*context), "cmptmp");
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoRelacionalIgual(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};
class ExpressaoRelacionalDiferente : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoRelacionalDiferente(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, DIFERENTE), esquerda(esquerda), direita(direita) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *L =
        esquerda->tradutor(context, builder, module, functions, namedValues);
    Value *R =
        direita->tradutor(context, builder, module, functions, namedValues);
    return builder->CreateZExt(builder->CreateICmpNE(L, R, "cmptmp"),
                               llvm::Type::getInt64Ty(*context), "cmptmp");
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoRelacionalIgual(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class ExpressaoRelacionalMaior : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoRelacionalMaior(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, MAIOR), esquerda(esquerda), direita(direita) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *L =
        esquerda->tradutor(context, builder, module, functions, namedValues);
    Value *R =
        direita->tradutor(context, builder, module, functions, namedValues);
    return builder->CreateZExt(builder->CreateICmpSGT(L, R, "cmptmp"),
                               llvm::Type::getInt64Ty(*context), "cmptmp");
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoRelacionalMaior(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class ExpressaoRelacionalMenor : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoRelacionalMenor(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, MENOR), esquerda(esquerda), direita(direita) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *L =
        esquerda->tradutor(context, builder, module, functions, namedValues);
    Value *R =
        direita->tradutor(context, builder, module, functions, namedValues);
    return builder->CreateZExt(builder->CreateICmpSLT(L, R, "cmptmp"),
                               llvm::Type::getInt64Ty(*context), "cmptmp");
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoRelacionalMenor(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class ExpressaoRelacionalMaiorIgual : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoRelacionalMaiorIgual(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, MAIOR_IGUAL), esquerda(esquerda),
        direita(direita) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *L =
        esquerda->tradutor(context, builder, module, functions, namedValues);
    Value *R =
        direita->tradutor(context, builder, module, functions, namedValues);
    return builder->CreateZExt(builder->CreateICmpSGE(L, R, "cmptmp"),
                               llvm::Type::getInt64Ty(*context), "cmptmp");
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoRelacionalMaiorIgual(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class ExpressaoRelacionalMenorIgual : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoRelacionalMenorIgual(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, MENOR_IGUAL), esquerda(esquerda),
        direita(direita) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *L =
        esquerda->tradutor(context, builder, module, functions, namedValues);
    Value *R =
        direita->tradutor(context, builder, module, functions, namedValues);
    return builder->CreateZExt(builder->CreateICmpSLE(L, R, "cmptmp"),
                               llvm::Type::getInt64Ty(*context), "cmptmp");
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoRelacionalMenorIgual(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class ExpressaoLogicaE : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoLogicaE(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, E), esquerda(esquerda), direita(direita) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *L =
        esquerda->tradutor(context, builder, module, functions, namedValues);
    Value *R =
        direita->tradutor(context, builder, module, functions, namedValues);
    return builder->CreateAnd(L, R, "andtmp");
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoLogicaE(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class ExpressaoLogicaOU : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoLogicaOU(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, E), esquerda(esquerda), direita(direita) {}

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *L =
        esquerda->tradutor(context, builder, module, functions, namedValues);
    Value *R =
        direita->tradutor(context, builder, module, functions, namedValues);
    return builder->CreateOr(L, R, "andtmp");
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ExpressaoLogicaOU(\n");
    esquerda->print(out, d + 1);
    virgula(out, d);
    direita->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};
} // namespace A
#endif /* EXPRESSAO_H */