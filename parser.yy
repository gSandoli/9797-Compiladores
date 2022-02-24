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
%token <integerVal> INTEGER		    "integer"
%token <doubleVal> 	REAL		      "real"
%token <stringVal> 	IDENTIFIER    "identifier"
%token <stringVal>  KEYWORD       "keyword"
%token <stringVal>  VIRGULA       "virgula"
%token <stringVal>  DOIS_PONTOS   "doisPontos"
%token <stringVal>  PONTO_VIRUGLA "pontoVirgula"
%token <stringVal>  ABR_PRT       "abreParenteses"
%token <stringVal>  FCH_PRT       "fechaParenteses"
%token <stringVal>  ABR_COL       "abreColchetes"
%token <stringVal>  FCH_COL       "fechaColchetes"
%token <stringVal>  ABR_CHV       "abreChaves"
%token <stringVal>  FCH_CHV       "fechaChaves"
%token <stringVal>  PONTO         "ponto"
%token <stringVal>  SOMA          "mais"
%token <stringVal>  SUBTRACAO     "menos"
%token <stringVal>  MULTIPLICACAO "multiplicacao"
%token <stringVal>  DIVISAO       "divisao"
%token <stringVal>  IGUAL_IGUAL   "igual_igual"
%token <stringVal>  DIFERENTE     "diferente"
%token <stringVal>  MENOR         "menor"
%token <stringVal>  MENOR_IGUAL    "menorIgual"
%token <stringVal>  MAIOR         "maior"
%token <stringVal>  MAIOR_IGUAL    "maiorIgual"
%token <stringVal>  E             "e"
%token <stringVal>  OU            "ou"
%token <stringVal>  PONTO_IGUAL    "pontoIgual"
%token <stringVal>  IGUAL         "igual"

/* %token <stringVal>  INI_BLOCO     "iniBloco"
%token <stringVal>  FIM_BLOCO     "fimBloco" */

/* entender como iniciar e finalizar um bloco */

%%

program:  /* empty */
        | constant
        | variable
        | keyword
        | virgula
        | dois_pontos
        | ponto_virgula
        | abr_prt
        | fch_prt
        | abr_col
        | fch_col
        | abr_chv
        | fch_chv
        | ponto
        | soma
        | subtracao
        | multiplicacao
        | divisao
        | igual_igual
        | diferente
        | menor
        | menor_igual
        | maior
        | maior_igual
        | e
        | ou
        | ponto_igual
        | igual


constant : INTEGER { std::cout << "Inteiro: " << $1 << std::endl; }
         | REAL  { std::cout << "Real: " << $1 << std::endl; }

variable : IDENTIFIER {  std::cout << "Identificador: " << *$1 << std::endl; }

keyword : KEYWORD { std::cout << "Palavra Reservada: " << *$1 << std::endl; }

virgula : VIRGULA { std::cout << "Simbolo: " << *$1 << std::endl; }
dois_pontos : DOIS_PONTOS { std::cout << "Simbolo: " << *$1 << std::endl; }
ponto_virgula : PONTO_VIRUGLA { std::cout << "Simbolo: " << *$1 << std::endl; }
abr_prt : ABR_PRT { std::cout << "Simbolo: " << *$1 << std::endl; }
fch_prt : FCH_PRT { std::cout << "Simbolo: " << *$1 << std::endl; }
abr_col : ABR_COL { std::cout << "Simbolo: " << *$1 << std::endl; }
fch_col : FCH_COL { std::cout << "Simbolo: " << *$1 << std::endl; }
abr_chv : ABR_CHV { std::cout << "Simbolo: " << *$1 << std::endl; }
fch_chv : FCH_CHV { std::cout << "Simbolo: " << *$1 << std::endl; }
ponto : PONTO { std::cout << "Simbolo: " << *$1 << std::endl; }
soma : SOMA { std::cout << "Simbolo: " << *$1 << std::endl; }
subtracao : SUBTRACAO { std::cout << "Simbolo: " << *$1 << std::endl; }
multiplicacao : MULTIPLICACAO { std::cout << "Simbolo: " << *$1 << std::endl; }
divisao : DIVISAO { std::cout << "Simbolo: " << *$1 << std::endl; }
igual_igual : IGUAL_IGUAL { std::cout << "Simbolo: " << *$1 << std::endl; }
diferente : DIFERENTE { std::cout << "Simbolo: " << *$1 << std::endl; }
menor : MENOR { std::cout << "Simbolo: " << *$1 << std::endl; }
menor_igual : MENOR_IGUAL { std::cout << "Simbolo: " << *$1 << std::endl; }
maior : MAIOR { std::cout << "Simbolo: " << *$1 << std::endl; }
maior_igual : MAIOR_IGUAL { std::cout << "Simbolo: " << *$1 << std::endl; }
e : E { std::cout << "Simbolo: " << *$1 << std::endl; }
ou : OU { std::cout << "Simbolo: " << *$1 << std::endl; }
ponto_igual : PONTO_IGUAL { std::cout << "Simbolo: " << *$1 << std::endl; }
igual : IGUAL { std::cout << "Simbolo: " << *$1 << std::endl; }

/* ini_bloco : INI_BLOCO { std::cout << "Inicio Bloco: " << *$1 << std::endl; }

fim_bloco : FIM_BLOCO { std::cout << "Fim Bloco: " << *$1 << std::endl; } */

%%

namespace Simples {
   void Parser::error(const location&, const std::string& m) {
        std::cerr << *driver.location_ << ": " << m << std::endl;
        driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
   }
}
