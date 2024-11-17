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

input: expr {
    printf("\nResult=%d\n", $1);
    return 0;
};

expr: 
    expr '+' expr   { $$ = $1 + $3; }
   |expr '-' expr   { $$ = $1 - $3; }
   |expr '*' expr   { $$ = $1 * $3; }
   |expr '/' expr   { $$ = $1 / $3; }
   |expr '%' expr   { $$ = $1 % $3; }
   |'(' expr ')'    { $$ = $2; }
   |NUMBER          { $$ = $1; }
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