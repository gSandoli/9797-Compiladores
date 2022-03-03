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

//palavras reservadas
%token <stringVal>  PARE       "pare"
%token <stringVal>  CONTINUE       "continue"
%token <stringVal>  PARA       "para"
%token <stringVal>  FPARA       "fpara"
%token <stringVal>  ENQUANTO       "enquanto"
%token <stringVal>  FENQUANTO       "fenquanto"
%token <stringVal>  FACA       "faça"
%token <stringVal>  SE       "se"
%token <stringVal>  FSE       "fse"
%token <stringVal>  VERDADEIRO       "verdadeiro"
%token <stringVal>  FALSO       "falso"
%token <stringVal>  TIPO       "tipo"
%token <stringVal>  DE       "de"
%token <stringVal>  LIMITE       "limite"
%token <stringVal>  GLOBAL       "global"
%token <stringVal>  LOCAL       "local"
%token <stringVal>  INTEIRO       "inteiro"
%token <stringVal>  REAL       "real"
%token <stringVal>  CADEIA       "cadeia"
%token <stringVal>  VALOR       "valor"
%token <stringVal>  REF       "ref"
%token <stringVal>  RETORNE       "retorne"
%token <stringVal>  NULO       "nulo"
%token <stringVal>  INICIO       "início"
%token <stringVal>  FIM       "fim"


// %token <stringVal>  INI_BLOCO     "iniBloco"
// %token <stringVal>  FIM_BLOCO     "fimBloco"

%%

program:  /* empty */
        | constant program
        | variable program
        | pare program
        | continue program
        | para program
        | fpara program
        | enquanto program
        | fenquanto program
        | faca program
        | se program
        | fse program
        | verdadeiro program
        | falso program
        | tipo program
        | de program
        | limite program
        | global program
        | local program
        | inteiro program
        | real program
        | cadeia program
        | valor program
        | ref program
        | retorne program
        | nulo program
        | inicio program
        | fim program
        | virgula program
        | dois_pontos program
        | ponto_virgula program
        | abr_prt program
        | fch_prt program
        | abr_col program
        | fch_col program
        | abr_chv program
        | fch_chv program
        | ponto program
        | soma program
        | subtracao program
        | multiplicacao program
        | divisao program
        | igual_igual program
        | diferente program
        | menor program
        | menor_igual program
        | maior program
        | maior_igual program
        | e program
        | ou program
        | ponto_igual program
        | igual program
        | eol program


constant : INTEIROV { std::cout << "Inteiro: " << $1 << std::endl; }
         | REALV  { std::cout << "Real: " << $1 << std::endl; }

variable : IDENTIFIER {  std::cout << "Identificador: " << *$1 << std::endl; }

//estados simbolo
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

//estados palavras reservadas
pare : PARE { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
continue : CONTINUE { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
para : PARA { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
fpara : FPARA { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
enquanto : ENQUANTO { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
fenquanto : FENQUANTO { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
faca : FACA { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
se : SE { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
fse : FSE { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
verdadeiro : VERDADEIRO { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
falso : FALSO { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
tipo : TIPO { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
de : DE { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
limite : LIMITE { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
global : GLOBAL { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
local : LOCAL { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
inteiro : INTEIRO { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
real : REAL { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
cadeia : CADEIA { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
valor : VALOR { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
ref : REF { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
retorne : RETORNE { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
nulo : NULO { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
inicio : INICIO { std::cout << "Palavra Reservada: " << *$1 << std::endl; }
fim : FIM { std::cout << "Palavra Reservada: " << *$1 << std::endl; }

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