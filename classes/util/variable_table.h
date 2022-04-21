#ifndef VARIABLE_TABLE_H
#define VARIABLE_TABLE_H
#define MAX_SIZE 127
#include <iostream>

using namespace std;
namespace T
{
    class VariableTable
    {
    public:
        string table[MAX_SIZE][2];
        VariableTable(){};

        bool exists(const string &name)
        {
            for (int i = 0; i < MAX_SIZE; ++i)
                if (table[i][0] == name)
                    return true;
            return false;
        }

        bool lookType(const string &name, const string &type)
        {
            for (int i = 0; i < MAX_SIZE; ++i)
                if (table[i][0] == name && table[i][1] == type)
                    return true;
            return false;
        }

        bool add(const string &name, const string &type)
        {
            for (int i = 0; i < MAX_SIZE; ++i)
            {
                if (table[i][0].empty())
                {
                    table[i][0] = name;
                    table[i][1] = type;
                    return true;
                }
            }
            cerr << "VariableTable cheia!" << endl;
            abort();
        }

        void show()
        {
            for (int i = 0; i < MAX_SIZE; ++i)
                if (!table[i][0].empty())
                    cout << table[i][0] << " | " << table[i][1] << endl;
        }
    };
}

#endif // VARIABLE_TABLE_H
