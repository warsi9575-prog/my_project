#include<stdio.h>
 void finalprice (float price) ;
int main () {
    float price;
//float price = 100.00;
printf("enter the price  :  ");
scanf("%f", &price);
      printf("price is %f\n",price);
    finalprice(price);
    return 0;
}

void finalprice(float price) {
    float value = price + (0.18 * price);
    printf("Final price is %f\n", value);
}
