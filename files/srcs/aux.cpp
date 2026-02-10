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


string see_binary(int value)
{
    string str = "";
    for (int i = (int)(sizeof(i)*BITS); i != -1 ;i--)
    {
        if (value & (1 << i))
            str += "1";
        else
            str += "0";
    }
    return str;
}

set<string> obtainVariables(const string& expr)
{
    istringstream iss(expr);
    string token;
    set<string> _var;

    while (iss >> token)
    {
        if (token.size() == 1 && isalpha(static_cast<unsigned char>(token[0])))
            _var.insert(token);
    }
    return _var;
}