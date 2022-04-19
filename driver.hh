#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "classes/ast.h"
using namespace std;
using namespace A;
namespace Simples
{
  /// Forward declarations of classes
  class Parser;
  class Scanner;
  class location;

  class Driver
  {
  public:
    Driver();
    ~Driver();

    Ast *root;

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
}
