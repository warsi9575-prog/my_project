#include <stdio.h>

int main() {
    int num = 10;
    int *ptr = &num;           // pointer to int
    int **pptr = &ptr;         // pointer to pointer (double pointer)
    
    printf("=== Pointer to Pointer (Double Pointer) Demo ===\n\n");
    
    printf("Value of num: %d\n", num);
    printf("Address of num: %p\n", &num);
    printf("Address of ptr: %p\n", &ptr);
    printf("Address of pptr: %p\n\n", &pptr);
    
    printf("ptr (stores address of num): %p\n", ptr);
    printf("*ptr (value at address): %d\n", *ptr);
    printf("pptr (stores address of ptr): %p\n", pptr);
    printf("*pptr (value at that address): %p\n", *pptr);
    printf("**pptr (value at the value): %d\n\n", **pptr);
    
    // Modifying through pptr
    printf("=== Modifying Value Through Pointer to Pointer ===\n");
    **pptr = 20;
    printf("After **pptr = 20:\n");
    printf("num = %d\n", num);
    printf("*ptr = %d\n", *ptr);
    printf("**pptr = %d\n\n", **pptr);
    
    // Example with arrays
    printf("=== Using Pointer to Pointer with Arrays ===\n");
    int arr[3] = {5, 15, 25};
    int *p = arr;
    int **pp = &p;
    
    printf("Array elements using **pp:\n");
    for(int i = 0; i < 3; i++) {
        printf("arr[%d] = %d (via **pp = %d)\n", i, arr[i], **pp);
        (*pp)++;  // increment pointer
    }
    
    return 0;
}
