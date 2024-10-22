%token NUMBER // Define token NUMBER

%left '+' '-' 
%left '*' '/' '%' 
%left '(' ')'

%%

input: E{
    printf("\nResult=%d\n",$1);
    return 0;
};

// Define the grammar rules
E:E'+'E {$$=$1+$3;}
 |E'-'E {$$=$1-$3;}
 |E'*'E {$$=$1*$3;}
 |E'/'E {$$=$1/$3;}
 |E'%'E {$$=$1%$3;}
 |'('E')' {$$=$2;}
 | NUMBER {$$=$1;}
;

%%

void main()
{
    printf("\nEnter Any Arithmetic Expression: ");
    return yyparse(); 
}

void yyerror()
{
    printf("\nEntered arithmetic expression is Invalid\n\n");
}