// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef EXPRESSAO_H // include guard
#define EXPRESSAO_H

#include <string>
#include <iostream>
#include "ast.h"

using namespace std;

namespace A
{
    class Expressao : public Ast
    {
    public:
        Expressao() {}
    };
}

#endif /* EXPRESSAO_H */