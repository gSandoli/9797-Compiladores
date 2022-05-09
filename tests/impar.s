/* 
    ## Impar ##
    Imprime todos os impares de 0 até n 
*/

global:
    /* Declaração de variáveis */
    i : inteiro := 0
    n : inteiro := 10
ação:
    /* Lê valor do terminal */
    n := li();
    
    /* Loop */
    enquanto i <= n faça
        se i & 1 verdadeiro
            imprimei(i)
        fse;
        i := i + 1
    fenquanto;

    /* Fim de programa */
    termine(0)