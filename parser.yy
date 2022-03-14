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
}

%code provides {
  namespace Simples  {
    // Forward declaration of the Driver class
    class Driver;

    inline void yyerror (const char* msg) {
      std::cerr << msg << std::endl;
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
  int  			      integerVal;
  double 			    doubleVal;
  std::string*		stringVal;
}

/* Tokens */
%token              TOK_EOF 0     "end of file"
%token			        EOL		        "end of line"
%token <stringVal> 	IDENTIFIER    "identifier"
%token <integerVal> INTEIROV      "inteiroV"
%token <doubleVal>  REALV         "realV"

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

%%

program: declaracoes

declaracoes : lista_declaracao_de_tipos
            | lista_declaracoes_de_globais

/* declaracao de tipos */
lista_declaracao_de_tipos : 
                          | TIPO DOIS_PONTOS lista_declaracao_tipo { printf("Declaração de tipos.\n"); } declaracoes

lista_declaracao_tipo : declaracao_tipo
                      | lista_declaracao_tipo declaracao_tipo

declaracao_tipo : IDENTIFIER IGUAL descritor_tipo

descritor_tipo : IDENTIFIER {std::cout << "declaracao de referencia " << std::endl; }
               | ABR_CHV tipo_campos FCH_CHV {std::cout << "declaracao de struct " << std::endl; }
			         | ABR_COL tipo_constantes FCH_COL DE IDENTIFIER {std::cout << "declaracao de array" << std::endl; }

tipo_campos : tipo_campo
      			| tipo_campos VIRGULA tipo_campo

tipo_campo : IDENTIFIER DOIS_PONTOS IDENTIFIER 

tipo_constantes : INTEIROV
			        	| tipo_constantes VIRGULA INTEIROV

/* declaracao de globais */
lista_declaracoes_de_globais : 
                             | GLOBAL DOIS_PONTOS lista_declaracao_variavel { printf("Declaração de variavel global.\n"); }

lista_declaracao_variavel : IDENTIFIER DOIS_PONTOS IDENTIFIER PONTO_IGUAL expr
                          | lista_declaracao_variavel IDENTIFIER DOIS_PONTOS IDENTIFIER PONTO_IGUAL expr

criacao_de_registro : tipo_registro
                    | criacao_de_registro VIRGULA tipo_registro

tipo_registro : IDENTIFIER IGUAL literal

expr : expr_log
     | ABR_CHV criacao_de_registro FCH_CHV { printf("Declaração de variavel de registro.\n"); }

expr_log : expr_log OU expr_rel { printf("expr logica OU\n" ); }
         | expr_log E expr_rel { printf("expr logica E\n" ); }
         | expr_rel

expr_rel : expr_rel MENOR_IGUAL expr_ari { printf("expr relacional <=\n" ); }
         | expr_rel MAIOR_IGUAL expr_ari { printf("expr relacional >=\n" ); }
         | expr_rel MENOR expr_ari { printf("expr relacional <\n" ); }
         | expr_rel MAIOR expr_ari { printf("expr relacional >\n" ); }
         | expr_rel DIFERENTE expr_ari { printf("expr relacional !=\n" ); }
         | expr_rel IGUAL_IGUAL expr_ari { printf("expr relacional ==\n" ); }
         | expr_ari

expr_ari : expr_ari SUBTRACAO expr_ari_ { printf("expr aritmetica - \n" ); }
         | expr_ari SOMA expr_ari_ { printf("expr aritmetica +\n" ); }
         | expr_ari_ 

expr_ari_ : expr_ari_ MULTIPLICACAO fator { printf("expr aritmetica *\n" ); }
          | expr_ari_ DIVISAO fator { printf("expr aritmetica /\n" ); }
          | fator

fator : ABR_PRT expr FCH_PRT { printf("achou um fator () \n" ); }
      | literal { printf("achou um literal\n" ); }
      | NULO { printf("achou um nulo\n" ); }
      | chamada_funcao { printf("achou uma chamada de funcao\n" ); }
      | local_de_armazenamento { printf("achou um local de armazenamento\n" ); }

chamada_funcao : 
               /*| IDENTIFIER ABR_PRT args FCH_PRT ]
                  criar estados "args"
               */

local_de_armazenamento : IDENTIFIER

literal : INTEIROV
        | REALV
        /* | CADEIAV */

%%

namespace Simples {
   void Parser::error(const location&, const std::string& m) {
        std::cerr << *driver.location_ << ": " << m << std::endl;
        driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
   }
}