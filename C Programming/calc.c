#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/* Checks a+b for overflow. Returns 1 if overflow, 0 if ok (and writes result). */
static int safe_add(int a, int b, int *result) {
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) return 1;
    *result = a + b;
    return 0;
}

static int safe_sub(int a, int b, int *result) {
    if ((b < 0 && a > INT_MAX + b) || (b > 0 && a < INT_MIN + b)) return 1;
    *result = a - b;
    return 0;
}

static int safe_mul(int a, int b, int *result) {
    if (a != 0 && b != 0) {
        if (a == -1 && b == INT_MIN) return 1;
        if (b == -1 && a == INT_MIN) return 1;
        int r = a * b;
        if (r / a != b) return 1;
        *result = r;
        return 0;
    }
    *result = 0;
    return 0;
}

int main(void) {
    char line[1024];

    printf("Enter expression (e.g. 10 + 5 * 2 - 3): ");
    if (!fgets(line, sizeof(line), stdin)) {
        printf("Error: No input received.\n");
        return EXIT_FAILURE;
    }

    /* Make sure the line wasn't truncated (no newline found = too long) */
    if (strchr(line, '\n') == NULL && strlen(line) == sizeof(line) - 1) {
        printf("Error: Expression too long.\n");
        return EXIT_FAILURE;
    }

    int pos = 0;
    long total;
    int consumed;

    /* Read the first number */
    if (sscanf(line + pos, "%ld%n", &total, &consumed) != 1) {
        printf("Error: Expression must start with a number.\n");
        return EXIT_FAILURE;
    }
    pos += consumed;

    if (total > INT_MAX || total < INT_MIN) {
        printf("Error: Number out of range.\n");
        return EXIT_FAILURE;
    }

    int accumulator = (int)total;
    int term_count = 1;

    /* Loop: read an operator + number pair at a time until the line runs out */
    while (1) {
        char op;
        int matched = sscanf(line + pos, " %c%n", &op, &consumed);

        if (matched != 1) {
            break; /* nothing left but whitespace/newline -> done */
        }
        pos += consumed;

        long next;
        if (sscanf(line + pos, "%ld%n", &next, &consumed) != 1) {
            printf("Error: Expected a number after operator '%c'.\n", op);
            return EXIT_FAILURE;
        }
        pos += consumed;

        if (next > INT_MAX || next < INT_MIN) {
            printf("Error: Number out of range.\n");
            return EXIT_FAILURE;
        }
        int b = (int)next;
        int result;

        switch (op) {
            case '+':
                if (safe_add(accumulator, b, &result)) {
                    printf("Error: Overflow.\n");
                    return EXIT_FAILURE;
                }
                break;

            case '-':
                if (safe_sub(accumulator, b, &result)) {
                    printf("Error: Overflow.\n");
                    return EXIT_FAILURE;
                }
                break;

            case '*':
                if (safe_mul(accumulator, b, &result)) {
                    printf("Error: Overflow.\n");
                    return EXIT_FAILURE;
                }
                break;

            case '/':
                if (b == 0) {
                    printf("Error: Division by zero.\n");
                    return EXIT_FAILURE;
                }
                if (accumulator == INT_MIN && b == -1) {
                    printf("Error: Overflow.\n");
                    return EXIT_FAILURE;
                }
                result = accumulator / b;
                break;

            case '%':
                if (b == 0) {
                    printf("Error: Modulus by zero.\n");
                    return EXIT_FAILURE;
                }
                if (accumulator == INT_MIN && b == -1) {
                    printf("Error: Overflow.\n");
                    return EXIT_FAILURE;
                }
                result = accumulator % b;
                break;

            default:
                printf("Error: Invalid operator '%c'.\n", op);
                return EXIT_FAILURE;
        }

        accumulator = result;
        term_count++;
    }

    if (term_count < 2) {
        printf("Error: Need at least one operator and number (e.g. 10 + 5).\n");
        return EXIT_FAILURE;
    }

    printf("Result = %d\n", accumulator);
    return EXIT_SUCCESS;
}