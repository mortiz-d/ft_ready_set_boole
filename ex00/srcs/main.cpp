#include "../../files/include/boole.hpp"

// https://en.wikipedia.org/wiki/Gray_code

void test (int a,int b)
{
    cout << "Test : "<< a << " + "<< b << " = " << adder(a,b) << endl;
}

int main (void)
{	
    test(1,2);
    test(2,2);
    test(5,20);
    test(16,64);
    test(-4,1);
	return 0;
}