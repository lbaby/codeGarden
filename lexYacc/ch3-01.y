%token  NUMBER 
%%
result:	expression		{ printf("%d\n", $1); }
	;


expression:	
		expression '+' NUMBER{ $$ = $1 + $3; printf("%d+%d\n", $1,$3); }
	|	NUMBER			{ $$ = $1; printf("=%d\n",$1); }
	;
