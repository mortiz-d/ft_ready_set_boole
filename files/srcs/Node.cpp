#include "boole.hpp"

Node::Node(): negated(false), value("None"), left(nullptr), right(nullptr) 
{
    return;
}

Node::Node(string val) : negated(false), value(move(val)), left(nullptr), right(nullptr) 
{
    return;
}

Node::Node(const Node & node)
{
    // cout  << "Constructor de copia" << endl;
    *this = node;
}

Node::~Node()
{
    // cout  << "destruido" << endl;
    return;
}

Node &Node::operator=(const Node& other)
{
    // cout  << "Operador =" << endl;
    this->value = other.value;
    this->left = other.left ? new Node(*other.left) : nullptr;
    this->right = other.right ? new Node(*other.right) : nullptr;
    this->negated = other.negated;
    return (*this);
}