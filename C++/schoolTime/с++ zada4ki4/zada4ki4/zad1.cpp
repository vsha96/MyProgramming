/*
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
int main(){
	vector<vector <int> > f;
	int n,m; //размеры массива	
	int i,j; //шаги
	cin>>n>>m;
	f.resize(n);
	for(i=0;i!=n;i++){
		f[i].resize(m);
	}
	//loading
	for(i=0;i!=m;i++){
        for(j=0;j!=n;j++){
            cin>>f[j][i];
        }
    }
	//смотрим матрицу на симпатичность
	for(j=0;j!=m-1;j++){
        for(i=0;i!=n-1;i++){
			if(f[i][j]==f[i+1][j]){if(f[i][j]==f[i+1][j+1]){if(f[i][j]==f[i][j+1]){cout<<"NO"; system("PAUSE"); return 0;}}};
		}
	}
	cout<<"YES"<<endl; 
	system("PAUSE");
}
*/