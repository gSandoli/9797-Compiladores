// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef FATOR_H // include guard
#define FATOR_H

#include <string>
#include <iostream>
#include "ast.h"

using namespace std;

namespace A
{
    class Fator : public Ast
    {
    public:
        Fator() {}
    };
}

#endif /* FATOR_H */