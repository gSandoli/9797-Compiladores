/* 
    ## Impar ##
    Imprime todos os impares de 0 até n 
*/

global:
    i : inteiro := 0
    n : inteiro := 10
ação:
    enquanto i <= n faça
        se i & 1 verdadeiro
            imprimei(i)
        fse;
        i := i + 1
    fenquanto;
    termine(0)