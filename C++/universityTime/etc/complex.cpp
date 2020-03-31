#include <stdio.h>
#include <unistd.h>
#include <math.h>

void print()
{
	printf("You've initialized smt\n");
}

class complex {
		double re, im;
	public:
		//constructors
		complex() { re = im = 0; }
		//complex(double r) { re = r; im = r; }
		complex(double r): re(r), im(r) {}
		//complex(double a_re = 0, double a_im = 0)//there are def par
		complex(double a_re, double a_im)
		{ 
			::print(); //global proc, if we have same id in class
			re = a_re; im = a_im;
		}
		//destructor
		~complex() { printf("THEY KILLED ME\n"); }
		//methods
		double modulo() { return sqrt(re*re + im*im); }	
};

int main() {
	complex r(5);
	complex z(3,4);
	printf("mod = %f\n", z.modulo());

	complex *q;
	q = new complex[10];
	delete[] q;
	
}
