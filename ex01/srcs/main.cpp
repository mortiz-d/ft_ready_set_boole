#include "../../files/include/boole.hpp"

void test (int a,int b)
{
    cout << "Test : "<< a << " x "<< b << " = " << multiplier(a,b) << endl;
}

int main (void)
{	
    test(1,2);
    test(2,2);
    test(0,20);
    test(16,64);
    test(-4,1);
	return 0;
}