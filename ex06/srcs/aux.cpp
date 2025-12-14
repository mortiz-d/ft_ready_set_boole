#include "boole.hpp"

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

std::string see_binary(unsigned int value)
{
    std::string res = "";
    int total_bits = (sizeof(value)*BITS);
    for (int i = total_bits - 1; i >= 0; --i)
    {
        if (value & (1 << i))
            res += "1";
        else
            res +=  "0";
    }
    return res;
}

std::set<std::string> obtainVariables(const std::string& expr)
{
    std::istringstream iss(expr);
    std::string token;
    std::set<std::string> _var;

    while (iss >> token)
    {
        if (token.size() == 1 && std::isalpha(static_cast<unsigned char>(token[0])))
            _var.insert(token);
    }
    return _var;
}