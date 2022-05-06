// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef EXPRESSAO_H // include guard
#define EXPRESSAO_H

#include "ast.h"
#include "fator.h"
#include "funcao.h"
#include "literal.h"
#include "util/print.h"
#include <iostream>
#include <string>

using namespace std;

namespace A {
class Expressao : public Ast {
public:
  enum Type { SOMA, SUBTRACAO, DIVISAO, MULTIPLICACAO };
  Type type;
  Expressao(int line, int col, Type type) : Ast(line, col), type(type) {}
  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module);
};

class ExpressaoAritmeticaDivisao : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoAritmeticaDivisao(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, DIVISAO), esquerda(esquerda), direita(direita) {
    cout << "Construindo nó expressão aritmética (divisão) " << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó expressão aritmética (divisão) " << endl;
    esquerda->semanticAnalyze(variableTable, functionTable);
    direita->semanticAnalyze(variableTable, functionTable);

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
    }
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
                  unique_ptr<IRBuilder<>> &builder,
                  unique_ptr<Module> &module) {
    auto L = ((Fator *)esquerda)->tradutor(context, builder, module);
    auto R = ((Fator *)direita)->tradutor(context, builder, module);

    return nullptr;
  }
};

class ExpressaoAritmeticaMultiplicacao : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoAritmeticaMultiplicacao(int line, int col, Ast *esquerda,
                                   Ast *direita)
      : Expressao(line, col, MULTIPLICACAO), esquerda(esquerda),
        direita(direita) {
    cout << "Construindo nó expressão aritmética (multiplicação) " << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó expressão aritmética (multiplicação) "
         << endl;
    esquerda->semanticAnalyze(variableTable, functionTable);
    direita->semanticAnalyze(variableTable, functionTable);

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
    }
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
                  unique_ptr<IRBuilder<>> &builder,
                  unique_ptr<Module> &module) {
    auto L = ((Fator *)esquerda)->tradutor(context, builder, module);
    auto R = ((Fator *)direita)->tradutor(context, builder, module);

    return nullptr;
  }
};

class ExpressaoAritmeticaSoma : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoAritmeticaSoma(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, SOMA), esquerda(esquerda), direita(direita) {
    cout << "Construindo nó expressão aritmética (soma) " << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó expressão aritmética (soma) " << endl;
    esquerda->semanticAnalyze(variableTable, functionTable);
    direita->semanticAnalyze(variableTable, functionTable);

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

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder,
                  unique_ptr<Module> &module) {
    auto L = ((Fator *)esquerda)->tradutor(context, builder, module);
    auto R = ((Fator *)direita)->tradutor(context, builder, module);

    return nullptr;
  }
};

class ExpressaoAritmeticaSubtracao : public Expressao {
public:
  Ast *esquerda;
  Ast *direita;
  ExpressaoAritmeticaSubtracao(int line, int col, Ast *esquerda, Ast *direita)
      : Expressao(line, col, SUBTRACAO), esquerda(esquerda), direita(direita) {
    cout << "Construindo nó expressão aritmética (subtração) " << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {
    cout << "Análise semântica do nó expressão aritmética (subtração) " << endl;
    esquerda->semanticAnalyze(variableTable, functionTable);
    direita->semanticAnalyze(variableTable, functionTable);

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

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder,
                  unique_ptr<Module> &module) {
    auto L = ((Fator *)esquerda)->tradutor(context, builder, module);
    auto R = ((Fator *)direita)->tradutor(context, builder, module);

    return nullptr;
  }
};
} // namespace A
#endif /* EXPRESSAO_H */