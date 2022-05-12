Como conversamos dia 05/05 na sala do profª, havia sido implementado a análise semântica de funções e expressões.
Porém decidimos focar na implementação da parte 3 que contempla a geração de código executável pois o peso interferiria muito
na nota final. Com isso, a árvore de instruções acabou sendo modificada de tal modo que análise semântica não está sendo chamada
e portanto não pode ser testada. A implementação da análise semântica de funções está presente no código que entregamos, porém, a 
análise semântica de expressões foi removida devido a remodelagem da arvore e pode ser vista no histórido do github no link a seguir:
https://github.com/sSandoli/9797-Compiladores/commit/02d7d28d0cc848c3095ce5a05a93be57a5ef2d81

Havia sido implementado os seguintes erros:
    - Função:
        - [ERRO SEMÂNTICO] Função não existe
        - [ERRO SEMÂNTICO] Parâmetros faltando
        - [ERRO SEMÂNTICO] Tipo de parâmetro incorreto (https://github.com/sSandoli/9797-Compiladores/commit/64e133430e979a579b46f4aa60c12f7187077b20)
    - Divisão:
        - [ERRO SEMÂNTICO] Tipo void em divisão
        - [ERRO SEMÂNTICO] Tipos diferentes em divisão
        - [ERRO SEMÂNTICO] Operação (divisão) com valor nulo
        - [ERRO SEMÂNTICO] Divisão por 0
        - [ERRO SEMÂNTICO] Divisão por 0.0
    - Multiplicação:
        - [ERRO SEMÂNTICO] Tipos void em multiplicação
        - [ERRO SEMÂNTICO] Tipos diferentes em multiplicação
        - [ERRO SEMÂNTICO] Operação (multiplicação) com valor nulo
    - Soma:
        - [ERRO SEMÂNTICO] Tipos void em soma
        - [ERRO SEMÂNTICO] Tipos diferentes em soma
        - [ERRO SEMÂNTICO] Operação (soma) com valor nulo
    - Subtração:
        - [ERRO SEMÂNTICO] Tipos void em subtração
        - [ERRO SEMÂNTICO] Tipos diferentes em subtração
        - [ERRO SEMÂNTICO] Operação (subtração) com valor nulo
