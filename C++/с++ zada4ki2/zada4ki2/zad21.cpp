
#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> a;
int main() {
	int w,h;
	int n;
	int i,j,s; //steps
	int S=0; //square
	cin>>w>>h;
	cin>>n;
	for(i=0;i!=w;i++){
		vector<int> v;
		for(j=0;j!=h;j++){
			v.push_back(0);
		}
		a.push_back(v);
	}

	int a1,a2,b1,b2;
	for(i=0;i!=n;i++){
		cin>>a1>>a2>>b1>>b2;
		for(j=a1;j<b1;j++){
			for(s=a2;s<b2;s++){
				a[j][s] += 1;
			}
		}
	}

	for(i=0;i!=w;i++){
		for(j=0;j!=h;j++){
			if(a[i][j]==0){S++;}
		}
	}
	cout<<endl<<"square = "<<S<<" ";
	system("PAUSE");
	return 0;
}