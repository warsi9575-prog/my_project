# include<stdio.h>

int calcmarks(int maths, int science, int sunskrit);

int main() {
    int science = 95;
    int maths = 92;
    int sunskrit = 91;
    printf("percentage is: %d ",calcmarks(maths, science, sunskrit));
    return 0;
}

int calcmarks(int maths, int science, int sunskrit) {
 return ((maths + science + sunskrit )/3);
}


/*

# include<stdio.h>

int calcmarks();

int main() {
     printf("percentage is: %d ", calcmarks());
     return 0;
}

int calcmarks() {
    int science = 98;
    int maths = 95;
    int sunskrit = 99;
    int percentage = ((maths + science + sunskrit )/3);
  return percentage;
}

*/