#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<vector<int> > a;
int main() {
	int i,j;
	int n,m;
	int Wall=0;
	double l=0.8,w=0.2,h=3;
	cin>>n>>m;

	a.resize(n);
	for(i=0;i!=n;i++){
		a[i].resize(m);
	}
	//заполнение комнат
	for(i=0;i!=m;i++){
		for(j=0;j!=n;j++){
			cin>>a[j][i];
		}
	}
	//счет стен
	for(i=0;i!=m;i++){
		for(j=0;j!=n-1;j++){
			if(a[j][i]!=a[j+1][i]) Wall++;
		}
	}
	for(i=0;i!=m-1;i++){
		for(j=0;j!=n;j++){
			if(a[j][i]!=a[j][i+1]) Wall++;
		}
	}
	//cout<<Wall<<" ";
	/*
	for(i=0;i!=m;i++){
		for(j=0;j!=n;j++){
			cout<<" "<<a[j][i]<<" ";
		}
		cout<<" "<<endl;
	}
	*/
	//—„≈“ —“џ ќ¬
	vector<vector<int> > cross;
	int crossCount=0;//колво стыков
	//задаем размер массиву стыков, с учетом того, что их n-1 * m-1
	cross.resize(n-1);
	for(i=0;i!=n-1;i++){
		cross[i].resize(m-1);
	}
	//занул€ем массив
	for(i=0;i!=n-1;i++){
		for(j=0;j!=m-1;j++){
			cross[i][j] = 0;
		}
	}
	//теперь ходим по данной нам комнате и смотрим стыки
	for(j=1;j!=m;j++){
		for(i=1;i!=n;i++){
			if(a[i][j]!=a[i-1][j-1]) cross[i-1][j-1]=1;
			//if(a[i][j]!=a[i+1][j-1]) cross[i][j-1]=1;
			//if(a[i][j]!=a[i-1][j+1]) cross[i-1][j]=1;
			//if(a[i][j]!=a[i+1][j+1]) cross[i][j]=1;
		}
	}
	for(j=1;j!=m;j++){
		for(i=0;i!=n-1;i++){
			if(a[i][j]!=a[i+1][j-1]) cross[i][j-1]=1;
		}
	}

	//фуууух, считаем полученные стыки, они у нас в массиве равны 1
	double V=0; //объем стен
	for(i=0;i!=n-1;i++){
		for(j=0;j!=m-1;j++){
			if(cross[i][j]==1) crossCount++;
		}
	}
	V += Wall*w*l*h + crossCount*w*w*h;

	//√ƒ≈ “ќ ѕќ“≈–яЋ—я —“џ !!!!! ответ 4.44 выдает!!! ѕрав ответ 4.56 ”јјјјјјјјјјјјјјјјјјјјјј
	cout<<" объем стен V = "<<V;

	system("PAUSE");
}