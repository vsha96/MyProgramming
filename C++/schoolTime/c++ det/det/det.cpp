#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector<vector <double>> minor(vector<vector <double>> &c, int N, int i){
	 vector<vector <double>> y;
	 int j,e;
	 y.resize(N-1);
	 for(e=0;e!=N-1;e++){
	 	y[e].resize(N-1);
	 }
	 
	 for(e=1;e!=N;e++){
			 for(j=0;j!=i;j++){
				 y[e-1][j] = c[e][j];
			 }
			 for(j=i+1;j!=N;j++){
				 y[e-1][j-1] = c[e][j];
			 }
	 }
		
	 return y;
}

double det(vector<vector <double>> &b,int N){
	int i;
	if(N == 1){
		return b[0][0];
	}
	if(N == 2){
		return b[0][0]*b[1][1]-b[0][1]*b[1][0];
	}
	if(N > 2){
		double y = 0;
		for(i=0;i!=N;i++){
			y += pow(-1.0,i)*b[0][i]*det(minor(b,N,i) , N-1);
		}
		return y;
	}
	else {
		cout<<"H";
	}
}


int main(){
	int n; //размер матрицы
	int i,j;
	vector<vector <double>> a; //матрица
	vector<vector <double>> temp;//временный массив
	double s = 0; //answer

	cin>>n;
	a.resize(n);
	for(i=0;i!=n;i++){
		a[i].resize(n);
	}
	//loading
	for(i=0;i!=n;i++){
        for(j=0;j!=n;j++){
            cin>>a[i][j];
        }
	}

	cout<<det(a,n)<<endl;
	system("PAUSE");
}