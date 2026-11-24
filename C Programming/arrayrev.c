#include<stdio.h>
void rev(int*,int);
void printarray(int*,int);
int main(){
    int a[]={1,2,3,4,5};
    int length=sizeof(a)/sizeof(a[0]);
    printarray(a,length);
    rev(a,length);
    printarray(a,length);   
    return 0;
}
void rev(int* arr,int len){
        int i,j,temp;
        for(i=0,j=len-1;i<j;i++,j--){
            temp=arr[j];
            arr[j]=arr[i];
            arr[i]=temp;

        }
}
void printarray(int* arr,int len){
    int i;
    for(i=0;i<len;i++){
        printf("%d\t",arr[i]);
    }
    printf("\n");
}