#include "boole.hpp"

Cube::Cube()
{
    return;
}

Cube::~Cube()
{
    return;
}


void Cube::visualize()
{
    std::cout << "Cube {" << std::endl;
    std::cout <<  "  type: "<< this->columns.size() << " x "<< this->rows.size() << std::endl;
    
    std::cout <<  "  col : { ";
    for (int col :  this->columns)
    {
        std::cout << col << " ";
    }
    std::cout << "  }" << std::endl;
    
    std::cout <<  "  rows: { ";
    for (int r : this->rows)
    {
        std::cout << r << " ";
    }
    std::cout << "  }" << std::endl;

    std::cout << "}" << std::endl;

    return;
}
