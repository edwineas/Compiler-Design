#include <stdio.h>

char input[100];
int i;

int E();
int EP();
int T();
int TP();
int F();

void main(){
    printf("Enter the string: ");
    scanf("%s",input);
    if (E()){
        if (input[i+1] == '\0'){
            printf("The string is accepted\n");
        }
        else{
            printf("The string is not accepted\n");
        }
    }
    else{
        printf("The string is not accepted\n");
    }
}

int E(){
    if(T()){
        if(EP()){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

int EP(){
    if(input[i]=='+'){
        i++;
        if(T()){
            if(EP()){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    else{
        return 1;
    }
}

int T() {
    if(F()){
        if (TP()){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return  0;
    }
}

int TP() {
    if(input[i] == '*'){
        i++;
        if(F()){
            if(TP()){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    else{
        return 1;
    }
}

int F(){
    if (input[i] == '('){
        i++;
        if (E()){
            if (input[i] == ')'){
                return 1;
            }
            else 
                return 0;
        }
    }
    else if (input[i] >='a' && input[i]<='z'){
        i++;
        return 1;
    }
    else{
        return 0;
    }
}