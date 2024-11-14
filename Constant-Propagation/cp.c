#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct expr
{
    char op[2], op1[5], op2[5], res[5];
    int flag;
} arr[10];

int n;

void change(int i, char *res)
{
    for (int j = i + 1; j < n; j++)
    {
        if (strcmp(arr[i].res, arr[j].op1) == 0) // If the result of ith expression is equal to the first operand of jth expression
            strcpy(arr[j].op1, res); 
        else if (strcmp(arr[i].res, arr[j].op2) == 0) // If the result of ith expression is equal to the second operand of jth expression
            strcpy(arr[j].op2, res);
    }
}

void main()
{
    // Input Section
    int i, op1, op2, res;
    char op, result[5];
    printf("Enter the number of  expressions : ");
    scanf("%d", &n);
    printf("\nEnter the expressions : \n");
    for (i = 0; i < n; i++)
    {
        scanf("%s", arr[i].op);
        scanf("%s", arr[i].op1);
        scanf("%s", arr[i].op2);
        scanf("%s", arr[i].res);
        arr[i].flag = 0;
    }
    // Implementation section
    for (i = 0; i < n; i++)
    {
        if (isdigit(arr[i].op1[0]) && isdigit(arr[i].op2[0]) || strcmp(arr[i].op, "=") == 0) // if both are digits or opertor is '='
        {
            op1 = atoi(arr[i].op1); // Convert first operand to integer
            op2 = atoi(arr[i].op2); // Convert second operand to integer
            op = arr[i].op[0];
            switch (op)
            {
            case '+':
                res = op1 + op2;
                break;
            case '-':
                res = op1 - op2;
                break;
            case '*':
                res = op1 * op2;
                break;
            case '/':
                res = op1 / op2;
                break;
            case '=':
                res = op1;
                break;
            }
            sprintf(result, "%d", res);
            arr[i].flag = 1;
            change(i, result); // Change the value of res in the next expressions
        }
    }
    // Output Section
    printf("\nOptimized code is : \n");
    for (i = 0; i < n; i++)
    {
        if (!arr[i].flag)
        {
            printf("%s %s %s %s\n", arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
        }
    }
}

// INPUT :

//     Enter the maximum number of expressions : 4

//     Enter the input :
//     = 3 - a
//     + a b t1
//     + a c t2
//     + t1 t2 t3

// OUTPUT :

//     Optimized code is :
//     + 3 b t1
//     + 3 c t2
//     + t1 t2 t3