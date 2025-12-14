#include "boole.hpp"


int adder(int a, int b)
{
    int carry = 0;
    while (b != 0) {
        carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

// https://en.wikipedia.org/wiki/Binary_multiplier
int multiplier(int a, int b)
{
    int res;

    res = 0;
    while (b != 0) {
        if (b & (1))
            res = adder(res,a);
        a <<= 1;
        b >>= 1;
    }

    return res;
}


int grey_map(int value)
{
    // int map;

    // map = 0;
    // while (value != 0) {

    //     value >>= 1;
    // }
    // return map;
    return value ^ (value >> 1);
}


int reverse_grey(int num)
{
    int mask = num;
    while (mask) {
        mask >>= 1;
        num   ^= mask;
    }
    return num;
}


void see_binary(int value)
{
    for (int i = (int)(sizeof(i)*BITS); i != -1 ;i--)
    {
        if (value & (1 << i))
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << std::endl;
    return;
}



// https://en.wikipedia.org/wiki/Gray_code

int main (void)
{	
    // int a = 15;
    // int b = 3;
    // int res = multiplier(a,b);
    // std::cout << "Hola!" << sizeof(a) << std::endl;
    // std::cout << "Hola!" << a << b << res << std::endl;
    
    int value = 0; // 110
    see_binary(value);
    int grey_value = grey_map(value);
    std::cout << "Grey value is " << value << " its binary is "<< grey_value << " and turning it back is "<< reverse_grey(grey_value) << std::endl;
    see_binary(grey_value);

	return 0;
}