/*
 * PARSER
 */

%{

/*** C++ Declarations ***/
#include "parser.hh"
#include "scanner.hh"

#define yylex driver.scanner_->yylex

%}

%code requires {
  #include <iostream>
  #include "driver.hh"
  #include "location.hh"
  #include "position.hh"
  #include "../classes/ast.h"
  #include "../classes/literal.h"
  #include "../classes/fator.h"
  #include "../classes/expressao.h"
  #include "../classes/funcao.h"
  #include "../classes/comando.h"

  using namespace A;
  using namespace std;
}

%code provides {
  namespace Simples  {
    // Forward declaration of the Driver class
    class Driver;

    inline void yyerror (const char* msg) {
      cerr << msg << endl;
    }
  }
}

/* Require bison 2.3 or later */
%require "2.4"
/* enable c++ generation */
%language "C++"
%locations
/* write out a header file containing the token defines */
%defines
/* add debug output code to generated parser. disable this for release
 * versions. */
%debug
/* namespace to enclose parser in */
%define api.namespace {Simples}
/* set the parser's class identifier */
%define api.parser.class {Parser}
/* set the parser */
%parse-param {Driver &driver}
/* set the lexer */
%lex-param {Driver &driver}
/* verbose error messages */
%define parse.error verbose
/* use newer C++ skeleton file */
%skeleton "lalr1.cc"
/* Entry point of grammar */
%start program

%union
{
 /* YYLTYPE */
  Ast             *ast;
  Literal         *literal;
  string          *stringVal;
  int  			      integerVal;
  double 			    doubleVal;
}

/* Tokens */
%token              TOK_EOF 0     "end of file"
%token			        EOL		        "end of line"
%token <stringVal> 	IDENTIFIER    "identifier"
%token <integerVal> INTEIROV      "inteiroV"
%token <doubleVal>  REALV         "realV"
%token <stringVal>  CADEIAV       "cadeia"

// tipos
%type <ast> program lista_comandos comando chamada_funcao args_chamada
%type <ast> expr expr_ari expr_ari_ expr_log expr_rel fator literal

// simbolos
%token  VIRGULA       "virgula"
%token  DOIS_PONTOS   "doisPontos"
%token  PONTO_VIRUGLA "pontoVirgula"
%token  ABR_PRT       "abreParenteses"
%token  FCH_PRT       "fechaParenteses"
%token  ABR_COL       "abreColchetes"
%token  FCH_COL       "fechaColchetes"
%token  ABR_CHV       "abreChaves"
%token  FCH_CHV       "fechaChaves"
%token  PONTO         "ponto"
%token  SOMA          "mais"
%token  SUBTRACAO     "menos"
%token  MULTIPLICACAO "multiplicacao"
%token  DIVISAO       "divisao"
%token  IGUAL_IGUAL   "igual_igual"
%token  DIFERENTE     "diferente"
%token  MENOR         "menor"
%token  MENOR_IGUAL   "menorIgual"
%token  MAIOR         "maior"
%token  MAIOR_IGUAL   "maiorIgual"
%token  E             "e"
%token  OU            "ou"
%token  PONTO_IGUAL   "pontoIgual"
%token  IGUAL         "igual"

//palavras reservadas
%token  PARE          "pare"
%token  CONTINUE      "continue"
%token  PARA          "para"
%token  FPARA         "fpara"
%token  ENQUANTO      "enquanto"
%token  FENQUANTO     "fenquanto"
%token  FACA          "faça"
%token  SE            "se"
%token  FSE           "fse"
%token  VERDADEIRO    "verdadeiro"
%token  FALSO         "falso"
%token  TIPO          "tipo"
%token  DE            "de"
%token  LIMITE        "limite"
%token  GLOBAL        "global"
%token  LOCAL         "local"
%token  VALOR         "valor"
%token  REF           "ref"
%token  RETORNE       "retorne"
%token  NULO          "nulo"
%token  INICIO        "início"
%token  FIM           "fim"
%token  FUNCAO        "função"
%token  ACAO          "ação"

%%

program: declaracoes { /*printf("terminou declaracoes\n");*/}
       | ACAO DOIS_PONTOS lista_comandos { driver.root = $3; }

declaracoes : lista_declaracao_de_tipos lista_declaracoes_de_globais lista_declaracoes_de_funcoes program

/* declaracao de tipos */
lista_declaracao_de_tipos : 
                          | TIPO DOIS_PONTOS lista_declaracao_tipo { /*printf("Declaração de tipos.\n");*/ }

lista_declaracao_tipo : declaracao_tipo
                      | lista_declaracao_tipo declaracao_tipo

declaracao_tipo : IDENTIFIER IGUAL descritor_tipo

descritor_tipo : IDENTIFIER
               | ABR_CHV tipo_campos FCH_CHV
			         | ABR_COL tipo_constantes FCH_COL DE IDENTIFIER

tipo_campos : tipo_campo
      			| tipo_campos VIRGULA tipo_campo

tipo_campo : IDENTIFIER DOIS_PONTOS IDENTIFIER 

tipo_constantes : INTEIROV
			        	| tipo_constantes VIRGULA INTEIROV

/* declaracao de globais */
lista_declaracoes_de_globais : 
                             | GLOBAL DOIS_PONTOS lista_declaracao_variavel { /*printf("Declaração de variavel global.\n");*/ }

lista_declaracao_variavel : IDENTIFIER DOIS_PONTOS IDENTIFIER PONTO_IGUAL expr
                          | lista_declaracao_variavel IDENTIFIER DOIS_PONTOS IDENTIFIER PONTO_IGUAL expr

criacao_de_registro : tipo_registro
                    | criacao_de_registro VIRGULA tipo_registro

tipo_registro : IDENTIFIER IGUAL literal

/* declaracao de funcoes */

lista_declaracoes_de_funcoes: 
                            | FUNCAO DOIS_PONTOS lista_declaracao_funcao { /*printf("Declaração de funções\n");*/ }

lista_declaracao_funcao: 
                       | IDENTIFIER ABR_PRT args FCH_PRT IGUAL corpo { /*printf("declaracao metodo\n");*/ } lista_declaracao_funcao
                       | IDENTIFIER ABR_PRT args FCH_PRT DOIS_PONTOS IDENTIFIER IGUAL corpo { /*printf("declaracao funcao\n");*/ } lista_declaracao_funcao

args: 
    | modificador IDENTIFIER DOIS_PONTOS IDENTIFIER
    | args VIRGULA modificador IDENTIFIER DOIS_PONTOS IDENTIFIER 

modificador: VALOR 
           | REF

corpo: declaracao_de_locais ACAO DOIS_PONTOS lista_comandos 

declaracao_de_locais:
                    | LOCAL DOIS_PONTOS lista_declaracao_variavel

/* expressoes */
expr : expr_log { $$ = $1; }
     | ABR_CHV criacao_de_registro FCH_CHV

expr_log : expr_log OU expr_rel
         | expr_log E expr_rel
         | expr_rel { $$ = $1; }

expr_rel : expr_rel MENOR_IGUAL expr_ari
         | expr_rel MAIOR_IGUAL expr_ari
         | expr_rel MENOR expr_ari
         | expr_rel MAIOR expr_ari
         | expr_rel DIFERENTE expr_ari
         | expr_rel IGUAL_IGUAL expr_ari
         | expr_ari { $$ = $1; }

expr_ari : expr_ari SUBTRACAO expr_ari_ { $$ = new ExpressaoAritmeticaSubtracao(driver.line, driver.col, $1, $3); }
         | expr_ari SOMA expr_ari_ { $$ = new ExpressaoAritmeticaSoma(driver.line, driver.col, $1, $3); }
         | expr_ari_ { $$ = $1; }

expr_ari_ : expr_ari_ MULTIPLICACAO fator { $$ = new ExpressaoAritmeticaMultiplicacao(driver.line, driver.col, $1, $3); }
          | expr_ari_ DIVISAO fator { $$ = new ExpressaoAritmeticaDivisao(driver.line, driver.col, $1, $3); }
          | fator { $$ = $1; }

fator : ABR_PRT expr FCH_PRT { $$ = new FatorExpressao(driver.line, driver.col, $2); }
      | literal { $$ = new FatorLiteral(driver.line, driver.col, $1); }
      | NULO { $$ = new FatorNil(driver.line, driver.col); }
      | chamada_funcao { $$ = new FatorFuncao(driver.line, driver.col, $1); }
      | local_de_armazenamento

chamada_funcao: IDENTIFIER ABR_PRT args_chamada FCH_PRT { $$ = new Funcao(driver.line, driver.col, $1, $3); }

args_chamada: { $$ = nullptr; }
            | expr { $$ = $1; }
            | args_chamada VIRGULA expr

local_de_armazenamento : IDENTIFIER
                       | local_de_armazenamento PONTO IDENTIFIER
                       | local_de_armazenamento ABR_PRT expr FCH_PRT

literal : INTEIROV {  $$ = new LiteralInteiro(driver.line, driver.col, $1); }
        | REALV { $$ = new LiteralReal(driver.line, driver.col,$1); }
        | CADEIAV { $$ = new LiteralCadeia(driver.line, driver.col,$1); }

/* comandos */
lista_comandos: { $$ = nullptr; }
              | comando { $$ = $1; }
              | comando PONTO_VIRUGLA lista_comandos { $$ = new ListaComando(driver.line, driver.col, $1, $3); }

comando: IDENTIFIER PONTO_IGUAL expr 
       | chamada_funcao { $$ = $1; }
       | SE expr VERDADEIRO lista_comandos FSE 
       | SE expr VERDADEIRO lista_comandos FALSO lista_comandos FSE 
       | PARA IDENTIFIER DE expr LIMITE expr FACA lista_comandos FPARA 
       | ENQUANTO expr FACA lista_comandos FENQUANTO 
       | PARE  
       | CONTINUE  
       | RETORNE expr 
%%

namespace Simples {
   void Parser::error(const location&, const string& m) {
        cerr << *driver.location_ << ": " << m << endl;
        driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
   }
}