%{ /* -*- C++ -*- */

#include "parser.hh"
#include "scanner.hh"
#include "driver.hh"
using namespace std;

/*  Defines some macros to update locations */
#define STEP() do {driver.location_->step();} while (0)
#define COL(col) driver.location_->columns(col)
#define LINE(line) do {driver.location_->lines(line);} while (0)
#define YY_USER_ACTION COL(yyleng);
#define ADJ_COL {driver.col+=yyleng;}
#define ADJ_LINE {driver.line+=1; driver.col = 0;}

/* import the parser's token type into a local typedef */
typedef Simples::Parser::token token;
typedef Simples::Parser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::TOK_EOF

string s_str;
%}

/*** Flex Declarations and Options ***/

%s COMENTARIO
%s CADEIA
/* enable scanner to generate debug output. disable this for release
 * versions. */
%option debug
/* enable c++ scanner class generation */
%option c++
/* we don’t need yywrap */
%option noyywrap
/* you should not expect to be able to use the program interactively */
%option never-interactive
/* provide the global variable yylineno */
%option yylineno
/* do not fabricate input text to be scanned */
%option nounput
/* the manual says "somewhat more optimized" */
%option batch
/* change the name of the scanner class. results in "SimplesFlexLexer" */
%option prefix="Simples"

/*
%option stack
*/

/* Abbreviations.  */

blank   [ \t]+
eol     [\n\r]+

%%

 /* The following paragraph suffices to track locations accurately. Each time
 yylex is invoked, the begin position is moved onto the end position. */
%{
  STEP();
%}

 /*** BEGIN EXAMPLE - Change the example lexer rules below ***/

<INITIAL>{
[0-9]+ {
	ADJ_COL;
    yylval->integerVal = atoi(yytext);
    return token::INTEIROV;
 }

[0-9]+"."[0-9]* {
	ADJ_COL;
    yylval->doubleVal = atof(yytext);
    return token::REALV;
}

"pare" {
	ADJ_COL;
	return token::PARE;
}
"continue" {
	ADJ_COL;
	return token::CONTINUE;
}
"para" {
	ADJ_COL;
	return token::PARA;
}
"fpara" {
	ADJ_COL;
	return token::FPARA;
}
"enquanto" {
	ADJ_COL;
	return token::ENQUANTO;
}
"fenquanto" {
	ADJ_COL;
	return token::FENQUANTO;
}
"faça" {
	ADJ_COL;
	return token::FACA;
}
"se" {
	ADJ_COL;
	return token::SE;
}
"fse" {
	ADJ_COL;
	return token::FSE;
}
"verdadeiro" {
	ADJ_COL;
	return token::VERDADEIRO;
}
"falso" {
	ADJ_COL;
	return token::FALSO;
}
"tipo" {
	ADJ_COL;
	return token::TIPO;
}
"de" {
	ADJ_COL;
	return token::DE;
}
"limite" {
	ADJ_COL;
	return token::LIMITE;
}
"global" {
	ADJ_COL;
	return token::GLOBAL;
}
"local" {
	ADJ_COL;
	return token::LOCAL;
}
"valor" {
	ADJ_COL;
	return token::VALOR;
}
"ref" {
	ADJ_COL;
	return token::REF;
}
"retorne" {
	ADJ_COL;
	return token::RETORNE;
}
"nulo" {
	ADJ_COL;
	return token::NULO;
}
"função" {
	ADJ_COL;
	return token::FUNCAO;
} 
"ação" {
	ADJ_COL;
	return token::ACAO;
} 
"," {
	ADJ_COL;
	return token::VIRGULA;
}
":" {
	ADJ_COL;
	return token::DOIS_PONTOS;
}
";" {
	ADJ_COL;
	return token::PONTO_VIRUGLA;
}
"(" {
	ADJ_COL;
	return token::ABR_PRT;
}
")" {
	ADJ_COL;
	return token::FCH_PRT;
}
"[" {
	ADJ_COL;
	return token::ABR_COL;
}
"]" {
	ADJ_COL;
	return token::FCH_COL;
}
"{" {
	ADJ_COL;
	return token::ABR_CHV;
}
"}" {
	ADJ_COL;
	return token::FCH_CHV;
}
"." {
	ADJ_COL;
	return token::PONTO;
}
"+" {
	ADJ_COL;
	return token::SOMA;
}
"-" {
	ADJ_COL;
	return token::SUBTRACAO;
}
"*" {
	ADJ_COL;
	return token::MULTIPLICACAO;
}
"/" {
	ADJ_COL;
	return token::DIVISAO;
}
"==" {
	ADJ_COL;
	return token::IGUAL_IGUAL;
}
"!=" {
	ADJ_COL;
	return token::DIFERENTE;
}
"<" {
	ADJ_COL;
	return token::MENOR;
}
"<=" {
	ADJ_COL;
	return token::MENOR_IGUAL;
}
">" {
	ADJ_COL;
	return token::MAIOR;
}
">=" {
	ADJ_COL;
	return token::MAIOR_IGUAL;
}
"&" {
	ADJ_COL;
	return token::E;
}
"|" {
	ADJ_COL;
	return token::OU;
}
":=" {
	ADJ_COL;
	return token::PONTO_IGUAL;
}
"=" {
	ADJ_COL;
	return token::IGUAL;
}

[_A-Za-z][_A-Za-z0-9]* {
	ADJ_COL;
    yylval->stringVal = new string(yytext, yyleng);
    return token::IDENTIFIER;
}

"/\*" {
	ADJ_COL;
	BEGIN(COMENTARIO);
}

"\"" {
	ADJ_COL;
	s_str = "";
	BEGIN(CADEIA);
}
}

<COMENTARIO>{
	<<EOF>> {
		ADJ_COL;
		cout << "[ERRO LEXICO] Comentario nao terminado.\n";
		exit(1);
	}

	"\*/" {
		ADJ_COL;
		BEGIN(INITIAL);
	}

	. {ADJ_COL;}
}

<CADEIA>{
	<<EOF>> {
		ADJ_COL;
		cout << "[ERRO LEXICO] Cadeia nao terminada.\n";
		exit(1);
	}

	"\"" {
		ADJ_COL;
		BEGIN(INITIAL);
		yylval->stringVal = new string(s_str);
		return token::CADEIAV;
	}

	. {
		ADJ_COL;
		s_str += yytext;
	}
}

{blank} { ADJ_COL;STEP(); }

{eol}  { ADJ_LINE; LINE(yyleng); }

. {
	ADJ_COL;
	cerr << *driver.location_ << " token inesperado : " << *yytext << endl;
	driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
	STEP();
}

%%

/* CUSTOM C++ CODE */

namespace Simples {

  Scanner::Scanner() : SimplesFlexLexer() {}

  Scanner::~Scanner() {}

  void Scanner::set_debug(bool b) {
    yy_flex_debug = b;
  }
}

#ifdef yylex
# undef yylex
#endif

int SimplesFlexLexer::yylex()
{
  cerr << "call parsepitFlexLexer::yylex()!" << endl;
  return 0;
}