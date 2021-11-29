%{
# include "y.tab.h"
int countn = 0; /* keep track of line number */
%}

%option yylineno

word [a-zA-Z]*
num [0-9]*

%%

"int"				{ return INT; }
"char"				{ return CHAR; }
"if"				{ return IF; }
"else"				{ return ELSE; }
"return"			{ return RETURN; }
^"#include"[ ]*<.+\.h>		{ return INCLUDE; }
"<"				{ return L; }
"+"				{ return ADD; }
"*"				{ return MULTIPLY; }
[\n]				{ countn++; }
[\t]*				{ ; }
[ ]*				{ ; }
\/\/.*				{ ; }
\/\*(.*\n)*.*\*\/		{ ; }
{word}				{ return WORD; }
{num}				{ return NUM; }

%%

int yywrap(){
	return 1;
}
