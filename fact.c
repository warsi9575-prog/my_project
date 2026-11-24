#include <stdio.h>

 int fact(int n);

int main() {
 int n=5;
    printf("factorial  of %d is %d", n, fact(n));

    return 0;
}

int fact(int n) {
    if(n == 0) {
      return 1;
    }

   int factNM1 = fact (n-1)*n;
   //just trying a simple logic
    //int factN = factNM1 *n;
    //return factN;
      return factNM1;
}