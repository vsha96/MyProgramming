#include <stdio.h>
#include <unistd.h>
#include <math.h>

class complex {
		double re, im;
	public:
		//constructors
		complex() { re = im = 0; }
		complex(double r) { re = r; im = r; }
		complex(double a_re, double a_im) { re = a_re; im = a_im; }
		//destructor
		~complex() {}
		//methods
		double modulo() { return sqrt(re*re + im*im); }	
};

int main() {
	complex z(3,4);
	printf("mod = %f\n", z.modulo());
	
}
