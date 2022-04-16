// arquivo header das classes e métodos utilizados para construir a AST do compilador
#ifndef EXPRESSAO_H // include guard
#define EXPRESSAO_H

#include <string>
#include <iostream>
#include "ast.h"
#include "funcao.h"

using namespace std;

namespace AST
{
    class Expressao : public ArgsChamada
    {
    public:
        Expressao() {}
    };
}

#endif /* EXPRESSAO_H */