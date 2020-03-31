#include <stdio.h>
#include <unistd.h>

class A {
		int x;
	public:
		A(int px) { x = px; }
		void print() { printf("A: x = %i\n", x); }
};

class B {
		int y;
		int z;
		A a; //constructor has par-s!
	public:
		B(int py) : z(-10), a(z) { //there we're calling A constructor
			 y = py;
		}
		void print() {
			printf("B: y = %i\n", y);
			printf("B: z = %i\n", z);
			a.print();
		}
};

int main()
{
	B b(5);
	b.print();
	
	
}

