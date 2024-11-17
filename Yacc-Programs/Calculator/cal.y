%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER

%left '+' '-'    /* lowest precedence */
%left '*' '/' '%'  /* higher precedence */
%left '(' ')'    /* highest precedence */

%%

input: E {
    printf("\nResult=%d\n", $1);
    return 0;
};

E: 
    E '+' E { $$ = $1 + $3; }
   |E '-' E { $$ = $1 - $3; }
   |E '*' E { $$ = $1 * $3; }
   |E '/' E { $$ = $1 / $3; }
   |E '%' E { $$ = $1 % $3; }
   |'(' E ')' { $$ = $2; }
   |NUMBER { $$ = $1; }
;

%%

int main()
{
    printf("\nEnter Any Arithmetic Expression: ");
    return yyparse(); 
}

void yyerror(const char *s)
{
    printf("\nEntered arithmetic expression is Invalid: %s\n\n", s);
}