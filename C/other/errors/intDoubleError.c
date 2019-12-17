#include <stdio.h>
int main()
{
   int a;
   double b;
   printf("Write int a = ");
   scanf("%i",a); /*something went wrong, I got another error?*/
   
   printf("Write double b = ");
   scanf("%lf",b);
   /*we will switch a and b in printf*/
   print("I'll print b = %f and a = %i",a,b);
}