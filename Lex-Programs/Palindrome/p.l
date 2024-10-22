%{
char str[1000];
int idx = 0;
%}

%%
. { str[idx++] = yytext[0]; }
\n { str[idx] = '\0'; return 0; }
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

    // Check if the string is a palindrome
    int len = strlen(str);
    int is_palindrome = 1;
    for(int i = 0; i < len / 2; i++) {
        if(str[i] != str[len - i - 1]) {
            is_palindrome = 0;
            break;
        }
    }

    if(is_palindrome) {
        printf("The string is a palindrome.\n");
    } else {
        printf("The string is not a palindrome.\n");
    }

    return 0;
}

int yywrap()
{
    return 1;
}