/* 
    ## Potenciação ## 
    b^e = r
*/

global:
    /* Declaração de variáveis */
    b : inteiro := 0
    e : inteiro := 0
    i : inteiro := 0
    r : inteiro := 1
ação:
    /* Lê valor do terminal */
    b := li();
    e := li();

    /* Loop */
    enquanto i < e faça
        r := r * b;
        i := i + 1
    fenquanto;

    /* Resultado */
    imprimei(r);

    /* Fim de programa */
    termine(0)