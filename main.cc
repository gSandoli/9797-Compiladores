#include <iostream>
#include <llvm/IR/Module.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

#include "classes/ast.h"
#include "classes/fator.h"
#include "classes/funcao.h"
#include "classes/literal.h"
#include "driver.hh"

#include "classes/util/function_table.h"
#include <iostream>

#include "classes/codegen/codegen.cpp"
#include <map>

using namespace std;
using namespace T;
using namespace llvm;

int main(int argc, char **argv) {
  string filename;
  string folder = "output/";
  string lib = folder + "lib.o";
  string output = folder + "a.out";
  string fonte = folder + "fonte.ll";
  string fonteAssembly = folder + "fonte.s";
  string tree = folder + "tree.out";
  string llvmFile = folder + "llvm.out";
  bool intermediateCode = false; // fonte.ll
  bool assemblyCode = false;     // fonte.s
  int opt;

  if (argc == 1) {
    cerr << "ERROR: missing arguments\n" << endl;
    cout << "USAGE: ./sc [-i] [-s] [-o <destino>] <fonte>" << endl;
    cout << "\t-i : imprime o código intermediário. O arquivo de saída deve "
            "chamar fonte.ll // opcional"
         << endl;
    cout << "\t-s : imprime o código Assembly. O arquivo de saída deve chamar "
            "fonte.s // opcional"
         << endl;
    cout << "\t-o <destino> : gera o executável com o nome destino. Caso não "
            "seja fornecido, deve ser gerado um arquivo chamado a.out. // "
            "optional"
         << endl;
    cout << "\t<fonte> : código fonte, cujo extensão é .s" << endl;
    abort();
  }

  while ((opt = getopt(argc, argv, "iso:")) != EOF) {
    switch (opt) {
    case 'i':
      intermediateCode = true;
      break;
    case 's':
      assemblyCode = true;
      break;
    case 'o':
      output = optarg;
      output += ".out";
      output = folder + output;
      break;
    default:
      cerr << endl;
      abort();
    }
  }

  int argsNotParsed = argc - optind;
  if (argsNotParsed < 1) {
    cerr << "ERROR: source file is missing" << endl;
    abort();
  } else if (argsNotParsed > 1) {
    cerr << "ERROR: source file is wrong" << endl;
    abort();
  } else {
    filename = argv[optind];
  }

  Simples::Driver driver;
  driver.parse_file(filename);

  // Funcao *func = ((Funcao *)driver.root);
  // Fator *f = ((Fator *)func->args);
  // FatorLiteral *fl = ((FatorLiteral *)f);
  // LiteralInteiro *li = ((LiteralInteiro *)fl->literal);

  // cout << "MAIN Nó chamada de função:" << endl;
  // cout << "\tChamada: " << func->identifier << endl;
  // cout << "\tArgs: " << li->value << endl;

  driver.root->semanticAnalyze(*driver.variableTable, *driver.functionTable);

  system("mkdir -p output");
  FILE *treeOutput = fopen(tree.c_str(), "w");
  if (treeOutput != NULL) {
    driver.root->print(treeOutput, 0);
  }
  fclose(treeOutput);

  if (intermediateCode) {
    FILE *out = fopen(output.c_str(), "w");
    if (out != NULL) {
      // implementar o código intermediario aqui
    }
    fclose(out);
  }

  static unique_ptr<LLVMContext> context;
  static unique_ptr<Module> module;
  static unique_ptr<IRBuilder<>> builder;
  static map<string, Value *> NamedValues;

  context = make_unique<LLVMContext>();
  builder = make_unique<IRBuilder<>>(*context);
  module = make_unique<Module>("teste", *context);

  /* Geração de código intermediário */
  Value *codegen = tradutor(context, builder, module, driver.root, llvmFile);

  const string cmdLib = "clang-13 -c -o" + lib + " classes/util/lib.cpp";
  system(cmdLib.c_str());
  const string cmd = "g++ " + llvmFile + " " + lib + " -o" + output;
  system(cmd.c_str());
  cout << "Wrote " << output << endl;

  return 0;
}
