#ifndef BOOLE_HPP
#define BOOLE_HPP
#include <iostream>

#define BITS 8

#include <iomanip> 
#include <stack>
#include <set>
#include <map>
#include <vector>
#include <cctype>
#include <string>
#include <sstream>
#include <stdexcept>


#define DEBUG 0

// using std::string;

// https://es.wikipedia.org/wiki/%C3%81lgebra_de_Boole

struct Node {
    public:
        bool  negated;
        std::string value;
        Node* left;
        Node* right;

        Node();
        Node(std::string val);
        Node(const Node & node);
        ~Node();
        Node &operator=(const Node& otra);
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

        Node* simplify_formula (Node* node);
        Node* normalizeRight(Node* node);
        std::string inorder(Node* node) const;
        std::string translateValue(const std::string& expr) const;
        std::string inorderMath(Node* node) const;
        void preorder(Node* node) const;
        std::string postorder(Node* node) const;
        
    public:
        ExpressionTree(void);
        ~ExpressionTree(void);

        void build_Simplified(const std::string& expr);
        void build(const std::string& expr);
        double calculate(std::map<std::string, bool> _input_var) const;
        void normalize_to_the_Right(void);

        std::string printInOrderMath(void) const;
        std::string printInOrder(void) const;
        void printPreOrder(void) const;
        std::string printPostOrder(void) const;
};

class Cube {        
    public:
        std::set<int> columns;
        std::set<int> rows;

        Cube(void);
        ~Cube(void);
        void visualize();
};


class TruthTable {
    private:
        ExpressionTree tree;
        std::vector<std::vector<int>> _table;
        std::vector<std::string > _colum_order;
        int _n_rows;


        //New Truth table


        public:
        TruthTable(void);
        ~TruthTable(void);
        
        void generate_table(const std::string& expr);
        void display_table(void) const;
        int get_nbr_posibilities(void) const;
};

class Kargnauth_Map {
    private:
        TruthTable table;
        ExpressionTree tree;
        std::vector<std::string> kmap_rows_vars;
        std::vector<std::string> kmap_cols_vars;
        std::vector<std::vector<bool>> kmap;
        std::vector<std::vector<bool>> kmap_unchecked;
        std::vector<Cube> validated_areas; //kargnaught

        bool find_aceptable_group(int col, int row);
        bool check_sector(int y ,int x, int y_end, int x_end, int mode);
        std::vector<int> detectChanges(const std::vector<std::vector<int>> gray, std::set<int> columns);
        std::string elavorate_formula(void);
        void appendVarsRPN( const std::vector<int>& changes, const std::vector<std::string>& vars, std::string& out, int& varsCount); //extension of elavorate formula :v
    public:
        Kargnauth_Map(void);
        ~Kargnauth_Map(void);

        bool generate_kmap(const std::string& expr);
        void print_kmap(void) const;
        std::string kmap_agrupations();
};

std::set<std::string> obtainVariables(const std::string& expr);
int grey_map(int value);
int reverse_grey(int num);
std::string see_binary(unsigned int value);



#endif