%{ /* -*- C++ -*- */

#include "parser.hh"
#include "scanner.hh"
#include "driver.hh"

/*  Defines some macros to update locations */
#define STEP() do {driver.location_->step();} while (0)
#define COL(col) driver.location_->columns(col)
#define LINE(line) do {driver.location_->lines(line);} while (0)
#define YY_USER_ACTION COL(yyleng);

/* import the parser's token type into a local typedef */
typedef Simples::Parser::token token;
typedef Simples::Parser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::TOK_EOF

std::string s_str;

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
     yylval->integerVal = atoi(yytext);
     return token::INTEIROV;
 }

[0-9]+"."[0-9]* {
    yylval->doubleVal = atof(yytext);
    return token::REALV;
}

"pare" {
	return token::PARE;
}
"continue" {
	return token::CONTINUE;
}
"para" {
	return token::PARA;
}
"fpara" {
	return token::FPARA;
}
"enquanto" {
	return token::ENQUANTO;
}
"fenquanto" {
	return token::FENQUANTO;
}
"faça" {
	return token::FACA;
}
"se" {
	return token::SE;
}
"fse" {
	return token::FSE;
}
"verdadeiro" {
	return token::VERDADEIRO;
}
"falso" {
	return token::FALSO;
}
"tipo" {
	return token::TIPO;
}
"de" {
	return token::DE;
}
"limite" {
	return token::LIMITE;
}
"global" {
	return token::GLOBAL;
}
"local" {
	return token::LOCAL;
}
"valor" {
	return token::VALOR;
}
"ref" {
	return token::REF;
}
"retorne" {
	return token::RETORNE;
}
"nulo" {
	return token::NULO;
}
"início" {
	return token::INICIO;
}
"fim" {
	return token::FIM;
}
"função" {
	return token::FUNCAO;
} 
"ação" {
	return token::ACAO;
} 
"," {
	return token::VIRGULA;
}
":" {
	return token::DOIS_PONTOS;
}
";" {
	return token::PONTO_VIRUGLA;
}
"(" {
	return token::ABR_PRT;
}
")" {
	return token::FCH_PRT;
}
"[" {
	return token::ABR_COL;
}
"]" {
	return token::FCH_COL;
}
"{" {
	return token::ABR_CHV;
}
"}" {
	return token::FCH_CHV;
}
"." {
	return token::PONTO;
}
"+" {
	return token::SOMA;
}
"-" {
	return token::SUBTRACAO;
}
"*" {
	return token::MULTIPLICACAO;
}
"/" {
	return token::DIVISAO;
}
"==" {
	return token::IGUAL_IGUAL;
}
"!=" {
	return token::DIFERENTE;
}
"<" {
	return token::MENOR;
}
"<=" {
	return token::MENOR_IGUAL;
}
">" {
	return token::MAIOR;
}
">=" {
	return token::MAIOR_IGUAL;
}
"&" {
	return token::E;
}
"|" {
	return token::OU;
}
":=" {
	return token::PONTO_IGUAL;
}
"=" {
	return token::IGUAL;
}

[A-Za-z][A-Za-z0-9]* {
    yylval->stringVal = new std::string(yytext, yyleng);
    return token::IDENTIFIER;
}

"/\*" {
	BEGIN(COMENTARIO);
}

"\"" {
	s_str = "";
	BEGIN(CADEIA);
}
}

<COMENTARIO>{
	<<EOF>> {
		std::cout << "[ERRO LEXICO] Comentario nao terminado.\n";
		exit(1);
	}

	"\*/" {
		BEGIN(INITIAL);
	}

	. {}
}

<CADEIA>{
	<<EOF>> {
		std::cout << "[ERRO LEXICO] Comentario nao terminado.\n";
		exit(1);
	}

	"\"" {
		/* yylval->cad = s_str; */
		std::cout <<  "Scanner: " << s_str << "\n";
		BEGIN(INITIAL);
		return token::CADEIAV;
	}

	. {
		s_str += yytext;
	}
}

{blank} { STEP(); }

{eol}  { LINE(yyleng); }

. {
	std::cerr << *driver.location_ << " Unexpected token : " << *yytext << std::endl;
	driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
	STEP ();
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
  std::cerr << "call parsepitFlexLexer::yylex()!" << std::endl;
  return 0;
}