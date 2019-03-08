#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
int main(){
	vector<vector <double> > a;
	int n; //размеры системы уравнений
	int i,j,e,l; //шаги
	double v1,v2; //сохраняем множители
	double xproverka; //проверка для последнего корня в полученной лестнице

	cin>>n;
	a.resize(n+1);
	for(i=0;i!=n+1;i++){
		a[i].resize(n);
	}
	//loading
	for(i=0;i!=n;i++){
        for(j=0;j!=n+1;j++){
            cin>>a[j][i];
        }
    }
	//расстановка уравнений
	for(i=0;i!=n-2;i++){
		if (a[i][i]*a[i+1][i+1] == a[i][i+1]*a[i+1][i]){ // смотрим появление нулей в диагонали, в случае 1 выполняем перестановку уравнений
			for(j=0;j!=n+1;j++){
				v1 = a[j][i];
				v2 = a[j][i+2];
				a[j][i] = v2;
				a[j][i+2] = v1;
			}
		}
	}
	cout<<endl;
	//reloaded
	for(i=0;i!=n;i++){
        for(j=0;j!=n+1;j++){
            cout<<a[j][i]<<" ";
        }
		cout<<endl;
    }
	//метод Гаусса
	//  for(j=0;j!=n;j++)  for(e=0;e!=n-1;e++) for(l=0;l!=n-2;l++) for(j=0;j!=n-1;j++)
	//for(j=0;j!=n-1;j++){
		for(l=0;l!=n-1;l++){
			for(e=l+1;e!=n;e++){
					v1 = a[l][l]; //сохраняем множитель l корня l строки
					v2 = a[l][e]; //сохраняем множитель l корня e=l+1 строки
					if((v1!=0) && (v2!=0)){
						for(i=0;i!=n+1;i++){ //домножаем на число
							a[i][l]=a[i][l]*v2;
							a[i][e]=a[i][e]*v1;
						}
						for(i=0;i!=n+1;i++){ //вычитаем строки
							a[i][e] -= a[i][l];
						}
					}
			}
		}
//	}

	/*
	xproverka = a[n][n-1]/a[n-1][n-1];
	cout<<xproverka<<" ";
	*/

	vector<double> x(n);
	for(l=n-1;l!=-1;l--){
		x[l]=a[n][l]/a[l][l]; //взяли корень внизу
		//начинаем вычитать строки вверху
		for(j=n-2;j!=-1;j--){
			a[n][j] -= a[l][j]*x[l];
		}
	}
	//выводим значения корней
	cout<<endl<<"korni systemi ";
	for(l=0;l!=n;l++){
		cout<<x[l]<<" ";
	}
	system("PAUSE");
}