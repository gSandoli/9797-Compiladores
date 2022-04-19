#include <string>
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "driver.hh"
#include "classes/ast.h"
#include "classes/funcao.h"
#include "classes/fator.h"
#include "classes/literal.h"

using namespace std;

int main(int argc, char **argv)
{
  string filename;
  string output = "a.out";
  bool intermediateCode = false; // fonte.ll
  bool assemblyCode = false;     // fonte.s
  int opt;

  if (argc == 1)
  {
    cerr << "ERROR: missing arguments\n"
         << endl;
    cout << "USAGE: ./sc [-i] [-s] [-o <destino>] <fonte>" << endl;
    cout << "\t-i : imprime o código intermediário. O arquivo de saída deve chamar fonte.ll // opcional" << endl;
    cout << "\t-s : imprime o código Assembly. O arquivo de saída deve chamar fonte.s // opcional" << endl;
    cout << "\t-o <destino> : gera o executável com o nome destino. Caso não seja fornecido, deve ser gerado um arquivo chamado a.out. // optional" << endl;
    cout << "\t<fonte> : código fonte, cujo extensão é .s" << endl;
    abort();
  }

  while ((opt = getopt(argc, argv, "iso:")) != EOF)
  {
    switch (opt)
    {
    case 'i':
      intermediateCode = true;
      break;
    case 's':
      assemblyCode = true;
      break;
    case 'o':
      output = optarg;
      output += ".out";
      break;
    default:
      cerr << endl;
      abort();
    }
  }

  int argsNotParsed = argc - optind;
  if (argsNotParsed < 1)
  {
    cerr << "ERROR: source file is missing" << endl;
    abort();
  }
  else if (argsNotParsed > 1)
  {
    cerr << "ERROR: source file is wrong" << endl;
    abort();
  }
  else
  {
    filename = argv[optind];
  }

  Simples::Driver driver;
  driver.parse_file(filename);

  Funcao *func = ((Funcao *)driver.root);
  Fator *f = ((Fator *)func->args);
  FatorLiteral *fl = ((FatorLiteral *)f);
  LiteralInteiro *li = ((LiteralInteiro *)fl->literal);

  cout << "MAIN Nó chamada de função:" << endl;
  cout << "\tChamada: " << func->identifier << endl;
  cout << "\tArgs: " << li->value << endl;

  if (intermediateCode)
  {
    FILE *out = fopen(output.c_str(), "w");
    if (out != NULL)
    {
      driver.root->print(out, 0);
      fprintf(out, "\n");
    }
    fclose(out);
  }

  return 0;
}
