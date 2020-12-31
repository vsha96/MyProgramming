#include <iostream>
#include <math.h>
#include <ctime>

using namespace std;

int main()
{
	// размеры матрицы
	int n_rows = 5;
    int n_cols = 10;

    // инициализируем матрицу
    srand(time(NULL)); 
	double **matrix = new double* [n_rows];
	for (int i = 0; i < n_rows; i++) {
		matrix[i] = new double [n_cols];
	}

	// выводим ее
	for (int i = 0; i < n_rows; i++) {
		for (int j = 0; j < n_cols; j++) {
			matrix[i][j] = (double)(rand())/RAND_MAX * 10;
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	// очистка матрицы
	for (int i = 0; i < n_rows; i++) {
		delete[] matrix[i];
	}
	delete [] matrix;
	
	return 0;
}