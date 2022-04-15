#include <string>
#include <iostream>
#include <unistd.h>

#include "driver.hh"
using namespace std;

int main(int argc, char **argv)
{
  string filename;
  int opt;
  while ((opt = getopt(argc, argv, "i:?")) != EOF)
    switch (opt)
    {
    case 'i':
      filename = optarg;
      break;
    case '?':
      cerr << "Usuage: tc -i <filename>" << endl;
      break;
    default:
      cerr << endl;
      abort();
    }

  Simples::Driver driver;
  driver.parse_file(filename);
  return 0;
}
