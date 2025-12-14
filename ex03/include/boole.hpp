#ifndef BOOLE_HPP
#define BOOLE_HPP
#include <iostream>

#define BITS 8

#include <iostream>
#include <stack>
#include <cctype>
#include <string>
#include <sstream>
#include <stdexcept>

// https://es.wikipedia.org/wiki/%C3%81lgebra_de_Boole

struct Node {
    public:
        bool  negated;
        std::string value;
        Node* left;
        Node* right;

        Node(std::string val);
        // Node(std::string val) : value(std::move(val)), left(nullptr), right(nullptr) {}
};


class ExpressionTree {
    private:
        Node* root;
        
        double evaluate(Node* node) const;
        void clear(Node *root);
        bool isOperator(const std::string& expr) const;

        bool isBoolean(const std::string& expr) const;
        bool isNegation(const std::string& expr) const;

        std::string inorder(Node* node) const;
        std::string translateValue(const std::string& expr) const;
        std::string inorderMath(Node* node) const;
        void preorder(Node* node) const;
        void postorder(Node* node) const;
        
    public:
        ExpressionTree();
        ~ExpressionTree();

        void build(const std::string& expr);
        double calculate(void) const;

        std::string printInOrderMath(void) const;
        std::string printInOrder(void) const;
        void printPreOrder(void) const;
        void printPostOrder(void) const;
};

#endif