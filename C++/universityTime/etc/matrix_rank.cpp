#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <time.h> 

using namespace std;

// размер матрицы
#define MATRIX_SIZE 1000
#define N_ROWS MATRIX_SIZE
#define N_COLS MATRIX_SIZE
// точность вычислений
#define EPS 0.01

void matrix_print(vector < vector<double> > matrix)
{
    int n_rows = matrix.size();
    int n_cols = matrix[0].size();
    for (int i = 0; i < n_rows; i++) {
		for (int j = 0; j < n_cols; j++) {
			cout << setprecision(5) << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

// индекс строки с максимальным значением в столбце
// если захотим модифицировать метод Гаусса
int max_in_col(vector < vector<double> > matrix, int col)
{
    int n_rows = matrix.size();
    int maxi = 0;
    double max = matrix[0][col];
    for (int i=0; i<n_rows; i++) {
        if (max < matrix[i][col]) {
            max = matrix[i][col]; maxi = i;
        }
    }
    cout << "max elem in col number " << col << " is " << max << " index = " << maxi << endl;
    return maxi;
}

// нулевая ли строка
bool row_null(vector<double> row)
{ 
    int n_cols = row.size();
    for (int i=0; i<n_cols; i++) {
        if (row[i] != 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    // размеры матрицы
	int n_rows = N_ROWS;
    int n_cols = N_COLS;
    // инициализируем матрицу
    vector< vector<double> > matrix (n_rows, vector<double> (n_cols));
    // теперь ее значения
    srand(time(NULL));
    int i,j;
    for (i = 0; i < n_rows; i++) {
		for (j = 0; j < n_cols; j++) {
			matrix[i][j] = (double)(rand())/RAND_MAX * 100;
		}
	}
    //matrix_print(matrix);
    
    // сколько памяти для хранения матрицы
    double data_size = sizeof(matrix) + sizeof(matrix[0])*n_rows + sizeof(matrix[0][0])*n_rows*n_cols;
    cout << "data size is " << data_size / 8 / 1024 << " KByte" << endl;

    // подсчет времени
    unsigned long t_start, t_end;
    double seconds;

    // алгоритм Гаусса
    int m,l; // еще счетчики
    double t, k; // значение опорного элемента, коэффицент
    t_start = clock(); // засекаем время
    for (i=0, l=0; i<n_rows-1 && l<n_cols; i++, l++) {
        if (matrix[i][l] == 0) { // если опорный 0, то меняем строку
            //cout << "!!! I SEE 0\n";
            for (m=i+1; m<n_rows; m++) { // ищем, где ненулевой элемент в столбце
                if (matrix[m][i] != 0) {
                    swap(matrix[i], matrix[m]); // меняем местами
                    break;
                }
            }
            if (m == n_rows) { // если весь столбец из нулей
                //cout << "!!! ALL ARE 0\n";
                if (l+1 >= n_cols) break; // переходим на другой столбец, если есть возможность
                i--; // смещаемся...
                continue; // ...вправо, на следующей итерации

            } /* else {
                cout << "!!! SWAPPED\n";
                matrix_print(matrix);
            } */
        }

        t = matrix[i][l]; // опорный элемент
        for (j=i+1; j<n_rows; j++) { // обнуляем столбец и вычитаем из строк ниже
            if (matrix[j][l] == 0) continue; // если уже нуль, переходим к следующей строке
            k = matrix[j][l] / t; // иначе считаем коэффицент
            for (m=i; m<n_cols; m++) { // вычитаем из строки
                matrix[j][m] = matrix[j][m] - matrix[i][m] * k;
                if (matrix[j][m] < EPS) { // с заданной точностью
                    matrix[j][m] = 0;
                }
            }
        }
    }

    //matrix_print(matrix);
    
    int r;
    for (r=min(n_rows,n_cols)-1; r>=0; r--) { // считаем ранг
        if (!row_null(matrix[r])) break;
    }
    r++;
    t_end = clock(); // засекаем время
    seconds = ((double)(t_end - t_start))/CLOCKS_PER_SEC;
    
    cout << "matrix size is " << N_ROWS << "*" << N_COLS << endl;
    cout << "time = " << seconds << " sec"<< endl;
    cout << "r = "<< r << endl;
}
