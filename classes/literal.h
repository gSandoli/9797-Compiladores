// arquivo header das classes e métodos utilizados para construir a AST do
// compilador
#ifndef LITERAL_H // include guard
#define LITERAL_H

#include "ast.h"
#include "util/print.h"
#include <iostream>
#include <ostream>
#include <string>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Value.h"

using namespace std;
using namespace llvm;
namespace A {
class Literal : public Ast {
public:
  enum Type { INTEIRO, REAL, CADEIA };

  Type type;

  Literal(int line, int col, Type type) : Ast(line, col), type(type) {}
};

class LiteralInteiro : public Literal {
public:
  int value;
  LiteralInteiro(int line, int col, int value)
      : Literal(line, col, INTEIRO), value(value) {
    cout << "Construindo nó literal (inteiro " << type << "): " << value
         << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {}

  Value *tradutor(unique_ptr<LLVMContext> context,
                  unique_ptr<IRBuilder<>> builder, unique_ptr<Module> module) {
    cout << "Tradutor nó literal (inteiro)" << endl;
    ConstantInt *ci;
    ci = ConstantInt::get(*context, APInt(64, value));
    cout << "ci: " << ci->getType()->getTypeID() << endl;
    return ci;
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "LiteralInteiro(%d)", value);
  }
};

class LiteralReal : public Literal {
public:
  double value;
  LiteralReal(int line, int col, double value)
      : Literal(line, col, REAL), value(value) {
    cout << "Construindo nó literal (real " << type << "): " << value << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {}

  Value *tradutor(unique_ptr<LLVMContext> &context,
                  unique_ptr<IRBuilder<>> &builder,
                  unique_ptr<Module> &module) {
    cout << "Tradutor nó literal (real)" << endl;
    ConstantFP *ret;
    ret = ConstantFP::get(*context, APFloat(value));
    cout << "cf: " << ret->getType()->getTypeID() << endl;
    return ret;
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "LiteralReal(%f)", value);
  }
};

class LiteralCadeia : public Literal {
public:
  string value;
  LiteralCadeia(int line, int col, string *value)
      : Literal(line, col, CADEIA), value(*value) {
    cout << "Construindo nó literal (cadeia " << type << "): " << *value
         << endl;
  }

  void semanticAnalyze(VariableTable variableTable,
                       FunctionTable functionTable) const {}

  // TOODO: achar a "classe" do llvm que referencia string
  Value *tradutor(unique_ptr<LLVMContext> context,
                  unique_ptr<IRBuilder<>> builder, unique_ptr<Module> module) {
    // return ConstantFP::get(context, APFloat(value));
    return nullptr;
  }

  void print(FILE *out, int d) const {
    indent(out, d);
    fprintf(out, "LiteralCadeia(%s)", value.c_str());
  }
};
} // namespace A

#endif /* LITERAL_H */