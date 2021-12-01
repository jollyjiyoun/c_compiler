%{
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include "lex.yy.c"

void yyerror(const char *s);
int yylex();
int yywrap();
%}

%token IF ELSE INT CHAR L ADD MULTIPLY WORD NUM RETURN INCLUDE


%%
prog: headers word '(' ')' block
;

headers: headers headers
| INCLUDE
;

vtype: INT
| CHAR
;

word: vtype WORD
;

block: '{' decls slist '}'
|;

decls: decls decl
|;

slist: slist stat
| stat
;

decl: vtype word ';'
;

stat: IF '(' cond ')' block ELSE block
| WORD '=' expr ';'
| RETURN expr ';'
;

cond: expr L expr
;

expr: expr ADD fact
| expr MULTIPLY fact
| fact
;

fact: NUM
| WORD
;


%%

int main() {
	yyparse();
}


void yyerror(const char * msg) {
	fprintf(stderr, "line %d: %s\n", yylineno, msg);
}
