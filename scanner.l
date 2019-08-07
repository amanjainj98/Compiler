%{
	#include "parser.tab.h"
	// #include "storetokens.hh"
%}

int yylineno=1;
num [0-9]
id [a-zA-Z_][a-zA-Z0-9_]*
operator [+\-*/]
metachar [\(\){};,?:]
and "&&"
or "||"
not "!"
less "<"
lesseq "<="
greater ">"
greatereq ">="
equal "=="
notequal "!="



%%

[ \t]+ 	;
"//".*	;
int 	{store_token_name("INTEGER",yytext,yylineno); return INTEGER;}
float 	{store_token_name("FLOAT",yytext,yylineno); return FLOAT;}
void	{store_token_name("VOID",yytext,yylineno); return VOID;}
{num}+  	{store_token_name("NUM",yytext,yylineno); yylval.integer_value = atoi(yytext); return INTEGER_NUMBER;}
{num}*\.{num}+	{store_token_name("FNUM",yytext,yylineno); yylval.double_value = atof(yytext); return DOUBLE_NUMBER;}
{num}+\.{num}*	{store_token_name("FNUM",yytext,yylineno); yylval.double_value = atof(yytext); return DOUBLE_NUMBER;}
{operator} 	{store_token_name("ARITHOP",yytext,yylineno); return yytext[0];}
{metachar} 	{store_token_name("META CHAR",yytext,yylineno); return yytext[0];}
=   	{store_token_name("ASSIGN_OP",yytext,yylineno); return ASSIGN;}
{and}		{store_token_name("AND",yytext,yylineno); return AND;}
{or}		{store_token_name("OR",yytext,yylineno); return OR;}
{not}		{store_token_name("NOT",yytext,yylineno); return NOT;}
{less}	{store_token_name("LESS_THAN",yytext,yylineno); return LESS_THAN;}
{lesseq}	{store_token_name("LESS_THAN_EQUAL",yytext,yylineno); return LESS_THAN_EQUAL;}
{greater}	{store_token_name("GREATER_THAN",yytext,yylineno); return GREATER_THAN;}
{greatereq}	{store_token_name("GREATER_THAN_EQUAL",yytext,yylineno); return GREATER_THAN_EQUAL;}
{equal}	{store_token_name("EQUAL",yytext,yylineno); return EQUAL;}
{notequal}	{store_token_name("NOT_EQUAL",yytext,yylineno); return NOT_EQUAL;}
while	{store_token_name("WHILE",yytext,yylineno); return WHILE;}
do	{store_token_name("DO",yytext,yylineno); return DO;}
if	{store_token_name("IF",yytext,yylineno); return IF;}
else	{store_token_name("ELSE",yytext,yylineno); return ELSE;}
return	{store_token_name("RETURN",yytext,yylineno); return RETURN;}
print	{store_token_name("PRINT",yytext,yylineno); return PRINT;}
{id}  	{store_token_name("NAME",yytext,yylineno); std::string* text = new std::string(yytext); if(*text != "main") *text = *text+"_";  yylval.string_value = (std::string*)(text); return NAME;}

\n 		{}
.		{printf("Error : Line: %d: scanner internal error--no action found\n",yylineno);}

%%
