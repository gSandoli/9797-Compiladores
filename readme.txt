############################ Observações do projeto. ############################

O compilador não foi implementado por inteiro. As fases de análise léxica e sintática foram implementadas por completo.
A análise semântica, Árvore Sintática Abstrata, Representação Intermediária e Código executável foram implementadas parcialmente.
Abaixo será descrito o que foi implementado dentro de cada fase.

Análise Semântica:
    A análise semântica foi implementada no escopo de chamada de funções.
    Quando uma função chamada, é verificado se ela existe, e se ela tem parâmetros. O tipo dos parâmetros não é verificado.

Árvore Sintática Abstrata, Representação Intermediária e Código executável:
    Estas três fases foram implementadas nas mesmas funcionalidades, visto que era necessário criar o nó na árvore para poder criar a RI e o código final.
    As fases foram implementadas nas seguintes funcionalidades:
        - Declaração e Atribuição de variáveis (Sem ser struct ou vetor, ou do tipo cadeia);
        - Chamada de função;
        - Expressões, exceto criação de registro. Local de armazenamento apenas variáveis unárias, sem struct ou vetor.;
        - Literais*;
        - If e If Then Else;
        - Loop While;
        - Funções externas da biblioteca padrão.

    As principais funcionalidades NÃO implementadas são:
        - Declaração de tipos;
        - Declaração de funções; 
        - For loop;
        
* O literal cadeia foi implementado, entretanto não foi possível executá-lo devido ao erro de compilação que não conseguímos resolver.
* O erro é: /usr/bin/ld: output/llvm.out: relocalização R_X86_64_32 contra ".rodata.str1.1" não pode ser usada ao fazer um objecto PIE; recompile with -fPIE
* A flag "-fPIE" foi adicionada no comando de compilação, entretanto o erro persistiu.
* Sendo assim, as implementações não consideraram o tipo cadeia.

############################ Instruções para construção do projeto ############################
O projeto inclui um makefile com algumas opções para automatizar o processo de execução e construção do projeto.
Para instalar as dependências do projeto (llvm-13, clang, entre outros), execute: make install
Para fazer build do projeto, execute: make build
Para construir um docker container com o projeto, execute: make container
Para executar o container, execute: make container-run

############################ Testes ############################
O projeto inclui uma pasta chamada "tests" que incluem alguns testes prontos.
Para construir os binários dos testes, execute: make test
Para executar algum teste, execute: ./output/X.out, onde X pode ser:
    - impar.out (imprime os ímpares de 0 ao valor digitado.)
    - par.out (imprime os pares de 0 ao valor digitado.)
    - pow.out (imprime a potência do valor digitado.)
    - sqrt.out (imprime a raíz quadrada do valor digitado.)
    - fibonacci.out (imprime a sequência de fibonacci até o valor digitado.)