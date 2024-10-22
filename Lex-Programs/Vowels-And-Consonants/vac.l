%{
int vow_count=0;
int const_count =0;
%}

%%
[aeiouAEIOU] {vow_count++;}
[bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ] {const_count++;}
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
    printf("Number of Vowels: %d\n", vow_count);
    printf("Number of Consonants: %d\n", const_count);
    return(0);
}

int yywrap()
{
    return 1;
}