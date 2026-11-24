#include <stdio.h>

float square(float side);
float rectangle(float A, float B);
float circle(float radius);

int main() {
    float A = 5.67;
    float B = 3.45;

    printf("area is %.2f\n", rectangle(A, B));

    return 0;
}


float square(float side) {
    return side * side;
}

float rectangle(float A, float B) {
    return A * B;
}

float circle(float radius) {
    return 3.14 * radius * radius;
}
