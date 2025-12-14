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


struct Node {
    public:
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
        bool isNumber(const std::string& expr) const;

        void inorder(Node* node) const;
        void preorder(Node* node) const;
        void postorder(Node* node) const;
        
    public:
        ExpressionTree();
        ~ExpressionTree();

        void build(const std::string& expr);
        double calculate(void) const;

        void printInOrder(void) const;
        void printPreOrder(void) const;
        void printPostOrder(void) const;
};


// struct Node {
//     std::string value;
//     Node* left;
//     Node* right;

//     Node(std::string val) : value(std::move(val)), left(nullptr), right(nullptr) {}
// };

// class ExpressionTree {
// private:
//     Node* root;

//     // función recursiva para evaluar el árbol
//     double evaluate(Node* node) const {
//         if (!node) return 0;

//         // si el nodo es número
//         if (isNumber(node->value))
//             return std::stod(node->value);

//         // si es operador
//         double leftVal = evaluate(node->left);
//         double rightVal = evaluate(node->right);

//         if (node->value == "+") return leftVal + rightVal;
//         if (node->value == "-") return leftVal - rightVal;
//         if (node->value == "*") return leftVal * rightVal;
//         if (node->value == "/") return leftVal / rightVal;

//         throw std::runtime_error("Operador desconocido: " + node->value);
//     }

//     bool isOperator(const std::string& c) const {
//         return c == "+" || c == "-" || c == "*" || c == "/";
//     }

//     bool isNumber(const std::string& s) const {
//         if (s.empty()) return false;
//         bool point = false;
//         for (char ch : s) {
//             if (std::isdigit(ch)) continue;
//             if (ch == '.' && !point) { point = true; continue; }
//             return false;
//         }
//         return true;
//     }

//     void clear(Node* node) {
//         if (!node) return;
//         clear(node->left);
//         clear(node->right);
//         delete node;
//     }

//     void inorder(Node* node) const {
//         if (!node) return;
//         if (node->left) std::cout << "(";
//         inorder(node->left);
//         std::cout << node->value;
//         inorder(node->right);
//         if (node->right) std::cout << ")";
//     }

//     void preorder(Node* node) const {
//         if (!node) return;
//         std::cout << node->value << " ";
//         preorder(node->left);
//         preorder(node->right);
//     }

//     void postorder(Node* node) const {
//         if (!node) return;
//         postorder(node->left);
//         postorder(node->right);
//         std::cout << node->value << " ";
//     }

// public:
//     ExpressionTree() : root(nullptr) {}
//     ~ExpressionTree() { clear(root); }

//     // Construir desde una expresión en notación postfija
//     void buildFromPostfix(const std::string& expr) {
//         clear(root);
//         root = nullptr;
//         std::stack<Node*> stack;

//         std::istringstream iss(expr);
//         std::string token;

//         while (iss >> token) {
//             if (!isOperator(token)) {
//                 stack.push(new Node(token)); // operando
//             } else {
//                 // operador: sacar dos operandos
//                 if (stack.size() < 2)
//                     throw std::runtime_error("Expresión postfija inválida");

//                 Node* right = stack.top(); stack.pop();
//                 Node* left = stack.top(); stack.pop();

//                 Node* op = new Node(token);
//                 op->left = left;
//                 op->right = right;
//                 stack.push(op);
//             }
//         }

//         if (stack.size() != 1)
//             throw std::runtime_error("Expresión postfija inválida (sobran operandos)");

//         root = stack.top();
//     }

//     // Mostrar en distintos órdenes
//     void printInorder() const { inorder(root); std::cout << "\n"; }
//     void printPreorder() const { preorder(root); std::cout << "\n"; }
//     void printPostorder() const { postorder(root); std::cout << "\n"; }

//     // Evaluar el árbol
//     double evaluate() const {
//         if (!root) throw std::runtime_error("Árbol vacío");
//         return evaluate(root);
//     }
// };


#endif