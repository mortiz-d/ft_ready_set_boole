#include "boole.hpp"

TruthTable::TruthTable() : _n_rows(0)
{
    return;
}
TruthTable::~TruthTable() 
{ 
    return;
}

std::vector<std::vector<int>> generateGrayCode_Truth_Table(int amount_variables) {
    int mask ,code ;
    int size = 1 << amount_variables;  // 2^n
    std::vector<std::vector<int>> gray(size , std::vector<int>(amount_variables));

    for (int i = 0; i < size; i++) {
        code = grey_map(i);

        for (int bit = 0; bit < amount_variables; bit++) {
            mask = 1 << (amount_variables - 1 - bit);
            if ((code & mask))
                gray[i][bit] = 1;
            else
                gray[i][bit] = 0;
        }
    }
    return gray;
}


void TruthTable::generate_table(const std::string& expr)
{
    std::set<std::string> vars = obtainVariables(expr);
    std::map<std::string, bool> input;
    int n = vars.size();
    int rows = 1 << n;
    
    _n_rows = rows;
    this->_colum_order.clear();
    this->_table.clear();

    if (n == 0)
    {
        std::cout << "No variables to create Truth Table" << std::endl;
        return;
    }

    //Creating the input so each row on the truth table has an input
    for (std::string v : vars)
        this->_colum_order.push_back(v);

    tree.build_Simplified(expr);
    this->_table = generateGrayCode_Truth_Table(n);

    //Here se set the table
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < n; j++)
            input[this->_colum_order[j]] = this->_table[i][j];

        this->_table[i].push_back(this->tree.calculate(input));
    }
}

void TruthTable::display_table(void) const
{
    if (this->_table.empty())
        return;

    std::cout << std::endl <<"Truth Table|" << std::endl;

    for (std::string col : this->_colum_order)
        std::cout << " " << col << " |";

    std::cout << std::endl << "|";
    for (size_t i = 0; i < this->_colum_order.size(); i++)
        std::cout << "---|";
    std::cout << std::endl;

    for (std::vector<int> row : this->_table)
    {
        std::cout << "|";
        for (int value : row)
            std::cout << " " << value << " |";
        std::cout << std::endl;
    }
}



int TruthTable::get_nbr_posibilities(void) const
{
    size_t posibilities = 0; 
    int result_score = this->_colum_order.size();

    for (std::vector<int> row : this->_table)
    {
        if ( row[result_score] )
            posibilities++;
    }
    return posibilities;
}
