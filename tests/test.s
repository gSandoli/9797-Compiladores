tipo :
integer = inteiro
integerStruct = {chave : inteiro , value : cadeia}
integerArray = [10, 15, 20, 25] de inteiro

global :
a : inteiro := 1
b : integerStruct := {chave = 2, value = 3 }
c : inteiro := a == 4
diogo : inteiro := 5
dolly : inteiro := 6
nota : real := 7.7
test : cadeia := "diogo"

função:
teste2(valor a: inteiro) : inteiro =
    local:
        b: inteiro := 8
        c: inteiro := 9

    ação:
        enquanto i < 10 faça
            imprimei(i*11);
            se i > 12 verdadeiro
                imprimei(i);
                continue
            falso
                pare
            fse
        fenquanto;

        para x de 13 limite 14 faça
            imprimei(x + 15)
        fpara;

        retorne c*16

teste(valor a: inteiro) = 
    /* declaracao de variaveis - pronto*/
    local:
        c: inteiro := 17
        d: real := 18.18
        i: inteiro := 19

    /* lista de comandos */
    ação:
        enquanto i < 20 faça
            imprimei(i*21);
            i := i + 22;
            se i > 23 verdadeiro
                continue;
                diogo()
            fse
        fenquanto

calculaNota(ref aluno1: inteiro, ref aluno2: inteiro) : real =
    local:
        saida : real := 24
    ação:
        saida := (aluno1 + aluno2) / 25;
        retorne saida

ação:
    nota := calculaNota(diogo, gabriel);
    imprimer(nota)
