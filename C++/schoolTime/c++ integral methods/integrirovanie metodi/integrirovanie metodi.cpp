/* #include <iostream>
#include <vector>
#include <cmath>

double F(double xf){
	return sqrt(abs(-pow(xf-2,2)+9));
}

using namespace std;
int main(){
	double a,b; // границы определенного интеграла
	double h,xi,e,x;
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
	cout<<"pryamoug = "<<s<<" ";
	s = 0;
	h=(b-a)/n;
	xi=a;
	for(i=0;i!=n;i++){
		s += (F(xi)+F(xi+h))/2*h;
		xi += h;
	}
	cout<<"trapecii = "<<s<<" ";
	s = 0;

	h = (b - a)/n/2;
	for(x = a;x < b;x += 2*h){
		s += h/3*(F(x)+F(x + 2*h)+4*F(x + h));
		
	}
	cout<<"metod simpsona = "<<s;
	system("PAUSE");

} */