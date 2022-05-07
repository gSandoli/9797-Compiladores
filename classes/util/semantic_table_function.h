#include <iostream>
#include <vector>

using namespace std;

class SemanticTableFunction {
public:
  string name;
  string type;
  vector<string> args;
  SemanticTableFunction(string const &name, vector<string> const &args,
                        string const &type)
      : name(name), args(args), type(type) {}
};