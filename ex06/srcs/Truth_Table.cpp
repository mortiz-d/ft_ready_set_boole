#include "boole.hpp"

TruthTable::TruthTable() : _n_rows(0)
{
    return;
}
TruthTable::~TruthTable() 
{ 
    return;
}



// void TruthTable::display_formula(void) const
// {
//    std::cout << this->tree.printInOrder() << std::endl;
//     std::cout << this->tree.printInOrderMath() << std::endl;
// }



void TruthTable::display_table(void)
{
    std::map<std::string, bool > _input;
    if (this->_map.size() == 0)
        return;
    
    std::cout << std::endl << "Truth Table" << std::endl;
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
                _input[key] = this->_map[key][i];
                std::cout << " " << this->_map[key][i] << " |";
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

    _var = obtainVariables(expr);
    for (std::string str : _var)
    {
        this->_map[str] = {};
        this->_colum_order.push_back(str);
    }
    for (int i = 0; i < (1 << (int)_var.size()); i++)
    {
        aux = 0;
        round = i;// grey_map(i);
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