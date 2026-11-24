#include<Stdio.h>

int main() {
    int i=5;
    int *ptr = &i;
    int **pptr = *ptr;
    printf("%u",pptr);


}