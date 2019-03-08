#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int main(){
	int n,i,j;
	double min,c;
	vector<double>  a(1);
	vector<double>  b(1);
	cout<<" vvedite kol-vo ";
	cin>>n;
	a.resize(n);
	b.resize(n);
	cout<<" vvedite tochki "<<endl;
	for(i=0;i!=n;i++){
		cin>>a[i];
		b[i]=a[i];
	}
	//sortirovka massiva
	for(i=0;i!=n;i++){
		min=b[i];
		c=min;
		for(j=i+1;j!=n;j++){
			if(min>b[j]){ min = b[j]; b[j] = c;}
		}
		b[i]=min;
	}
	//----
	
	for(i=0;i!=n;i++){cout <<b[i]<< " ";}

	system("PAUSE");
	return 0;
}