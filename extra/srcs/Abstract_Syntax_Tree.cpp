#include "boole.hpp"


Node::Node(std::string val) : value(std::move(val)), left(nullptr), right(nullptr) 
{
    return;
}

ExpressionTree::ExpressionTree() : root(nullptr) {}
ExpressionTree::~ExpressionTree() { this->clear(root); }

bool ExpressionTree::isOperator(const std::string& expr) const
{
    if (expr == "+" || expr == "-" || expr == "*" || expr == "/")
        return true;
    return false;
}

bool ExpressionTree::isNumber(const std::string& expr) const
{
    if (expr.empty())
        return false;
    
    bool point = false;
    for (size_t i = 0; i < expr.size(); i ++) {
        if (std::isdigit(expr[i])) continue;
        if (expr[i] == '.' && !point) 
        { 
            point = true; 
            continue;
        }
        return false;
    }
    return true;
}

void ExpressionTree::build(const std::string& expr) {
    // std::cout << "WOLOLO Tenemos la frase " << expr << std::endl;

    this->clear(root);
    this->root = nullptr;
    std::stack<Node*> stack;
    Node* aux_r;
    Node* aux_l;
    Node* op;

    std::istringstream iss(expr);
    std::string token;

    while (iss >> token) {
        // std::cout << token << std::endl;
        if (!isOperator(token)) {
            // std::cout << "Añadimos a la lista " << token << std::endl;
            stack.push(new Node(token)); // operando
        } else {
            // std::cout << "Añadimos un nodo a la operacion " << token << std::endl;
            if (stack.size() < 2)
                throw std::runtime_error("Expresión postfija inválida");
            aux_r = stack.top(); 
            stack.pop();
            aux_l = stack.top(); 
            stack.pop();

            op = new Node(token);
            op->left = aux_l;
            op->right = aux_r;
            stack.push(op);
        }
    }

    if (stack.size() != 1)
        throw std::runtime_error("Expresión postfija inválida (sobran operandos)");

    this->root = stack.top();
}

double ExpressionTree::calculate(void) const
{
    return this->evaluate(this->root);
}

double ExpressionTree::evaluate(Node* node) const {
    if (!node) return 0;
    if (this->isNumber(node->value))
        return std::stod(node->value);

    double leftVal = this->evaluate(node->left);
    double rightVal = this->evaluate(node->right);

    if (node->value == "+") return leftVal + rightVal;
    if (node->value == "-") return leftVal - rightVal;
    if (node->value == "*") return leftVal * rightVal;
    if (node->value == "/") return leftVal / rightVal;

    throw std::runtime_error("Operador desconocido: " + node->value);
}

void ExpressionTree::inorder(Node* node) const {
    if (!node) return;
    if (node->left) std::cout << "(";
    this->inorder(node->left);
    std::cout << node->value;
    this->inorder(node->right);
    if (node->right) std::cout << ")";
}

void ExpressionTree::preorder(Node* node) const {
    if (!node) return;
    std::cout << node->value << " ";
    this->preorder(node->left);
    this->preorder(node->right);
}

void ExpressionTree::postorder(Node* node) const {
    if (!node) return;
    this->postorder(node->left);
    this->postorder(node->right);
    std::cout << node->value << " ";
}


void ExpressionTree::clear(Node *node)
{
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
    // std::cout << "Limpiamos un node" << std::endl;
    return;
}

void ExpressionTree::printInOrder(void) const
{
    this->inorder(this->root);
    std::cout << std::endl;
}

void ExpressionTree::printPreOrder(void) const
{
    this->preorder(this->root);
    std::cout << std::endl;
}

void ExpressionTree::printPostOrder(void) const
{
    this->postorder(this->root);
    std::cout << std::endl;
}