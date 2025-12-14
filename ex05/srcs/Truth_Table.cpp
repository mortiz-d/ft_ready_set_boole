#include "boole.hpp"

TruthTable::TruthTable() : _n_rows(0)
{
    return;
}
TruthTable::~TruthTable() 
{ 
    return;
}

bool TruthTable::isVariable(const std::string& expr) const
{
    return expr.size() == 1 && std::isalpha(static_cast<unsigned char>(expr[0]));
}

std::set<std::string> TruthTable::obtainVariables(const std::string& expr) const
{
    std::istringstream iss(expr);
    std::string token;
    std::set<std::string> _var;

    while (iss >> token)
    {
        if (isVariable(token))
            _var.insert(token);
    }
    return _var;
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

void TruthTable::display_formula(void) const
{
   std::cout << this->tree.printInOrder() << std::endl;
    std::cout << this->tree.printInOrderMath() << std::endl;
}

void TruthTable::display_simplified_formula(void) const
{
   std::cout << this->tree.printInOrder() << std::endl;
    std::cout << this->tree.printInOrderMath() << std::endl;
}

void TruthTable::display_table(void)
{
    std::map<std::string, bool > _input;
    if (this->_map.size() == 0)
        return;
    
    
    std::cout << "|";
    for (auto& key : this->_colum_order)
    {
        std::cout << " " << key << " |";
    }
    std::cout << std::endl;

    std::cout << "|";
    for (int i = 0; i < (int)this->_map.size(); i++)
    {
        std::cout << "---|";
    }
    std::cout << std::endl;

    for (int i = 0; i < this->_n_rows; i++)
    {
        // std::cout << "Crap" << std::endl;


        // aux = 0;
        // round = grey_map(i);
        // // std::cout << "Round " << i << " : " << see_binary(round) << std::endl;
        std::cout << "|";
        _input.clear();
        for (auto& key : this->_colum_order)
        {
            if (key == "=")
            {
                std::cout << " " << this->tree.calculate(_input) << " |";
                continue;
            }
            else
            {   
                // _map[key].insert((bool)(round & (1 << aux)));
                // vec.push_back((bool)(round & (1 << aux)));
                _input[key] = this->_map[key][i];
                std::cout << " " << this->_map[key][i] << " |";
                // std::cout << "[" << key << "] : " << _map[key][i] << std::endl;
                // aux++;
            }
        }
        std::cout << std::endl;
        
    }

}

void TruthTable::generate_table(const std::string& expr)
{
    std::set<std::string> _var;
    int round, aux;

    this->_map.clear();
    this->_colum_order.clear();

    _var = this->obtainVariables(expr);
    for (std::string str : _var)
    {
        this->_map[str] = {};
        this->_colum_order.push_back(str);
    }
    for (int i = 0; i < (1 << (int)_var.size()); i++)
    {
        aux = 0;
        round = grey_map(i);
        for (auto& [key, vec]: this->_map)
        {
            vec.push_back((bool)(round & (1 << aux)));
            aux++;
        }
        this->_n_rows += 1;
        
    }
    this->_colum_order.push_back("=");
    this->_map["="] = {};
    this->tree.build_Simplified(expr);
}