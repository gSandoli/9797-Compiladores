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
#include <llvm-13/llvm/IR/BasicBlock.h>
#include <string>

using namespace std;

namespace A {
class Comando : public Ast {
public:
  enum Type { ATRIBUICAO, FUNCAO, IF, WHILE };
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

class ComandoSe : public Comando {
public:
  Ast *ifExp;
  Ast *ifList;
  ComandoSe(int line, int col, Ast *ifExp, Ast *ifList)
      : Comando(line, col, IF), ifExp(ifExp), ifList(ifList){};

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    ifExp->semanticAnalyze(semanticTableFunction);
    ifList->semanticAnalyze(semanticTableFunction);
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Value *test =
        ifExp->tradutor(context, builder, module, functions, namedValues);

    test = builder->CreateIntCast(test, llvm::Type::getInt1Ty(*context), 0,
                                  "ifcast");
    builder->CreateICmpNE(test, ConstantInt::get(*context, APInt(1, 1)),
                          "iftest");

    Function *function = builder->GetInsertBlock()->getParent();
    BasicBlock *thenBlock = BasicBlock::Create(*context, "then", function);
    BasicBlock *mergeBlock = BasicBlock::Create(*context, "ifcont");

    builder->CreateCondBr(test, thenBlock, mergeBlock);
    builder->SetInsertPoint(thenBlock);
    thenBlock = builder->GetInsertBlock();

    // THEN
    Value *then =
        ifList->tradutor(context, builder, module, functions, namedValues);

    builder->CreateBr(mergeBlock);
    function->getBasicBlockList().push_back(mergeBlock);
    builder->SetInsertPoint(mergeBlock);

    if (then && !then->getType()->isVoidTy()) {
      PHINode *PN = builder->CreatePHI(then->getType(), 2, "iftmp");
      PN->addIncoming(then, thenBlock);
      return PN;
    }
    return nullptr;
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ComandoSe(\n");
    ifExp->print(out, d + 1);
    virgula(out, d);
    ifList->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

class ComandoSeVerdadeiroFalso : public Comando {
public:
  Ast *ifExp;
  Ast *ifList;
  Ast *elseList;
  ComandoSeVerdadeiroFalso(int line, int col, Ast *ifExp, Ast *ifList,
                           Ast *elseList)
      : Comando(line, col, IF), ifExp(ifExp), ifList(ifList),
        elseList(elseList){};

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    ifExp->semanticAnalyze(semanticTableFunction);
    ifList->semanticAnalyze(semanticTableFunction);
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    cout << "entrou tradutor ComandoSeVerdadeiroFalso" << endl;
    // IF
    Value *test =
        ifExp->tradutor(context, builder, module, functions, namedValues);

    test = builder->CreateIntCast(test, llvm::Type::getInt1Ty(*context), 0,
                                  "ifcast");
    builder->CreateICmpNE(test, ConstantInt::get(*context, APInt(1, 1)),
                          "iftest");

    Function *function = builder->GetInsertBlock()->getParent();
    BasicBlock *thenBlock = BasicBlock::Create(*context, "then", function);
    BasicBlock *elseBlock = llvm::BasicBlock::Create(*context, "else");
    BasicBlock *mergeBlock = BasicBlock::Create(*context, "ifcont");

    builder->CreateCondBr(test, thenBlock, elseBlock);
    builder->SetInsertPoint(thenBlock);
    thenBlock = builder->GetInsertBlock();

    // THEN
    Value *then =
        ifList->tradutor(context, builder, module, functions, namedValues);

    builder->CreateBr(mergeBlock);

    function->getBasicBlockList().push_back(elseBlock);
    builder->SetInsertPoint(elseBlock);

    // ELSE
    Value *elsee =
        elseList->tradutor(context, builder, module, functions, namedValues);

    builder->CreateBr(mergeBlock);

    function->getBasicBlockList().push_back(mergeBlock);
    builder->SetInsertPoint(mergeBlock);

    if (!then->getType()->isVoidTy() && !elsee->getType()->isVoidTy()) {
      auto PN = builder->CreatePHI(then->getType(), 2, "iftmp");
      PN->addIncoming(then, thenBlock);
      PN->addIncoming(elsee, elseBlock);
      return PN;
    }
    return nullptr;
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ComandoSeVerdadeiroFalso(\n");
    ifExp->print(out, d + 1);
    virgula(out, d);
    ifList->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};
class ComandoEnquanto : public Comando {
public:
  Ast *exp;
  Ast *list;
  ComandoEnquanto(int line, int col, Ast *exp, Ast *list)
      : Comando(line, col, WHILE), exp(exp), list(list){};

  Ast *semanticAnalyze(
      SymbolTable<SemanticTableFunction> semanticTableFunction) const {
    exp->semanticAnalyze(semanticTableFunction);
    list->semanticAnalyze(semanticTableFunction);
    return ((Ast *)this);
  }

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder, unique_ptr<Module> &module,
                  SymbolTable<Function> &functions,
                  map<string, AllocaInst *> &namedValues) const {
    Function *function = builder->GetInsertBlock()->getParent();
    BasicBlock *testBB = BasicBlock::Create(*context, "test", function);
    BasicBlock *loopBB = BasicBlock::Create(*context, "loop", function);
    BasicBlock *nextBB = BasicBlock::Create(*context, "next", function);
    BasicBlock *afterBB = BasicBlock::Create(*context, "after", function);

    builder->CreateBr(testBB);
    builder->SetInsertPoint(testBB);

    Value *test =
        exp->tradutor(context, builder, module, functions, namedValues);

    if (!test)
      return nullptr;

    Value *EndCond = builder->CreateICmpEQ(
        test,
        ConstantInt::get(llvm::Type::getInt64Ty(*context), llvm::APInt(64, 0)),
        "loopcond");

    // goto after or loop
    builder->CreateCondBr(EndCond, afterBB, loopBB);
    builder->SetInsertPoint(loopBB);

    // loop:
    if (!list->tradutor(context, builder, module, functions, namedValues))
      return nullptr;

    // goto next:
    builder->CreateBr(nextBB);

    // next:
    builder->SetInsertPoint(nextBB);

    builder->CreateBr(testBB);

    // after:
    builder->SetInsertPoint(afterBB);

    return Constant::getNullValue(llvm::Type::getInt64Ty(*context));
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "ComandoEnquanto(\n");
    exp->print(out, d + 1);
    virgula(out, d);
    list->print(out, d + 1);
    indent(out, d);
    fprintf(out, ")\n");
  }
};

} // namespace A

#endif /* COMANDO_H */