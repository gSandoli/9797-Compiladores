/* 
    ## Potenciação ## 
    b^e = r
*/

global:
    i : inteiro := 0
    r : inteiro := 1
    b : inteiro := 5
    e : inteiro := 2
ação:
    enquanto i < e faça
        r := r * b;
        i := i + 1
    fenquanto;
    imprimei(r);
    termine(0)