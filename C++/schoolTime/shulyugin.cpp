#include <iostream>
#include <cmath>
using namespace std;
main () {
	int c = 0;
	int x = 57293;
	int z = 0;
	int r = 0;
	int pr = 0;
	int pl = 0;

	cin >> x ;

	while ( x != 0 ) {
		c = x % 10;
		x = x / 10;
		while (r != 0) {
            int z = 0;
			pr = (r / (10 ^ z)) % 10;
			pl = (r / 10^(z+1)) % 10;
			z++;
			if ((c >= pr) && (c <= pl )) {
				r = r * (10 ^ z) + c * (10 ^(z - 1)) + r % (10 ^ z);
			}
		}
	}

	cout << r ;
}
