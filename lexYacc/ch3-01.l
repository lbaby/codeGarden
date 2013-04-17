%{
#include "ch3-01.h"
#include <stdio.h>
extern int yylval;
%}

%%
[0-9]+	{  
	printf("N:%s\n", yytext);
	yylval = atoi(yytext); 
	return NUMBER;
 }

[ \t] {printf("%s:\\t\n",yytext);}		/* ignore white space */

\n	return 0;	/* logical EOF */

. { printf(".:%s\n", yytext);
	return yytext[0]; }
%%

int main(void)

{
yyparse();
}


int yyerror(char *errmsg)
{
printf("%s:%d \n", errmsg,yylineno);
}
