#include <iostream>
#include <math.h>
using namespace std;
double F(double x){
	double y = x+1;
	return y;
}

int main(){
	double a,b,c;
	double e,f1,f2,fc;
	cin>>a>>b;
	cin>>e;
	while(abs(a-b)>=e){
		c=(a+b)/2;
		f1=F(a);
		f2=F(b);
		fc=F(c);

		if(f1==0){
		cout<<"koren = "<<a<<endl;
		system("PAUSE");
		return 0;
		}
		if(f2==0){
		cout<<"koren = "<<b<<endl;
		system("PAUSE");
		return 0;
		}


		if(f1*fc<=0){
			a=c;
			//cout<<"a = "<<a<<endl;
		}
		if(f2*fc<=0){
			a=b;
			b=c;
			//cout<<"b = "<<b<<endl;
		}
		if(f1*f2>0){
			cout<<"kornya net "<<endl;
			system("PAUSE");
			return 0;
		}
	}
	cout<<"koren = " <<c;
	system("PAUSE");
}