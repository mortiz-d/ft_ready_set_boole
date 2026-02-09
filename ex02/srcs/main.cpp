#include "../../files/include/boole.hpp"


void test (int value)
{
    int grey_value = grey_map(value);

    cout << "Normal Value ("<< value <<")" << endl << see_binary(value) << endl;
    cout << "Grey   Value ("<< grey_value <<")" << endl << see_binary(grey_value) << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - "<< endl;
}

// https://en.wikipedia.org/wiki/Gray_code
int main (void)
{	
    test(5);
    test(3);
    test(2);
	return 0;
}