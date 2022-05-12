/* comparação */

global:
	g1 : inteiro := 10
	g2 : inteiro := 20

ação:
	se (g1 > 5) & (g2 < 30)
		verdadeiro
			imprimei(1)
		falso
			imprimei(0)
	fse