//задача про нахождение простых чисел
#include <iostream>
#include <math.h>
using namespace std;

int main() {
	setlocale(LC_CTYPE, "rus");
	int mas[26];
	int n = 0;
	int i = 10;
	cout << "2" << endl << "3 " << endl << "5 " << endl << "7 ";
	system("pause");
	while (n != 26) {
		i++;
		if (((i % 2) != 0) && ((i % 3) != 0) && ((i % 4) != 0) && ((i % 5) != 0) && ((i % 6) != 0) && ((i % 7) != 0) && ((i % 8) != 0) && ((i % 9) != 0)) {
			mas[n] = i;
			cout << mas[n] << endl << " ";
			n++;
		}
	}
	system("pause");
	return 0;
}
