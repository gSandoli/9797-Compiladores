/* 
    ## Série de Fibonacci ## 
    Imprime a série de Fibonacci até n
*/

global:
    /* Declaração de variáveis */
    n : inteiro := 0
    i : inteiro := 3
    t1 : inteiro := 0
    t2 : inteiro := 1
    x : inteiro := 1
ação:
    /* Lê valor do terminal */
    n := li();

    /* Imprime os primeiros valores */
    x := t1 + t2;
    imprimei(t1);
    imprimei(t2);

    /* Loop */
    enquanto i <= n faça
        imprimei(x);
        t1 := t2;
        t2 := x;
        x := t1 + t2;
        i := i + 1
    fenquanto;
    
    /* Imprime o ultimo valor */
    imprimei(x);

    /* Finalizando programa */
    termine(0)
