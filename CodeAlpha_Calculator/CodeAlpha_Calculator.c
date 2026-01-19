#include <stdio.h>

int main() {
    char operator;
    float num1, num2, result;

    printf("Simple Calculator\n");
    printf("Choose an operator (+, -, *, /): ");
    scanf(" %c", &operator);

    printf("Enter first number: ");
    scanf("%f", &num1);

    printf("Enter second number: ");
    scanf("%f", &num2);

    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("Result = %f", result);
            break;

        case '-':
            result = num1 - num2;
            printf("Result = %f", result);
            break;

        case '*':
            result = num1 * num2;
            printf("Result = %f", result);
            break;

        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("Result = %f", result);
            } else {
                printf("Error! Division by zero is not allowed.");
            }
            break;

        default:
            printf("Invalid operator!");
    }

    return 0;
}