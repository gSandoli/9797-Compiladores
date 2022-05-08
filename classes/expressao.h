// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef EXPRESSAO_H // include guard
#define EXPRESSAO_H

#include "ast.h"
#include "classes/chamada_funcao.h"
#include "fator.h"
#include "literal.h"
#include "util/print.h"
#include <iostream>
#include <string>

using namespace std;

namespace A {
class Expressao : public Ast {
public:
  enum Type { FATOR, SOMA, SUBTRACAO, DIVISAO, MULTIPLICACAO };
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
    cout << "Análise semântica do nó expressão aritmética (divisão) " << endl;
    /*
esquerda->semanticAnalyze(semanticTableFunction);
direita->semanticAnalyze(semanticTableFunction);

Fator *fesq = ((Fator *)esquerda);
Fator *fdir = ((Fator *)direita);
if (fesq->type == Fator::FUNCAO && fdir->type == Fator::LITERAL) {
  FatorFuncao *fafuesq = ((FatorFuncao *)fesq);
  Funcao *fuesq = ((Funcao *)fafuesq->funcao);
  FatorLiteral *fldir = ((FatorLiteral *)fdir);
  Literal *ldir = ((Literal *)fldir->literal);

  if (functionTable.getType(fuesq->identifier) == 3) {
    cerr << "[ERRO SEMÂNTICO] Tipo void em divisão";
    printPosition();
    exit(0);
  }

  if (functionTable.getType(fuesq->identifier) != ldir->type) {
    cerr << "[ERRO SEMÂNTICO] Tipos diferentes em divisão";
    printPosition();
    exit(0);
  }
}

if (fesq->type == Fator::LITERAL && fdir->type == Fator::FUNCAO) {

  FatorLiteral *flesq = ((FatorLiteral *)fesq);
  Literal *lesq = ((Literal *)flesq->literal);
  FatorFuncao *fafudir = ((FatorFuncao *)fdir);
  Funcao *fudir = ((Funcao *)fafudir->funcao);

  if (functionTable.getType(fudir->identifier) == 3) {
    cerr << "[ERRO SEMÂNTICO] Tipo void em divisão";
    printPosition();
    exit(0);
  }

  if (lesq->type != functionTable.getType(fudir->identifier)) {
    cerr << "[ERRO SEMÂNTICO] Tipos diferentes em divisão";
    printPosition();
    exit(0);
  }
}

if (fesq->type == Fator::FUNCAO && fdir->type == Fator::FUNCAO) {

  FatorFuncao *fafuesq = ((FatorFuncao *)fesq);
  Funcao *fuesq = ((Funcao *)fafuesq->funcao);
  FatorFuncao *fafudir = ((FatorFuncao *)fdir);
  Funcao *fudir = ((Funcao *)fafudir->funcao);

  if (functionTable.getType(fuesq->identifier) == 3 ||
      functionTable.getType(fudir->identifier) == 3) {
    cerr << "[ERRO SEMÂNTICO] Tipo void em divisão";
    printPosition();
    exit(0);
  }

  if (functionTable.getType(fuesq->identifier) !=
      functionTable.getType(fudir->identifier)) {
    cerr << "[ERRO SEMÂNTICO] Tipos diferentes em divisão";
    printPosition();
    exit(0);
  }
}

if (fesq->type == Fator::NIL || fdir->type == Fator::NIL) {
  cerr << "[ERRO SEMÂNTICO] Operação (divisão) com valor nulo";
  printPosition();
  exit(0);
}

if (fesq->type == Fator::LITERAL && fdir->type == Fator::LITERAL) {

  FatorLiteral *flesq = ((FatorLiteral *)fesq);
  FatorLiteral *fldir = ((FatorLiteral *)fdir);
  Literal *lesq = ((Literal *)flesq->literal);
  Literal *ldir = ((Literal *)fldir->literal);

  if (lesq->type != ldir->type) {
    cerr << "[ERRO SEMÂNTICO] Tipos diferentes em divisão";
    printPosition();
    exit(0);
  }

  if (ldir->type == Literal::INTEIRO &&
      ((LiteralInteiro *)ldir)->value == 0) {
    cerr << "[ERRO SEMÂNTICO] Divisão por 0";
    printPosition();
    exit(0);
  }
  if (ldir->type == Literal::REAL && ((LiteralReal *)ldir)->value == 0.0) {
    cerr << "[ERRO SEMÂNTICO] Divisão por 0.0";
    printPosition();
    exit(0);
  }
}*/
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
    cout << "Análise semântica do nó expressão aritmética (multiplicação) "
         << endl;
    /*
esquerda->semanticAnalyze(semanticTableFunction);
direita->semanticAnalyze(semanticTableFunction);

Fator *fesq = ((Fator *)esquerda);
Fator *fdir = ((Fator *)direita);
if (fesq->type == Fator::FUNCAO && fdir->type == Fator::LITERAL) {
 FatorFuncao *fafuesq = ((FatorFuncao *)fesq);
 Funcao *fuesq = ((Funcao *)fafuesq->funcao);
 FatorLiteral *fldir = ((FatorLiteral *)fdir);
 Literal *ldir = ((Literal *)fldir->literal);

 if (functionTable.getType(fuesq->identifier) == 3) {
   cerr << "[ERRO SEMÂNTICO] Tipos void em multiplicação";
   printPosition();
   exit(0);
 }

 if (functionTable.getType(fuesq->identifier) != ldir->type) {
   cerr << "[ERRO SEMÂNTICO] Tipos diferentes em multiplicação";
   printPosition();
   exit(0);
 }
}

if (fesq->type == Fator::LITERAL && fdir->type == Fator::FUNCAO) {

 FatorLiteral *flesq = ((FatorLiteral *)fesq);
 Literal *lesq = ((Literal *)flesq->literal);
 FatorFuncao *fafudir = ((FatorFuncao *)fdir);
 Funcao *fudir = ((Funcao *)fafudir->funcao);

 if (functionTable.getType(fudir->identifier) == 3) {
   cerr << "[ERRO SEMÂNTICO] Tipos void em multiplicação";
   printPosition();
   exit(0);
 }

 if (lesq->type != functionTable.getType(fudir->identifier)) {
   cerr << "[ERRO SEMÂNTICO] Tipos diferentes em multiplicação";
   printPosition();
   exit(0);
 }
}

if (fesq->type == Fator::FUNCAO && fdir->type == Fator::FUNCAO) {

 FatorFuncao *fafuesq = ((FatorFuncao *)fesq);
 Funcao *fuesq = ((Funcao *)fafuesq->funcao);
 FatorFuncao *fafudir = ((FatorFuncao *)fdir);
 Funcao *fudir = ((Funcao *)fafudir->funcao);

 if (functionTable.getType(fuesq->identifier) == 3 ||
     functionTable.getType(fudir->identifier) == 3) {
   cerr << "[ERRO SEMÂNTICO] Tipos void em multiplicação";
   printPosition();
   exit(0);
 }

 if (functionTable.getType(fuesq->identifier) !=
     functionTable.getType(fudir->identifier)) {
   cerr << "[ERRO SEMÂNTICO] Tipos diferentes em multiplicação";
   printPosition();
   exit(0);
 }
}

if (fesq->type == Fator::NIL || fdir->type == Fator::NIL) {
 cerr << "[ERRO SEMÂNTICO] Operação (multiplicação) com valor nulo";
 printPosition();
 exit(0);
}

if (fesq->type == Fator::LITERAL && fdir->type == Fator::LITERAL) {

 FatorLiteral *flesq = ((FatorLiteral *)fesq);
 FatorLiteral *fldir = ((FatorLiteral *)fdir);
 Literal *lesq = ((Literal *)flesq->literal);
 Literal *ldir = ((Literal *)fldir->literal);

 if (lesq->type != ldir->type) {
   cerr << "[ERRO SEMÂNTICO] Tipos diferentes em multiplicação";
   printPosition();
   exit(0);
 }
}*/
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
    cout << "Análise semântica do nó expressão aritmética (soma) " << endl;
    /*
    esquerda->semanticAnalyze(semanticTableFunction);
    direita->semanticAnalyze(semanticTableFunction);

    Fator *fesq = ((Fator *)esquerda);
    Fator *fdir = ((Fator *)direita);
    if (fesq->type == Fator::FUNCAO && fdir->type == Fator::LITERAL) {
      FatorFuncao *fafuesq = ((FatorFuncao *)fesq);
      Funcao *fuesq = ((Funcao *)fafuesq->funcao);
      FatorLiteral *fldir = ((FatorLiteral *)fdir);
      Literal *ldir = ((Literal *)fldir->literal);

      if (functionTable.getType(fuesq->identifier) == 3) {
        cerr << "[ERRO SEMÂNTICO] Tipos void em soma";
        printPosition();
        exit(0);
      }

      if (functionTable.getType(fuesq->identifier) != ldir->type) {
        cerr << "[ERRO SEMÂNTICO] Tipos diferentes em soma";
        printPosition();
        exit(0);
      }
    }

    if (fesq->type == Fator::LITERAL && fdir->type == Fator::FUNCAO) {

      FatorLiteral *flesq = ((FatorLiteral *)fesq);
      Literal *lesq = ((Literal *)flesq->literal);
      FatorFuncao *fafudir = ((FatorFuncao *)fdir);
      Funcao *fudir = ((Funcao *)fafudir->funcao);

      if (functionTable.getType(fudir->identifier) == 3) {
        cerr << "[ERRO SEMÂNTICO] Tipos void em soma";
        printPosition();
        exit(0);
      }

      if (lesq->type != functionTable.getType(fudir->identifier)) {
        cerr << "[ERRO SEMÂNTICO] Tipos diferentes em soma";
        printPosition();
        exit(0);
      }
    }

    if (fesq->type == Fator::FUNCAO && fdir->type == Fator::FUNCAO) {

      FatorFuncao *fafuesq = ((FatorFuncao *)fesq);
      Funcao *fuesq = ((Funcao *)fafuesq->funcao);
      FatorFuncao *fafudir = ((FatorFuncao *)fdir);
      Funcao *fudir = ((Funcao *)fafudir->funcao);

      if (functionTable.getType(fuesq->identifier) == 3 ||
          functionTable.getType(fudir->identifier) == 3) {
        cerr << "[ERRO SEMÂNTICO] Tipos void em soma";
        printPosition();
        exit(0);
      }

      if (functionTable.getType(fuesq->identifier) !=
          functionTable.getType(fudir->identifier)) {
        cerr << "[ERRO SEMÂNTICO] Tipos diferentes em soma";
        printPosition();
        exit(0);
      }
    }

    if (fesq->type == Fator::NIL || fdir->type == Fator::NIL) {
      cerr << "[ERRO SEMÂNTICO] Operação (soma) com valor nulo";
      printPosition();
      exit(0);
    }

    if (fesq->type == Fator::LITERAL && fdir->type == Fator::LITERAL) {

      FatorLiteral *flesq = ((FatorLiteral *)fesq);
      FatorLiteral *fldir = ((FatorLiteral *)fdir);
      Literal *lesq = ((Literal *)flesq->literal);
      Literal *ldir = ((Literal *)fldir->literal);

      if (lesq->type != ldir->type) {
        cerr << "[ERRO SEMÂNTICO] Tipos diferentes em soma";
        printPosition();
        exit(0);
      }
    }*/
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
    cout << "Análise semântica do nó expressão aritmética (subtração) " << endl;
    /*
    esquerda->semanticAnalyze(semanticTableFunction);
    direita->semanticAnalyze(semanticTableFunction);

    Fator *fesq = ((Fator *)esquerda);
    Fator *fdir = ((Fator *)direita);
    if (fesq->type == Fator::FUNCAO && fdir->type == Fator::LITERAL) {
      FatorFuncao *fafuesq = ((FatorFuncao *)fesq);
      Funcao *fuesq = ((Funcao *)fafuesq->funcao);
      FatorLiteral *fldir = ((FatorLiteral *)fdir);
      Literal *ldir = ((Literal *)fldir->literal);

      if (functionTable.getType(fuesq->identifier) == 3) {
        cerr << "[ERRO SEMÂNTICO] Tipos void em subtração";
        printPosition();
        exit(0);
      }

      if (functionTable.getType(fuesq->identifier) != ldir->type) {
        cerr << "[ERRO SEMÂNTICO] Tipos diferentes em subtração";
        printPosition();
        exit(0);
      }
    }

    if (fesq->type == Fator::LITERAL && fdir->type == Fator::FUNCAO) {

      FatorLiteral *flesq = ((FatorLiteral *)fesq);
      Literal *lesq = ((Literal *)flesq->literal);
      FatorFuncao *fafudir = ((FatorFuncao *)fdir);
      Funcao *fudir = ((Funcao *)fafudir->funcao);

      if (functionTable.getType(fudir->identifier) == 3) {
        cerr << "[ERRO SEMÂNTICO] Tipos void em subtração";
        printPosition();
        exit(0);
      }

      if (lesq->type != functionTable.getType(fudir->identifier)) {
        cerr << "[ERRO SEMÂNTICO] Tipos diferentes em subtração";
        printPosition();
        exit(0);
      }
    }

    if (fesq->type == Fator::FUNCAO && fdir->type == Fator::FUNCAO) {

      FatorFuncao *fafuesq = ((FatorFuncao *)fesq);
      Funcao *fuesq = ((Funcao *)fafuesq->funcao);
      FatorFuncao *fafudir = ((FatorFuncao *)fdir);
      Funcao *fudir = ((Funcao *)fafudir->funcao);

      if (functionTable.getType(fuesq->identifier) == 3 ||
          functionTable.getType(fudir->identifier) == 3) {
        cerr << "[ERRO SEMÂNTICO] Tipos void em subtração";
        printPosition();
        exit(0);
      }

      if (functionTable.getType(fuesq->identifier) !=
          functionTable.getType(fudir->identifier)) {
        cerr << "[ERRO SEMÂNTICO] Tipos diferentes em subtração";
        printPosition();
        exit(0);
      }
    }

    if (fesq->type == Fator::NIL || fdir->type == Fator::NIL) {
      cerr << "[ERRO SEMÂNTICO] Operação (subtração) com valor nulo";
      printPosition();
      exit(0);
    }

    if (fesq->type == Fator::LITERAL && fdir->type == Fator::LITERAL) {

      FatorLiteral *flesq = ((FatorLiteral *)fesq);
      FatorLiteral *fldir = ((FatorLiteral *)fdir);
      Literal *lesq = ((Literal *)flesq->literal);
      Literal *ldir = ((Literal *)fldir->literal);

      if (lesq->type != ldir->type) {
        cerr << "[ERRO SEMÂNTICO] Tipos diferentes em subtração";
        printPosition();
        exit(0);
      }
    }*/
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
} // namespace A
#endif /* EXPRESSAO_H */