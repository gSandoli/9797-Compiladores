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

lista_declaracao_de_tipos : 
                          | TIPO DOIS_PONTOS lista_declaracao_tipo

lista_declaracao_tipo : declaracao_tipo
                      | lista_declaracao_tipo declaracao_tipo

declaracao_tipo : IDENTIFIER IGUAL descritor_tipo

descritor_tipo : IDENTIFIER {std::cout << "declaracao de referencia " << std::endl; }
               | ABR_CHV tipo_campos FCH_CHV {std::cout << "declaracao de struct " << std::endl; }
			   | ABR_COL tipo_constantes FCH_COL DE IDENTIFIER {std::cout << "declaracao de array" << std::endl; }

tipo_campos : tipo_campo
			| tipo_campo VIRGULA tipo_campos

tipo_campo : IDENTIFIER DOIS_PONTOS IDENTIFIER

tipo_constantes : INTEIROV
				| tipo_constantes VIRGULA INTEIROV

constant : INTEIROV { std::cout << "Inteiro: " << $1 << std::endl; }
         | REALV  { std::cout << "Real: " << $1 << std::endl; }

variable : IDENTIFIER {  std::cout << "Identificador: " << *$1 << std::endl; }

//estados simbolo
virgula : VIRGULA { std::cout << "Simbolo: " << std::endl; }
dois_pontos : DOIS_PONTOS { std::cout << "Simbolo: " << std::endl; }
ponto_virgula : PONTO_VIRUGLA { std::cout << "Simbolo: " << std::endl; }
abr_prt : ABR_PRT { std::cout << "Simbolo: " << std::endl; }
fch_prt : FCH_PRT { std::cout << "Simbolo: " << std::endl; }
abr_col : ABR_COL { std::cout << "Simbolo: " << std::endl; }
fch_col : FCH_COL { std::cout << "Simbolo: " << std::endl; }
abr_chv : ABR_CHV { std::cout << "Simbolo: " << std::endl; }
fch_chv : FCH_CHV { std::cout << "Simbolo: " << std::endl; }
ponto : PONTO { std::cout << "Simbolo: " << std::endl; }
soma : SOMA { std::cout << "Simbolo: " << std::endl; }
subtracao : SUBTRACAO { std::cout << "Simbolo: " << std::endl; }
multiplicacao : MULTIPLICACAO { std::cout << "Simbolo: " << std::endl; }
divisao : DIVISAO { std::cout << "Simbolo: " << std::endl; }
igual_igual : IGUAL_IGUAL { std::cout << "Simbolo: " << std::endl; }
diferente : DIFERENTE { std::cout << "Simbolo: " << std::endl; }
menor : MENOR { std::cout << "Simbolo: " << std::endl; }
menor_igual : MENOR_IGUAL { std::cout << "Simbolo: " << std::endl; }
maior : MAIOR { std::cout << "Simbolo: " << std::endl; }
maior_igual : MAIOR_IGUAL { std::cout << "Simbolo: " << std::endl; }
e : E { std::cout << "Simbolo: " << std::endl; }
ou : OU { std::cout << "Simbolo: " << std::endl; }
ponto_igual : PONTO_IGUAL { std::cout << "Simbolo: " << std::endl; }
igual : IGUAL { std::cout << "Simbolo: " << std::endl; }

//estados palavras reservadas
pare : PARE { std::cout << "Palavra Reservada: " << std::endl; }
continue : CONTINUE { std::cout << "Palavra Reservada: " << std::endl; }
para : PARA { std::cout << "Palavra Reservada: " << std::endl; }
fpara : FPARA { std::cout << "Palavra Reservada: " << std::endl; }
enquanto : ENQUANTO { std::cout << "Palavra Reservada: " << std::endl; }
fenquanto : FENQUANTO { std::cout << "Palavra Reservada: " << std::endl; }
faca : FACA { std::cout << "Palavra Reservada: " << std::endl; }
se : SE { std::cout << "Palavra Reservada: " << std::endl; }
fse : FSE { std::cout << "Palavra Reservada: " << std::endl; }
verdadeiro : VERDADEIRO { std::cout << "Palavra Reservada: " << std::endl; }
falso : FALSO { std::cout << "Palavra Reservada: " << std::endl; }
tipo : TIPO { std::cout << "Palavra Reservada: " << std::endl; }
de : DE { std::cout << "Palavra Reservada: " << std::endl; }
limite : LIMITE { std::cout << "Palavra Reservada: " << std::endl; }
global : GLOBAL { std::cout << "Palavra Reservada: " << std::endl; }
local : LOCAL { std::cout << "Palavra Reservada: " << std::endl; }
valor : VALOR { std::cout << "Palavra Reservada: " << std::endl; }
ref : REF { std::cout << "Palavra Reservada: " << std::endl; }
retorne : RETORNE { std::cout << "Palavra Reservada: " << std::endl; }
nulo : NULO { std::cout << "Palavra Reservada: " << std::endl; }
inicio : INICIO { std::cout << "Palavra Reservada: " << std::endl; }
fim : FIM { std::cout << "Palavra Reservada: " << std::endl; }

eol : EOL
// ini_bloco : INI_BLOCO { std::cout << "Inicio Bloco: " << *$1 << std::endl; }
// fim_bloco : FIM_BLOCO { std::cout << "Fim Bloco: " << *$1 << std::endl; }

%%

namespace Simples {
   void Parser::error(const location&, const std::string& m) {
        std::cerr << *driver.location_ << ": " << m << std::endl;
        driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
   }
}