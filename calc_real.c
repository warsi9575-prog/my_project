#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define HISTORY_MAX 50

static double history[HISTORY_MAX];
static int history_count = 0;
static double memory_value = 0.0;
static int memory_set = 0;

static void print_help(void) {
    printf("\n----------------------------------------\n");
    printf(" Commands:\n");
    printf("   <op> <number>   e.g.  + 5   or   * 2.5\n");
    printf("   =                show current result again\n");
    printf("   c                clear result back to 0\n");
    printf("   m+               add current result to memory\n");
    printf("   m-               subtract current result from memory\n");
    printf("   mr               recall memory into current result\n");
    printf("   mc               clear memory\n");
    printf("   h                show calculation history\n");
    printf("   ?                show this help\n");
    printf("   q                quit\n");
    printf(" Operators: + - * / %% (%% = modulus, truncates decimals)\n");
    printf("----------------------------------------\n\n");
}

static void add_history(double value) {
    if (history_count < HISTORY_MAX) {
        history[history_count++] = value;
    } else {
        /* shift left, drop oldest */
        memmove(history, history + 1, sizeof(double) * (HISTORY_MAX - 1));
        history[HISTORY_MAX - 1] = value;
    }
}

static void print_history(void) {
    if (history_count == 0) {
        printf("(no history yet)\n");
        return;
    }
    printf("--- History ---\n");
    for (int i = 0; i < history_count; i++) {
        printf("  %2d: %g\n", i + 1, history[i]);
    }
    printf("---------------\n");
}

int main(void) {
    double result = 0.0;
    char line[256];

    printf("=== Console Calculator ===\n");
    printf("Type ? for help.\n\n");

    while (1) {
        printf("[%g] > ", result);

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\nInput closed. Exiting.\n");
            break;
        }

        /* Strip trailing newline */
        line[strcspn(line, "\n")] = '\0';

        /* Skip blank lines */
        if (line[0] == '\0') {
            continue;
        }

        /* Single-letter commands */
        if (strcmp(line, "q") == 0) {
            printf("Goodbye.\n");
            break;
        } else if (strcmp(line, "?") == 0) {
            print_help();
            continue;
        } else if (strcmp(line, "c") == 0) {
            result = 0.0;
            printf("Result cleared.\n");
            continue;
        } else if (strcmp(line, "=") == 0) {
            printf("Result = %g\n", result);
            continue;
        } else if (strcmp(line, "h") == 0) {
            print_history();
            continue;
        } else if (strcmp(line, "m+") == 0) {
            memory_value += result;
            memory_set = 1;
            printf("Added %g to memory (memory = %g).\n", result, memory_value);
            continue;
        } else if (strcmp(line, "m-") == 0) {
            memory_value -= result;
            memory_set = 1;
            printf("Subtracted %g from memory (memory = %g).\n", result, memory_value);
            continue;
        } else if (strcmp(line, "mr") == 0) {
            if (!memory_set) {
                printf("Memory is empty.\n");
            } else {
                result = memory_value;
                printf("Recalled memory: %g\n", result);
            }
            continue;
        } else if (strcmp(line, "mc") == 0) {
            memory_value = 0.0;
            memory_set = 0;
            printf("Memory cleared.\n");
            continue;
        }

        /* Otherwise expect: <operator> <number> */
        char op;
        double operand;
        int matched = sscanf(line, " %c %lf", &op, &operand);

        if (matched != 2) {
            printf("Error: Couldn't understand '%s'. Type ? for help.\n", line);
            continue;
        }

        double new_result = result;
        int ok = 1;

        switch (op) {
            case '+':
                new_result = result + operand;
                break;

            case '-':
                new_result = result - operand;
                break;

            case '*':
                new_result = result * operand;
                break;

            case '/':
                if (operand == 0.0) {
                    printf("Error: Division by zero.\n");
                    ok = 0;
                } else {
                    new_result = result / operand;
                }
                break;

            case '%':
                if (operand == 0.0) {
                    printf("Error: Modulus by zero.\n");
                    ok = 0;
                } else {
                    new_result = fmod(result, operand);
                }
                break;

            default:
                printf("Error: Unknown operator '%c'. Type ? for help.\n", op);
                ok = 0;
                break;
        }

        if (!ok) {
            continue;
        }

        /* Guard against NaN/Inf creeping in from edge-case math */
        if (isnan(new_result) || isinf(new_result)) {
            printf("Error: Result is not a valid number (overflow or invalid operation).\n");
            continue;
        }

        result = new_result;
        add_history(result);
        printf("Result = %g\n", result);
    }

    return EXIT_SUCCESS;
}