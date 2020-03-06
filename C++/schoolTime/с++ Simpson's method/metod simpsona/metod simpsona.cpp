#include <iostream>
#include <vector>
#include <cmath>

double F(double xf){
	return sqrt(abs((xf+1)*(5-xf)));
}

using namespace std;
int main(){
	double a,b;
	int i, j;
	double y1,y2,y3;
	double x,h;
	double n;
	double s = 0;

	cin>>a>>b;
	cin>>n;

	h = (b - a)/n/2;

	for(x = a;x < b;x += 2*h){
		s += h/3*(F(x)+F(x + 2*h)+4*F(x + h));
		
	}
	cout<<s;
	system("PAUSE");
}