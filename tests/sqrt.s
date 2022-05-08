/* 
    ## Potenciação ## 
    b^e = r
*/

global:
    x : inteiro := 1
    start : inteiro := 1
    end : inteiro := 1
    mid : inteiro := 0
ação:
    /* caso base */
    se (x==0)|(x==1) verdadeiro
        imprimei(x);
        termine(0)
    fse;

    enquanto start + 1 < end faça
        mid := start+(end-start)/2;

        se (mid==(x/mid)) verdadeiro
            imprimei(mid);
            termine(0)
        fse;

        se (mid>(x/mid)) verdadeiro
            end := mid
        falso
            start := mid
        fse
    fenquanto;
    imprimei(start)