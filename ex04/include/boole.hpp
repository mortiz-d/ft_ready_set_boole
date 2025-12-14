#ifndef BOOLE_HPP
#define BOOLE_HPP
#include <iostream>

#define BITS 8

#include <iostream>
#include <stack>
#include <set>
#include <map>
#include <vector>
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
};


class ExpressionTree {
    private:
        Node* root;
        
        double evaluate(Node* node,std::map<std::string, bool> _input_var) const;
        void clear(Node *root);
        bool isOperator(const std::string& expr) const;

        bool isBoolean(const std::string& expr) const;
        bool isNegation(const std::string& expr) const;
        bool isVariable(const std::string& expr) const;

        std::string inorder(Node* node) const;
        std::string translateValue(const std::string& expr) const;
        std::string inorderMath(Node* node) const;
        void preorder(Node* node) const;
        void postorder(Node* node) const;
        
    public:
        ExpressionTree(void);
        ~ExpressionTree(void);

        void build(const std::string& expr);
        double calculate(std::map<std::string, bool> _input_var) const;

        std::string printInOrderMath(void) const;
        std::string printInOrder(void) const;
        void printPreOrder(void) const;
        void printPostOrder(void) const;
};

class TruthTable {
    private:
        ExpressionTree tree;
        std::map<std::string, std::vector<bool> > _map;
        std::vector<std::string > _colum_order;
        int _n_rows;

        bool isVariable(const std::string& expr) const;
        std::set<std::string> obtainVariables(const std::string& expr) const;

    public:
        TruthTable(void);
        ~TruthTable(void);

        void generate_table(const std::string& expr);
        void display_table(void);
};

#endif