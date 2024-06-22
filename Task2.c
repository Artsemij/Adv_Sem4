/*
Написать алгоритм перевода из инфиксной записи в обратную польскую. Для его реализации нужны данные по приоритетам операций. 
Реализовать алгоритм, используя побитовые операции (&, |, ^).

Пример №1
Данные на вход: ( 3 & 5 ) ^ 4 | 9
Данные на выход: 3 5 & 4 ^ 9 |
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

int precedence(char op) {
    switch (op) {
        case '&':
            return 1;
        case '|':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}

void reverse(char *str) {
    int start = 0;
    int end = strlen(str) - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}

int is_operator(char c) {
    return (c == '&' || c == '|' || c == '^');
}

void infix_to_postfix(const char *infix, char *postfix) {
    int top = -1;
    char stack[MAX_SIZE];

    while (*infix != '\0') {
        if (*infix >= '0' && *infix <= '9') {
            // Append digit to the postfix string
            strncat(postfix, infix, 1);
        } else if (is_operator(*infix)) {
            // Check if the stack is empty or not
            while (top >= 0 && precedence(stack[top]) >= precedence(*infix)) {
                postfix[strlen(postfix)] = stack[top];
                top--;
            }

            // Push the current operator to the stack
            stack[++top] = *infix;
        } else if (*infix == '(') {
            // Push the left parenthesis to the stack
            stack[++top] = *infix;
        } else if (*infix == ')') {
            // Pop and append the operators from the stack until left parenthesis is found
            while (top >= 0 && stack[top] != '(') {
                postfix[strlen(postfix)] = stack[top];
                top--;
            }

            // Discard the left parenthesis
            top--;
        }

        infix++;
    }

    // Append remaining operators from the stack to the postfix string
    while (top >= 0) {
        postfix[strlen(postfix)] = stack[top];
        top--;
    }

    reverse(postfix);
}

int main() {
    const char infix_expr[] = "( 3 & 5 ) ^ 4 | 9";
    char postfix_expr[MAX_SIZE];

    infix_to_postfix(infix_expr, postfix_expr);

    printf("Postfix expression: %s\n", postfix_expr);

    return 0;
}