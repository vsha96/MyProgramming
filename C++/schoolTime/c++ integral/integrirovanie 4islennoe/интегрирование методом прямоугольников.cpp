/*
#include <iostream>
#include <cmath>


using namespace std;

double F(double x) {
	return sin(x)*sin(2*x)*sin(3*x); //первоначальная функция
}
//1  sin(x/2)
//2  pow(2*x-1,6)
//3  exp(2*x)
//4  sqrt(x*2)+pow(x,1/3)
//5  sin(x)*sin(2*x)*sin(3*x)

int main(){
	double a,b; // границы определенного интеграла
	double h,xi,e;
	double s=0; // интеграл
	int i; //шаги
	double n; //колво разбиений

	cin>>a>>b;//вводим концы отрезка
	cin>>n;//вводим колво разбиений

	h=(b-a)/n;
	xi=a;
	for(i=0;i!=n;i++){
		s += F(xi)*h;
		xi += h;
	}
	cout<<"integral = "<<s<<" ";
	system("pause");
}
*/