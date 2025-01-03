%{
#include <stdlib.h>
#include "y.tab.h"
extern int yylval;
%}

%%

[0-9]+  { yylval = atoi(yytext); return NUMBER; }
[ \t]   ; /* skip whitespace */
\n      return 0;
.       return yytext[0];

%%

int yywrap(void) {
    return 1;
}