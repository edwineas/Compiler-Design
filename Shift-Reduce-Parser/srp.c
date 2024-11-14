#include <stdio.h>
#include <string.h>

char inputString[100];
char stack[100];

char shift()
{
    char firstElement = inputString[0];
    memmove(inputString, inputString + 1, strlen(inputString)); // Copy the rest of the string to the beginning
    return firstElement;
}

void push(char token)
{
    int len = strlen(stack);
    stack[len] = token; // Push the token to the stack
    stack[len + 1] = '\0';
}

void printTableRow(const char *stack, const char *input, const char *action)
{
    printf("%-10s %-10s %-10s\n", stack, input, action);
}

int checkReducibility()
{
    int len = strlen(stack);
    if (len >= 1 && stack[len - 1] == 'i') // Check if the top element is 'i'
        return 1;
    if (len >= 3) // Check if the last three elements are of the form E+E or E*E or (E)
    {
        char lastThree[4];
        strncpy(lastThree, &stack[len - 3], 3); // Copy the last three elements to lastThree
        lastThree[3] = '\0';
        if (lastThree[0] == 'E' && (lastThree[1] == '+' || lastThree[1] == '*') && lastThree[2] == 'E') // Check if the last three elements are of the form E+E or E*E
            return 1;
        if (lastThree[0] == '(' && lastThree[1] == 'E' && lastThree[2] == ')') // Check if the last three elements are of the form (E)
            return 1;
    }
    return 0;
}

void reduce()
{
    int len = strlen(stack);
    if (len >= 1 && stack[len - 1] == 'i') // If the top element is 'i'
    {
        stack[len - 1] = 'E'; // Replace 'i' with 'E'
        printTableRow(stack, inputString, "Reduce i to E");
    }
    else if (len >= 3)
    {
        char lastThree[4];
        strncpy(lastThree, &stack[len - 3], 3); // Copy the last three elements to lastThree
        lastThree[3] = '\0';
        if (lastThree[0] == 'E' && (lastThree[1] == '+' || lastThree[1] == '*') && lastThree[2] == 'E') // If the last three elements are of the form E+E or E*E
        {
            stack[len - 3] = 'E'; // Replace E+E or E*E with E
            stack[len - 2] = '\0';
            printTableRow(stack, inputString, lastThree[1] == '+' ? "Reduce E+E to E" : "Reduce E*E to E"); // Print the action based on the operator
        }
        else if (lastThree[0] == '(' && lastThree[1] == 'E' && lastThree[2] == ')') // If the last three elements are of the form (E)
        {
            stack[len - 3] = 'E'; // Replace (E) with E
            stack[len - 2] = '\0';
            printTableRow(stack, inputString, "Reduce (E) to E");
        }
    }
}

int main()
{
    printf("Enter the Input String: ");
    scanf("%s", inputString);

    strcat(inputString, "$"); // Append $ to the end of the input string
    push('$');                // Push $ to the stack

    printf("%-10s %-10s %-10s\n", "Stack", "Input", "Action"); // Print Table Header
    printf("------------------------------\n");

    printTableRow(stack, inputString, "-"); // Initial State

    while (inputString[0] != '$')
    {
        char token = shift();
        push(token);
        char action[50];
        sprintf(action, "Shift '%c'", token);      // Create the action string with the token
        printTableRow(stack, inputString, action); // Print the table row

        while (checkReducibility()) // Check if the stack is reducible
        {
            reduce(); // Reduce the stack
        }
    }

    if (strcmp(stack, "$E") == 0 && strcmp(inputString, "$") == 0) // If the stack contains only $E and the input string contains only $
        printf("\n---Parsing Successfully Completed---\n");
    else
        printf("\n---Parsing Failed---\n");

    return 0;
}

// Enter the Input String: i+i*i
// Stack      Input      Action    
// ------------------------------
// $          i+i*i$     -         
// $i         +i*i$      Shift 'i' 
// $E         +i*i$      Reduce i to E
// $E+        i*i$       Shift '+' 
// $E+i       *i$        Shift 'i' 
// $E+E       *i$        Reduce i to E
// $E         *i$        Reduce E+E to E
// $E*        i$         Shift '*' 
// $E*i       $          Shift 'i' 
// $E*E       $          Reduce i to E
// $E         $          Reduce E*E to E

// ---Parsing Successfully Completed---