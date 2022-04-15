tipo :
integer = inteiro
integerStruct = {chave : inteiro , value : cadeia}
integerArray = [10, 15, 20, 25] de inteiro

global :
a : inteiro := 0
b : integerStruct := {chave = 0, value = 15 }
c : inteiro := a == 15
diogo : inteiro := 0
dolly : inteiro := 0
nota : real := 0.0
test : cadeia := "diogo"

função:
teste2(valor a: inteiro) : inteiro =
    local:
        b: inteiro := 5
        c: inteiro := 0

    ação:
        enquanto i < 5 faça
            imprimei(i*2);
            se i > 10 verdadeiro
                imprimei(i);
                continue
            falso
                pare
            fse
        fenquanto;

        para x de 5 limite 10 faça
            imprimei(x + 10)
        fpara;

        retorne c*2

teste(valor a: inteiro) = 
    /* declaracao de variaveis - pronto*/
    local:
        c: inteiro := 5
        d: real := 5.56
        i: inteiro := 0

    /* lista de comandos */
    ação:
        enquanto i < 5 faça
            imprimei(i*2);
            i := i + 1;
            se i > 10 verdadeiro
                continue;
                diogo()
            fse
        fenquanto

calculaNota(ref aluno1: inteiro, ref aluno2: inteiro) : real =
    local:
        saida : real := 0
    ação:
        saida := (aluno1 + aluno2) / 2;
        retorne saida

ação:
    nota := calculaNota(diogo, gabriel);
    imprimer(nota)
