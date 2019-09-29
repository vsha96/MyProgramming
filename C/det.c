#include <stdio.h>
#include <math.h>

double det(double a, double b, double c)
{
   return b*b-4*a*c;
}
int main()
{
   double p,q,r,d;
   if (3 != scanf("%lf %lf %lf",&p,&q,&r)) {
	printf("data format error\n");
	return 1;
   }
   if (p == 0) {
	return 2;
   }
   d = det(p,q,r);
   if (d < 0) {
	printf("no roots\n");
	return 0;
   }
   d = sqrt(d);
   printf("%f %f\n",(-q-d)/(2*p),(-q+d)/(2*p));
   return 0;
}