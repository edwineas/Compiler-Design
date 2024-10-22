%% /* Rule Section */

[a-zA-Z0-9_.]+\@[a-zA-Z0-9_]+\.[a-zA-Z0-9_]+ { printf("%s is a Valid Email ID", yytext); } /* Email ID */

[0-9]{10} { printf("%s is a Valid Mobile Number", yytext); } /* Mobile Number */

.+ { printf("%s is an Invalid Input", yytext); } /* Invalid Input */

%%

int main()
{
    FILE *file; // File pointer
    file=fopen("input.txt","r"); // Open the file
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

int yywrap()
{
    return 1;
}