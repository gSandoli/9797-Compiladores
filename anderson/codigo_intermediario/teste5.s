/* 
    ## Raiz quadrada ## 
    √x = r
*/

global:
    /* Declaração de variáveis */
    n : inteiro := 0
    i : inteiro := 0
    r : inteiro := 1
ação:
    n := li();
    /* Caso base */
    se (n==0)|(n==1) verdadeiro
        imprimei(n);
        termine(0)
    fse;

    /* Loop */
    enquanto r <= n faça
        i := i + 1;
        r := i * i
    fenquanto;

    /* Resultado */
    imprimei(i-1);
    
    /* Finalizando programa */
    termine(0)
