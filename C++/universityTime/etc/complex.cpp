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
		complex () { re = im = 0; }
		//complex(double r) { re = r; im = r; }
		complex (double r): re(r), im(0) {}
		//complex(double a_re = 0, double a_im = 0)//there are def par
		complex (double a_re, double a_im)
		{ 
			::print(); //global proc, if we have same id in class
			re = a_re; im = a_im;
		}
	//methods
		double get_re() const { return re; }
		double get_im() const { return im; }
		double modulo() { return sqrt(re*re + im*im); }	
		void print()
		{
			printf("(%f, %f)\n", re, im);
		}
		const complex& operator=(const complex& a)
		{
			re = a.re; im = a.im; return *this;
		}
	//destructor
		~complex() { /*printf("THEY KILLED ME\n");*/ }
};

complex operator+(const complex &a, const complex &b)
{
	return complex(a.get_re() + b.get_re(), a.get_im() + b.get_im());
}

int main() {
	complex r(5);
	complex z(3,4);
	printf("mod = %f\n", z.modulo());
	
	complex *q;
	q = new complex[3];
	delete[] q;
	
	complex t;
	t = z + 5.0 + r;
	t.print();
	
}
