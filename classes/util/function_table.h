#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H
#define MAX_SIZE 127
#include <iostream>

using namespace std;
namespace T
{
    class FunctionTable
    {
    public:
        string table[MAX_SIZE][3];
        FunctionTable()
        {
            add("imprimec", "cadeia", "void");                    // Imprime uma cadeia na saída padrão.
            add("imprimei", "inteiro", "void");                   // Imprime uma contante inteiro na saída padrão.
            add("imprimer", "real", "void");                      // Imprime uma constante real na saída padrão.
            add("emite", "", "void");                             // Execute um flush na saída padrão.
            add("lc", "", "cadeia");                              // Lê uma cadeia da entrada padrão.
            add("li", "", "inteiro");                             // Lê uma contante inteiro da entrada padrão.
            add("lr", "", "real");                                // Lê uma constante real da entrada padrão.
            add("ordem", "cadeia", "inteiro");                    // Retorna o valor ASCII do primeiro caracter da cadeia ou -1 se a cadeia é vazia.
            add("chr", "inteiro", "cadeia");                      // Retorna o caracter para o valor ASCII i. Erro de execução se o valor é inválido.
            add("tamanho", "cadeia", "inteiro");                  // Retorna a quantidade de caracteres da cadeia.
            add("subcadeia", "cadeia,inteiro,inteiro", "cadeia"); // Retorna a subcadeia de c iniciando no caracter i, composta por n caracteres. O primeiro caracter inicia na posição 0.
            add("concatene", "cadeia,cadeia", "cadeia");          // Retorna uma nova cadeia formada por c1 seguida por c2.
            add("inverter", "inteiro", "inteiro");                // Retorna 1 se a i for zero, ou 0 caso contrário.
            add("termine", "inteiro", "void");                    // Termina a execução do programa com o código i.
            add("gere_inteiro", "", "inteiro");                   // Retorna um número inteiro aleatório
            add("gere_real", "", "real");                         // Retorna um número real aleatório.
        };

        bool exists(const string &name)
        {
            for (int i = 0; i < MAX_SIZE; ++i)
                if (table[i][0] == name)
                    return true;
            return false;
        }

        bool lookArgs(const string &name, const string &arg)
        {
            for (int i = 0; i < MAX_SIZE; ++i)
                if (table[i][0] == name && table[i][1] == arg)
                    return true;
            return false;
        }

        bool lookType(const string &name, const string &type)
        {
            for (int i = 0; i < MAX_SIZE; ++i)
                if (table[i][0] == name && table[i][2] == type)
                    return true;
            return false;
        }

        bool add(const string &name, const string &arg, const string &type)
        {
            for (int i = 0; i < MAX_SIZE; ++i)
            {
                if (table[i][0].empty())
                {
                    table[i][0] = name;
                    table[i][1] = arg;
                    table[i][2] = type;
                    return true;
                }
            }
            cerr << "FunctionTable cheia!" << endl;
            abort();
        }

        void show()
        {
            for (int i = 0; i < MAX_SIZE; ++i)
                if (!table[i][0].empty())
                    cout << table[i][0] << " | " << table[i][1] << " | " << table[i][2] << endl;
        }
    };
};

#endif // FUNCTION_TABLE_H
