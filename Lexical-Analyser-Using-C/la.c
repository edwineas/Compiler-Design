#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{

    FILE *input, *output;
    int line_number = 1;  // line number
    int token_number = 0; // token number
    int i, flag, j;
    char ch, str[20];
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    char keyword[30][30] = {"int", "main", "if", "else", "do", "while"}; // keywords
    fprintf(output, "Line no. \t Token no. \t Token \t\t Lexeme\n\n");

    while (!feof(input))
    {
        i = 0;
        flag = 0;
        ch = fgetc(input);

        // Operators
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            fprintf(output, "%7d\t %7d\t Operator\t\t %7c\n", line_number, token_number, ch);
            token_number++;
        }

        // Special symbols
        else if (ch == ';' || ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == '?' || ch == '@' || ch == '!' || ch == '%' || ch == '#' )
        {
            fprintf(output, "%7d\t %7d\t Special symbol\t %7c\n", line_number, token_number, ch);
            token_number++;
        }

        // Numbers
        else if (isdigit(ch))
        {
            str[i++] = ch;
            ch = fgetc(input);

            while (isdigit(ch))
            {
                str[i++] = ch;
                ch = fgetc(input);
            }

            str[i] = '\0';
            fprintf(output, "%7d\t %7d\t Number\t\t %7s\n", line_number, token_number, str);
            token_number++;
            ungetc(ch, input);
        }

        // Identifiers and Keywords
        else if (isalpha(ch))
        {
            str[i++] = ch;
            ch = fgetc(input);

            while (isalnum(ch) && ch != ' ')
            {
                str[i++] = ch;
                ch = fgetc(input);
            }

            str[i] = '\0';

            for (j = 0; j <= 30; j++)
            {
                if (strcmp(str, keyword[j]) == 0)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag == 1)
            {
                fprintf(output, "%7d\t %7d\t Keyword\t\t %7s\n", line_number, token_number, str);
                token_number++;
                ungetc(ch, input);
            }

            else
            {
                fprintf(output, "%7d\t %7d\t Identifier\t\t %7s\n", line_number, token_number, str);
                token_number++;
                ungetc(ch, input);
            }
        }

        else if (ch == '\n')
        {
            line_number++;
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}