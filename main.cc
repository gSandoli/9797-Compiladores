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
  string output = folder + "a.out";
  string fonte = folder + "fonte.ll";
  string fonteAssembly = folder + "fonte.s";
  string tree = folder + "tree.out";
  string llvmFile = folder + "llvm.out";
  bool intermediateCode = false; // fonte.ll
  bool assemblyCode = false;     // fonte.s
  int opt;

  if (argc == 1) {
    cerr << "[ERRO] faltando argumentos\n" << endl;
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
    cerr << "[ERRO] arquivo de origem está faltando" << endl;
    abort();
  } else if (argsNotParsed > 1) {
    cerr << "[ERRO] arquivo de origem está errado" << endl;
    abort();
  } else {
    filename = argv[optind];
  }

  Simples::Driver driver;
  driver.parse_file(filename);

  driver.root->semanticAnalyze(*driver.variableTable, *driver.functionTable);

  system("mkdir -p output");
  FILE *treeOutput = fopen(tree.c_str(), "w");
  if (treeOutput != NULL) {
    driver.root->print(treeOutput, 0);
  }
  fclose(treeOutput);

  static unique_ptr<LLVMContext> context = make_unique<LLVMContext>();
  static unique_ptr<Module> module = make_unique<Module>("main", *context);
  static unique_ptr<IRBuilder<>> builder = make_unique<IRBuilder<>>(*context);
  static map<string, Value *> NamedValues;

  // Geração de código intermediário
  Value *codegen =
      tradutor(context, builder, module, driver.root, llvmFile, fonte);

  if (assemblyCode) {
    // default: llc-13 output/fonte.ll -o output/fonte.s
    const string cmdAss = "llc-13 " + fonte + " -o " + fonteAssembly;
    system(cmdAss.c_str());
  }

  if (!intermediateCode) {
    const string cmdRmFileLib = "rm -rf " + fonte;
    system(cmdRmFileLib.c_str());
  }

  const string cmdLib =
      "clang-13 -fpic -c -o output/lib.o classes/util/lib.cpp";
  system(cmdLib.c_str());
  // default: g++ output/llvm.out output/lib.o -o output/a.out
  const string cmd = "g++ " + llvmFile + " output/lib.o -o " + output;
  system(cmd.c_str());
  return 0;
}
