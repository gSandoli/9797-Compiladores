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
* Outro ponto importante é que acabamos confundindo o nome da função "imprime" e colocamos "imprimec".

############################ Código Intermediário, Assembly e Executável ############################
Os testes utilizados nessas 3 fases são:
    - teste1.s = imprime a sequência de fibonacci até o valor digitado.
    - teste2.s = imprime os ímpares de 0 ao valor digitado.
    - teste3.s = imprime os pares de 0 ao valor digitado.
    - teste4.s = imprime a potência do valor digitado.
    - teste5.s = imprime a raíz quadrada do valor digitado.
    - teste6.s = cria uma variável do tipo inteiro e imprime seu valor.
    - teste7.s = exemplo do loop enquanto no qual imprime o valor de 0 a 9.
    - teste8.s = exemplo do comando "se verdadeiro".
    - teste9.s = exemplo do comando "se verdadeiro falso" com operador lógico "&".
    - teste10.s = exemplo do comando "se verdadeiro falso" com operador lógico "|".