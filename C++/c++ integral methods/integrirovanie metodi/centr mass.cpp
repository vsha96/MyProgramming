#include <iostream>
#include <cmath>

double f(double xf){
	//return 9-xf*xf;
	//return sin(xf);
	return pow(2,xf*xf)*sin(xf)/xf;
}
double F(double xf){
	//return (9-xf*xf)*xf;
	//return sin(xf)*xf;
	return pow(2,xf*xf)*sin(xf);
}
double Fi(double xf){
	//return (9-xf*xf)*(9-xf*xf);
	//return sin(xf)*sin(xf);
	return pow(2,xf*xf)*sin(xf)*pow(2,xf*xf)*sin(xf)/xf/xf;
}

using namespace std;
int main(){
	double a,b; // границы определенного интеграла
	double h,xi,e,x,y;
	double s=0; // ploshad'
	int i; //шаги
	double n; //колво разбиений
	double xc=0,yc=0; //cent mass

	cin>>a>>b;//вводим концы отрезка
	cin>>n;//вводим колво разбиений

	h = (b - a)/n/2;
	for(x = a;x < b;x += 2*h){
		//if(x!=0){
		s += h/3*(f(x)+f(x + 2*h)+4*f(x + h));
		//}
	}
	for(x = a;x < b;x += 2*h){
		xc += (h/3*(F(x)+F(x + 2*h)+4*F(x + h)))/s;
	}
	
	for(x = a;x < b;x += 2*h){
		yc += (h/3*(Fi(x)+Fi(x + 2*h)+4*Fi(x + h)))/2/s;
	}
	
	cout<<"ploshad = "<<s<<endl;
	cout<<xc<<" ; "<<yc<<endl;
	system("PAUSE");
}