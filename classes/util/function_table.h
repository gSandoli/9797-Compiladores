#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H
#define MAX_SIZE 127
#include <iostream>

using namespace std;
namespace T {
class FunctionTable {
public:
  string table[MAX_SIZE][3];
  FunctionTable() {
    // Imprime uma cadeia na saída padrão.
    add("imprimec", "cadeia", "void");
    // Imprime uma contante inteiro na saída padrão.
    add("imprimei", "inteiro", "void");
    // Imprime uma constante real na saída padrão.
    add("imprimer", "real", "void");
    // Execute um flush na saída padrão.
    add("emite", "", "void");
    // Lê uma contante inteiro da entrada padrão.
    add("lc", "", "cadeia");
    // Lê uma contante inteiro da entrada padrão.
    add("li", "", "inteiro");
    // Lê uma constante real da entrada padrão.
    add("lr", "", "real");
    // Retorna o valor ASCII do primeiro caracter da cadeia ou -1 se a cadeia é
    // vazia.
    add("ordem", "cadeia", "inteiro");
    // Retorna o caracter para o valor ASCII i. Erro de execução se o valor é
    // inválido.
    add("chr", "inteiro", "cadeia");
    // Retorna a quantidade de caracteres da cadeia.
    add("tamanho", "cadeia", "inteiro");
    // Retorna a subcadeia de c iniciando no caracter i, composta por n
    // caracteres. O primeiro caracter inicia na posição 0.
    add("subcadeia", "cadeia,inteiro,inteiro", "cadeia");
    // Retorna uma nova cadeia formada por c1 seguida por c2.
    add("concatene", "cadeia,cadeia", "cadeia");
    // Retorna 1 se a i for zero, ou 0 caso contrário.
    add("inverter", "inteiro", "inteiro");
    // Termina a execução do programa com o código i.
    add("termine", "inteiro", "void");
    // Retorna um número inteiro aleatório
    add("gere_inteiro", "", "inteiro");
    // Retorna um número real aleatório.
    add("gere_real", "", "real");
  };

  bool exists(const string &name) {
    for (int i = 0; i < MAX_SIZE; ++i)
      if (table[i][0] == name)
        return true;
    return false;
  }

  int getArgs(const string &name) {
    for (int i = 0; i < MAX_SIZE; ++i)
      if (table[i][0] == name) {
        if (table[i][1] == "inteiro")
          return 0;
        if (table[i][1] == "real")
          return 1;
        if (table[i][1] == "cadeia")
          return 2;
      }
    return 0;
  }

  int getType(const string &name) {
    for (int i = 0; i < MAX_SIZE; ++i)
      if (table[i][0] == name) {
        if (table[i][2] == "inteiro")
          return 0;
        if (table[i][2] == "real")
          return 1;
        if (table[i][2] == "cadeia")
          return 2;
        if (table[i][2] == "void")
          return 3;
      }
    return -1;
  }

  bool add(const string &name, const string &arg, const string &type) {
    for (int i = 0; i < MAX_SIZE; ++i) {
      if (table[i][0].empty()) {
        table[i][0] = name;
        table[i][1] = arg;
        table[i][2] = type;
        return true;
      }
    }
    cerr << "FunctionTable cheia!" << endl;
    abort();
  }

  void show() {
    for (int i = 0; i < MAX_SIZE; ++i)
      if (!table[i][0].empty())
        cout << table[i][0] << " | " << table[i][1] << " | " << table[i][2]
             << endl;
  }
};
}; // namespace T

#endif // FUNCTION_TABLE_H
