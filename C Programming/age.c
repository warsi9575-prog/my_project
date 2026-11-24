#include<stdio.h>
int main () {
    int age;
    printf("enter the age : ");
    scanf ("%d",&age);
    if (age >= 18 ) {
        printf ("adult \n");
        printf("they can drive \n");
    } else if (age >12 && age < 20) {
            printf("teenager");
        } else {
        printf ("child \n");
        printf ("they can not drive");
    }
    return 0;
    
}