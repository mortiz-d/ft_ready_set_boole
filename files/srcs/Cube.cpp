#include "base.hpp"

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
    cout << "Cube {" << endl;
    cout <<  "  type: "<< this->columns.size() << " x "<< this->rows.size() << endl;
    
    cout <<  "  col : { ";
    for (int col :  this->columns)
    {
        cout << col << " ";
    }
    cout << "  }" << endl;
    
    cout <<  "  rows: { ";
    for (int r : this->rows)
    {
        cout << r << " ";
    }
    cout << "  }" << endl;

    cout << "}" << endl;

    return;
}
