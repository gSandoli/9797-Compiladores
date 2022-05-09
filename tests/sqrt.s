/* 
    ## Raiz quadrada ## 
    √x = r
*/

global:
    /* Declaração de variáveis */
    n : real := 0.0
    i : real := 0.0
    r : real := 1.0
ação:
    n := lr();
    /* Caso base */
    se (n==0.0)|(n==1.0) verdadeiro
        imprimer(n);
        termine(0)
    fse;

    /* Loop */
    enquanto r <= n faça
        i := i + 1.0;
        r := i * 1.0
    fenquanto;

    /* Resultado */
    imprimer(i-1.0);
    
    /* Finalizando programa */
    termine(0)
