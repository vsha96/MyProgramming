#include <iostream>
#include <cmath>

using namespace std;
//данная программа ищет экстремумы функции и определяет с установленной погрешностью
//а также их тип - максимум или минимум 
double F(double x) {
	return x*x; //первоначальная функция, не используется
}
double f(double x) {
	return 2*x; //производная функции
}

int main(){
	double a,b,h,xi,e;
	double n; //количество интервало на которые делится отрезок с экстремумами
	cout<<" vvedite a "<<endl; //начало отрезка
	cin>>a;
	cout<<" vvedite b "<<endl; //конец отрезка
	cin>>b;
	cout<<" vvedite e "<<endl; //погрешность
	cin>>e;
	cout<<" vvedite n "<<endl; //колво интервалов на которые делится отрезок
	cin>>n;
	xi=a; //положение нашей точки проверки экстремума на отрезке (идем по отрезку и смотрим экстремум)
	if (f(a)==0){ cout<<"extremum v to4ke A = "<<a; system("PAUSE"); return 0;}
	if (f(b)==0){ cout<<"extremum v to4ke A = "<<b; system("PAUSE"); return 0;}
	// ^ проверка производной в начале функции (не определяется тип экстремума)
	if (f(xi)<0){
	while (abs(f(xi))>=e){ 
		h=(b-a)/n; 
		while(f(xi)<0){ 
			xi += h;
		} 
		a = xi - h; // сокращаем отрезок на котором ходим
		xi -= h;
	}
	cout <<"minimum f(x) v to4ke A = "<<xi<<" ";
	}
	if(f(xi)>0){
	while (abs(f(xi))>=e){ 
		h=(b-a)/n; 
		while(f(xi)>0){ 
			xi += h;
		} 
		a = xi - h;
		xi -= h;
	}
	cout <<"maximum f(x) v to4ke A = "<<xi<<" ";
	}
	
	system("PAUSE");
	return 0;

}