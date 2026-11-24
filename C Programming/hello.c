#include <stdio.h>

 void printhello(int count, int n);

int main() {
 
    printhello(1, 5);

    return 0;
}

void printhello(int count, int n) {
    if(count>n) {
      return;
    }
printf(":hello\n");
printhello(count+1, 5);
}
