#include <iostream>
#include <math.h>

using namespace std;
double F(double x){
	return x*x*x+4*x-3;
}

double f(double x){
	return 3*x*x+4;
}

int main(){
	double x1,x2,e,xk;
	cin>> x1;
	cin>> x2;
	cin>> e;
	if (F(x1)==0){cout<<"koren = "<< x1; system("PAUSE"); return 0;}
	if (F(x2)==0){cout<<"koren = "<< x2; system("PAUSE"); return 0;}
	xk = x1 - F(x1)/f(x1);

	while(F(xk-e)*F(xk+e)>0){
		xk = x1 - F(x1)/f(x1);
		x1 += e;
	}
	cout<<"koren = "<<xk<<" ";

	system("PAUSE");
}