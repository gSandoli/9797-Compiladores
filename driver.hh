#pragma once

#include "classes/ast.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace A;
namespace Simples {
/// Forward declarations of classes
class Parser;
class Scanner;
class location;

class Driver {
public:
  Driver();
  ~Driver();

  Ast *root;
  int line = 1;
  int col = 0;
  SymbolTable<SemanticTableFunction> semanticTableFunctions;

  int parse();
  int parse_file(string &path);
  void reset();

private:
  Scanner *scanner_;
  Parser *parser_;
  location *location_;
  int error_;

  /// Allows Parser and Scanner to access private attributes
  /// of the Driver class
  friend class Parser;
  friend class Scanner;
};
} // namespace Simples
