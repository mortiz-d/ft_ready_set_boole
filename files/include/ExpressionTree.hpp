#ifndef EXPRESSIONTREE_HPP
#define EXPRESSIONTREE_HPP

#include "base.hpp"


class ExpressionTree {
    private:
        Node* root;
        
        double evaluate(Node* node,map<string, bool> _input_var) const;
        void clear(Node *root);
        bool isOperator(const string expr) const;

        bool isBoolean(const string expr) const;
        bool isNegation(const string expr) const;
        bool isVariable(const string expr) const;

        Node* simplify_formula (Node* node);
        Node* normalizeRight(Node* node);
        string inorder(Node* node) const;
        string translateValue(const string expr) const;
        string inorderMath(Node* node) const;
        void preorder(Node* node) const;
        string postorder(Node* node) const;
        
    public:
        ExpressionTree(void);
        ~ExpressionTree(void);

        void build_Simplified(const string expr);
        void build(const string expr);
        double calculate(map<string, bool> _input_var) const;
        void normalize_to_the_Right(void);

        string printInOrderMath(void) const;
        string printInOrder(void) const;
        void printPreOrder(void) const;
        string printPostOrder(void) const;
};


//∧ & Conjuncion
//∨ | Disjuncion
//⊕ ˆ Exclusice Disjuncion 
//⇒ > Material condition
//⇔ = Logical equivalence

//⊥ 0 False
//⊤ 1 True
//¬ ! Negation



#endif