#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack implementation
char stack[MAX][10];
int top = -1;

// Function to push to the stack
void push(char *str) {
    strcpy(stack[++top], str);
}

// Function to pop from the stack
void pop(char *str) {
    if (top == -1) return;
    strcpy(str, stack[top--]);
}

// Function to get precedence of operators
int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

// Function to convert infix expression to postfix
void infixToPostfix(char *infix, char *postfix) {
    char temp[MAX];
    int k = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        if (isalnum(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            temp[0] = infix[i];
            temp[1] = '\0';
            push(temp);
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top][0] != '(') {
                postfix[k++] = stack[top--][0];
            }
            top--; // pop '(' from stack
        } else {
            while (top != -1 && precedence(stack[top][0]) >= precedence(infix[i])) {
                postfix[k++] = stack[top--][0];
            }
            temp[0] = infix[i];
            temp[1] = '\0';
            push(temp);
        }
    }
    while (top != -1) {
        postfix[k++] = stack[top--][0];
    }
    postfix[k] = '\0';
}

// Function to generate intermediate code
void generateCode(char *postfix, char assignmentVar) {
    int t = 0;
    char op1[10], op2[10], temp[10];

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            char operand[2] = {postfix[i], '\0'};
            push(operand);
        } else {
            pop(op2);
            pop(op1);

            sprintf(temp, "T%d", t++);
            printf("%s = %s %c %s\n", temp, op1, postfix[i], op2);
            push(temp);
        }
    }
    // Final assignment
    pop(temp);
    printf("%c = %s\n", assignmentVar, temp);
}

int main() {
    char infix[MAX], postfix[MAX];

    // Input the expression
    printf("Enter the infix expression (e.g., a=3+b*c-d^e/f): ");
    scanf("%s", infix);

    // Extract LHS (variable) and RHS (expression)
    char assignmentVar = infix[0]; // Get the LHS variable (e.g., 'a')
    char *rhs = infix + 2; // Skip "a=" to get the RHS expression

    // Convert the RHS to postfix
    infixToPostfix(rhs, postfix);
    printf("Postfix Expression: %s\n", postfix);

    // Generate intermediate code
    printf("\nIntermediate Code:\n");
    generateCode(postfix, assignmentVar);

    return 0;
}
