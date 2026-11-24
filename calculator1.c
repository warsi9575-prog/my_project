// calculator by ikram warsi - improved version
// Uses floating point for precise division, loop for multiple calculations

#include <stdio.h>
#include <math.h>

int main()
{
    double num1, num2, result;
    char operator;
    char continueCalc;
    
    printf("========== CALCULATOR (IMPROVED) ==========\n");
    printf("Supported operations: + - * / %% (modulo) ^ (power)\n\n");
    
    do {
        // Input with validation
        printf("Enter first number: ");
        if (scanf("%lf", &num1) != 1) {
            printf("Error: Invalid number input!\n");
            while (getchar() != '\n');  // Clear input buffer
            continue;
        }
        
        printf("Enter operator (+, -, *, /, %%, ^): ");
        scanf(" %c", &operator);
        
        printf("Enter second number: ");
        if (scanf("%lf", &num2) != 1) {
            printf("Error: Invalid number input!\n");
            while (getchar() != '\n');  // Clear input buffer
            continue;
        }
        
        // Perform calculation
        switch (operator)
        {
            case '+':
                result = num1 + num2;
                printf("\nResult: %.2f + %.2f = %.2f\n\n", num1, num2, result);
                break;
            case '-':
                result = num1 - num2;
                printf("\nResult: %.2f - %.2f = %.2f\n\n", num1, num2, result);
                break;
            case '*':
                result = num1 * num2;
                printf("\nResult: %.2f * %.2f = %.2f\n\n", num1, num2, result);
                break;
            case '/':
                if (num2 != 0) {
                    result = num1 / num2;
                    printf("\nResult: %.2f / %.2f = %.2f\n\n", num1, num2, result);
                } else {
                    printf("\nError: Division by zero not allowed!\n\n");
                }
                break;
            case '%':
                if ((int)num2 != 0) {
                    result = (int)num1 % (int)num2;
                    printf("\nResult: %d %% %d = %.0f\n\n", (int)num1, (int)num2, result);
                } else {
                    printf("\nError: Modulo by zero not allowed!\n\n");
                }
                break;
            case '^':
                result = pow(num1, num2);
                printf("\nResult: %.2f ^ %.2f = %.2f\n\n", num1, num2, result);
                break;
            default:
                printf("\nError: Invalid operator!\n\n");
        }
        
        // Ask to continue
        printf("Do you want to perform another calculation? (y/n): ");
        scanf(" %c", &continueCalc);
        printf("\n");
        
    } while (continueCalc == 'y' || continueCalc == 'Y');
    
    printf("Thank you for using the calculator!\n");
    return 0;
}