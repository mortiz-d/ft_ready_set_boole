#ifndef NODE_HPP
#define NODE_HPP

#include "base.hpp"

struct Node {
    public:
        bool  negated;
        string value;
        Node* left;
        Node* right;

        Node();
        Node(string val);
        Node(const Node & node);
        ~Node();
        Node &operator=(const Node& otra);
};



#endif