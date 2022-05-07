#include "driver.hh"
#include "parser.hh"
#include "scanner.hh"
using namespace std;

namespace Simples {

void addFunction(SymbolTable<SemanticTableFunction> &table, string const &name,
                 vector<string> const &args, string const &type) {
  table.push(name, new SemanticTableFunction(name, args, type));
}

void createSemanticTableFunctions(SymbolTable<SemanticTableFunction> &table) {
  // Imprime uma cadeia na saída padrão.
  addFunction(table, "imprimec", {"cadeia"}, "void");
  // Imprime uma contante inteiro na saída padrão.
  addFunction(table, "imprimei", {"inteiro"}, "void");
  // Imprime uma constante real na saída padrão.
  addFunction(table, "imprimer", {"real"}, "void");
  // Execute um flush na saída padrão.
  addFunction(table, "emite", {}, "void");
  // Lê uma contante inteiro da entrada padrão.
  addFunction(table, "lc", {}, "cadeia");
  // Lê uma contante inteiro da entrada padrão.
  addFunction(table, "li", {}, "inteiro");
  // Lê uma constante real da entrada padrão.
  addFunction(table, "lr", {}, "real");
  // Retorna o valor ASCII do primeiro caracter da cadeia ou -1 se a cadeia é
  // vazia.
  addFunction(table, "ordem", {"cadeia"}, "inteiro");
  // Retorna o caracter para o valor ASCII i. Erro de execução se o valor é
  // inválido.
  addFunction(table, "chr", {"inteiro"}, "cadeia");
  // Retorna a quantidade de caracteres da cadeia.
  addFunction(table, "tamanho", {"cadeia", "inteiro", "inteiro"}, "cadeia");
  // Retorna a subcadeia de c iniciando no caracter i, composta por n
  // caracteres. O primeiro caracter inicia na posição 0.
  addFunction(table, "subcadeia", {"cadeia", "inteiro", "inteiro"}, "cadeia");
  // Retorna uma nova cadeia formada por c1 seguida por c2.
  addFunction(table, "concatene", {"cadeia", "cadeia"}, "cadeia");
  // Retorna 1 se a i for zero, ou 0 caso contrário.
  addFunction(table, "inverter", {"inteiro"}, "inteiro");
  // Termina a execução do programa com o código i.
  addFunction(table, "termine", {"inteiro"}, "void");
  // Retorna um número inteiro aleatório
  addFunction(table, "gere_inteiro", {}, "inteiro");
  // Retorna um número real aleatório.
  addFunction(table, "gere_real", {}, "real");
}

Driver::Driver()
    : scanner_(new Scanner()), parser_(new Parser(*this)),
      location_(new location()) {
  createSemanticTableFunctions(semanticTableFunctions);
}

Driver::~Driver() {
  delete parser_;
  delete scanner_;
  delete location_;
}

void Driver::reset() {
  delete location_;
  location_ = new location();
}

int Driver::parse() {
  scanner_->switch_streams(&cin, &cerr);
  parser_->parse();
  return 0;
}

int Driver::parse_file(string &path) {
  ifstream s(path.c_str(), ifstream::in);
  scanner_->switch_streams(&s, &cerr);
  parser_->parse();
  s.close();
  return 0;
}
} // namespace Simples
