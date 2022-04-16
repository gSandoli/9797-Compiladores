// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef FATOR_H // include guard
#define FATOR_H

#include <string>
#include <iostream>
#include "ast.h"
#include "expressao.h"

using namespace std;

namespace AST
{
    class Fator : public Expressao
    {
    public:
        Fator() {}
    };
}

#endif /* FATOR_H */