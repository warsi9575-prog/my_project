#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Discards leftover characters up to and including the next newline (or EOF). */
static void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}

int main(void) {
    while (1) {
        int a, b, result;
        char op;

        printf("Enter expression (e.g. 10 + 5), or 'q' to quit: ");
        int n = scanf(" %d %c %d", &a, &op, &b);

        if (n == EOF) {
            printf("Input closed. Exiting.\n");
            break;
        }

        if (n != 3) {
            printf("Error: Invalid input format. Try again.\n");
            flush_input();
            continue;
        }
        flush_input(); /* discard anything left on the line (e.g. trailing junk) */

        int ok = 1; /* becomes 0 if we hit an error */

        switch (op) {
            case '+':
                if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
                    printf("Error: Overflow.\n");
                    ok = 0;
                    break;
                }
                result = a + b;
                break;

            case '-':
                if ((b < 0 && a > INT_MAX + b) || (b > 0 && a < INT_MIN + b)) {
                    printf("Error: Overflow.\n");
                    ok = 0;
                    break;
                }
                result = a - b;
                break;

            case '*':
                result = a * b;
                if (a != 0 && result / a != b) {
                    printf("Error: Overflow.\n");
                    ok = 0;
                }
                break;

            case '/':
                if (b == 0) {
                    printf("Error: Division by zero.\n");
                    ok = 0;
                    break;
                }
                if (a == INT_MIN && b == -1) {
                    printf("Error: Overflow.\n");
                    ok = 0;
                    break;
                }
                result = a / b;
                break;

            case '%':
                if (b == 0) {
                    printf("Error: Modulus by zero.\n");
                    ok = 0;
                    break;
                }
                if (a == INT_MIN && b == -1) {
                    printf("Error: Overflow.\n");
                    ok = 0;
                    break;
                }
                result = a % b;
                break;

            default:
                printf("Error: Invalid operator '%c'.\n", op);
                ok = 0;
                break;
        }

        if (ok) {
            printf("Result = %d\n", result);
        }
        /* Loop back regardless of success/failure -- user can quit with Ctrl+Z (Windows) or Ctrl+D (Linux/Mac) */
    }

    return EXIT_SUCCESS;
}