%{
int COMMENT=0; 
%}

/* identifier patter */
identifier [a-zA-Z][a-zA-Z0-9]*

%% /* Rules Section start */

#.* { printf("\n%s is a preprocessor directive", yytext); } /* Preprocessor Directive */

"/*" { COMMENT = 1; } /* Comment start */
"*/" { COMMENT = 0; } /* Comment end */

int |
float |
char |
double |
while |
for |
struct |
typedef |
do |
if |
break |
continue |
void |
switch |
return |
else |
goto { if (!COMMENT) printf("\n%s is a keyword", yytext); } /* Keywords */

{identifier}\( { if (!COMMENT) printf("\nFUNCTION %s", yytext); } /* Function */

\{ { if (!COMMENT) printf("\nBLOCK BEGINS"); } /* Block Begins */
\} { if (!COMMENT) printf("\nBLOCK ENDS"); } /* Block Ends */

{identifier}(\[[0-9]*\])? { if (!COMMENT) printf("\n%s IDENTIFIER", yytext); } /* Identifier */

\".*\" { if (!COMMENT) printf("\n%s is a STRING", yytext); }  /* String */

[0-9]+ { if (!COMMENT) printf("\n%s is a NUMBER", yytext); } /* Number */

\( { if (!COMMENT) printf("%s", yytext); } /* Parenthesis start*/
\)(\:)? { if (!COMMENT) printf("\n%s", yytext); } /* Parenthesis end*/

= { if (!COMMENT) printf("\n%s is an ASSIGNMENT OPERATOR", yytext); } /* Assignment Operator */
\<= |
\>= |
\< |
== |
\> { if (!COMMENT) printf("\n%s is a RELATIONAL OPERATOR", yytext); } /* Relational Operator */

\+ |
\- |
\* |
\/ |
\% { if (!COMMENT) printf("\n%s is an ARITHMETIC OPERATOR", yytext); } /* Arithmetic Operator */

.|\n {}

%% /* Rules Section end */

int main()
{
    FILE *file; // File pointer
    file=fopen("var.c","r"); // Open the file
    if(!file) // If file not found
    {
        printf("could not open the file\n");
        exit(0);
    }
    yyin=file; // Set the file to read
    yylex(); // Call the lexer
    printf("\n"); 
    return(0);
}
int yywrap() // Function to wrap up the lexer
{
    return(1);
}

// Compile By
// lex lex.l
// gcc lex.yy.c
// ./a.out