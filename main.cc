#include <string>
#include <iostream>
#include <unistd.h>

#include "driver.hh"

int main(int argc, char **argv) {
  std::string filename;
  int opt;
  while ((opt = getopt(argc, argv, "i:s:o:?")) != EOF)
      switch(opt) {
          case 'i': std::cerr << "Imprimir codigo intermediario nao implementado." <<std::endl; break;
          case 's': std::cerr << "Imprimir codigo assembly nao implementado." <<std::endl; break;
          case 'o': std::cerr << "Definir nome final nao implementado." <<std::endl; break;
          case '?': std::cerr << "Usuage: tc -i <filename>" << std::endl; break;
          default: std::cerr << std::endl; abort();
      }

  filename = argv[argc-1];
  Simples::Driver driver;
  driver.parse_file(filename);
  return 0;
}
