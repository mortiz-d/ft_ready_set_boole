#include "boole.hpp"


Node::Node(std::string val) : negated(false), value(std::move(val)), left(nullptr), right(nullptr) 
{
    return;
}

ExpressionTree::ExpressionTree() : root(nullptr) {}
ExpressionTree::~ExpressionTree() { 
    // std::cout << "Bye bye tree"<< std::endl;
    this->clear(root);
 }

//∧ & Conjuncion
//∨ | Disjuncion
//⊕ ˆ Exclusice Disjuncion 
//⇒ > Material condition
//⇔ = Logical equivalence
bool ExpressionTree::isOperator(const std::string& expr) const
{
    if (expr == "&" || expr == "|"|| expr == "^" || expr == ">"|| expr == "=" || expr == "!")
        return true;
    return false;
}

//⊥   
//⊤
//¬
//∧ 
//∨ 
//⊕ 
//⇒ 
//⇔
std::string ExpressionTree::translateValue(const std::string& expr) const
{
    if (expr == "&")
        return "∧";
    if (expr == "|")
        return "∨";
    if (expr == "^") 
        return "⊕";
    if (expr == ">")
        return "⇒";
    if (expr == "=")
        return "⇔";
    if (expr == "1") 
        return "⊤";
    if (expr == "0")
        return "⊥";
    if (this->isVariable(expr))
        return expr;
    return "Error";
}

bool ExpressionTree::isNegation(const std::string& expr) const
{
    if (expr == "!")
        return true;
    return false;
}

bool ExpressionTree::isBoolean(const std::string& expr) const
{
    if (expr == "1" || expr == "0")
        return true;
    return false;
}

bool ExpressionTree::isVariable(const std::string& expr) const
{
    return expr.size() == 1 && std::isalpha(static_cast<unsigned char>(expr[0]));
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
        } 
        else if (isNegation(token)){
            // std::cout << "Añadimos una negacion al operador anterior " << token << std::endl;
            if (stack.size() < 1)
                throw std::runtime_error("Negacion inválida");
            aux_r = stack.top(); 
            stack.pop();
            aux_r->negated = true;
            stack.push(aux_r);
        }
         else {
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

double ExpressionTree::calculate(std::map<std::string, bool> _input_var) const
{
    return this->evaluate(this->root, _input_var);
}


double ExpressionTree::evaluate(Node* node, std::map<std::string, bool> _input_var) const {
    bool val_l;
    bool val_r;
    bool res;

    if (!node) return 0;

    if(this->isVariable(node->value))
    {
        res = _input_var[node->value];
    }
    else if (this->isBoolean(node->value))
    {
        res = std::stod(node->value);
    }
    else
    {
        val_l = this->evaluate(node->left,_input_var);
        val_r = this->evaluate(node->right,_input_var);

        // std::cout << "Calculamos con " << node->value << std::endl;
        if (node->value == std::string("&")) 
        {
            // std::cout << val_l << " & "<< val_r << " = " << (val_l & val_r) << std::endl;
            res = (val_l & val_r);
        }
        else if (node->value == std::string("|")) 
        {
            // std::cout << val_l << " | "<< val_r << " = " << (val_l | val_r) << std::endl;
            res = (val_l | val_r);
        }
        else if (node->value == std::string("^")) 
        {
            // std::cout << val_l << " == "<< val_r << " = " << (val_l == val_r) << std::endl;
            res = (val_l ^ val_r);
        }
        else if (node->value == std::string(">")) 
        {
            // std::cout << !val_l << " > "<< val_r << " = " << (!val_l | val_r) << std::endl;
            res = !val_l | val_r;
        }
        else if (node->value == std::string("=")) 
        {
            // std::cout << val_l << " == "<< val_r << " = " << (val_l == val_r) << std::endl;
            res = (val_l == val_r);
        }
        else
            throw std::runtime_error("Operador desconocido: " + node->value);
    }

    if (node->negated)
        res = !res;
    return res;
    
    
}

std::string ExpressionTree::inorder(Node* node) const {
    std::string res = "";
    if (!node) 
        return res;
    if (node->negated) //Tal vez?
        res += "!"; // Añadir aqui?
    if (node->left) 
        res += "(";
    res += this->inorder(node->left);
    res += node->value;
    res += this->inorder(node->right);
    if (node->right) 
        res += ")";
    return res;
}

std::string ExpressionTree::inorderMath(Node* node) const {
    std::string res = "";
    if (!node) 
        return res;
    if (node->negated)
        res += "¬";
    if (node->left) 
        res += "(";
    res += this->inorderMath(node->left);
    res += node->value;//this->translateValue(node->value);
    res += this->inorderMath(node->right);
    if (node->right) 
        res += ")";
    return res;
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

std::string ExpressionTree::printInOrder(void) const
{
    std::string result = "";
    result += this->inorder(this->root);
    return result;
}

std::string ExpressionTree::printInOrderMath(void) const
{
    std::string result = "";
    result += this->inorderMath(this->root);
    return result;
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