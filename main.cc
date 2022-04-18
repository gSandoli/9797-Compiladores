#include <string>
#include <iostream>
#include <unistd.h>

#include "driver.hh"
using namespace std;

static void usage()
{
  fprintf(stderr, "Usage: %s [-n number][-p pagefile] trace n1 n2 ...\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
  string filename;
  string output = "a.out";
  bool intermediateCode = false;
  bool assemblyCode = false;
  int opt;

  if (argc == 1)
  {
    cerr << "ERROR: missing arguments" << endl;
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
  return 0;
}
