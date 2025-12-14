#include "boole.hpp"


Node::Node(): negated(false), value("None"), left(nullptr), right(nullptr) 
{
    return;
}

Node::Node(std::string val) : negated(false), value(std::move(val)), left(nullptr), right(nullptr) 
{
    return;
}

Node::Node(const Node & node)
{
    // std::cout  << "Constructor de copia" << std::endl;
    *this = node;
}

Node::~Node()
{
    // std::cout  << "destruido" << std::endl;
    return;
}

Node &Node::operator=(const Node& other)
{
    // std::cout  << "Operador =" << std::endl;
    this->value = other.value;
    this->left = other.left ? new Node(*other.left) : nullptr;
    this->right = other.right ? new Node(*other.right) : nullptr;
    this->negated = other.negated;
    return (*this);
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

            aux_r->negated = !aux_r->negated;
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


Node* ExpressionTree::simplify_formula (Node* node)
{
    Node* aux_r;//, *aux_r_2;
    Node* aux_l;//, *aux_l_2;
    Node* op ,*aux_op, *aux_node;
    std::string aux_val;
    (void) aux_node;
    // std::cout  << "Simplify formula (complex version)" << this->inorder(node)  << std::endl;

    (void) op;
    (void) aux_r;
    (void) aux_l;

    if(node->value == ">")
    {
        node->value = "|";
        node->left->negated = !node->left->negated;
    }
    else if (node->value == "=")
    {
        op = new Node(*node);
        aux_op = new Node("&");
        node->value = ">";
        op->value = ">";
        aux_val = op->left->value;
        op->left->value = op->right->value;
        op->right->value = aux_val;

        op = this->simplify_formula(op);
        node = this->simplify_formula(node);
        aux_op->left = node;
        aux_op->right = op;
        node = aux_op;
    }
    else if ((node->value == "&" || node->value == "|") && node->negated)
    {
        if (node->value == "&")
            node->value = "|";
        else
            node->value = "&";

        node->negated = !node->negated;
        node->left->negated = !node->left->negated;
        // aux_r->negated = !aux_r->negated;
        if (this->isOperator(node->left->value))
            simplify_formula(node->left);
        node->right->negated = !node->right->negated;
        if (this->isOperator(node->right->value))
            simplify_formula(node->right);
        // aux_r->negated = !aux_r->negated;
        //     if (this->isOperator(token))
        //         aux_r = simplify_formula(aux_r);

    }
    else if ((node->value == "&" ))//|| node->value == "|"))
    {
        // (A ∧ (B ∨ C)) ⇔ ((A ∧ B) ∨ (A ∧ C))
        // (A & (B | C)) == ((A & B) | (A & C))
        if ( node->left->value == "|" && (this->isVariable(node->right->value) || this->isBoolean(node->right->value)))
        {
            
            op = new Node(*node->left);
            aux_op = new Node(*node->left);
            aux_node = new Node(*node->right);
            // aux_val = node->right->value;

            aux_op->left = node->right;
            aux_op->value = "&";
            op->right = op->left;
            op->left = aux_node;
            op->value = "&";
            node->right = aux_op;
            node->left = op;
            node->value = "|";
        }
        else if ( node->right->value == "|" && (this->isVariable(node->left->value) || this->isBoolean(node->left->value)))
        {
            
            op = new Node(*node->right);
            aux_op = new Node(*node->right);
            aux_node = new Node(*node->left); 

            aux_op->left = node->left;
            aux_op->value = "&";
            op->right = op->left;
            // op->left = op->right;
            op->left = aux_node;
            op->value = "&";
            node->right = aux_op;
            node->left = op;
            node->value = "|";
        }
    }
    else if ((node->value == "|" ))//|| node->value == "|"))
    {
        if ( node->left->value == "&" && (this->isVariable(node->right->value) || this->isBoolean(node->right->value)))
        {
            op = new Node(*node->left);
            aux_op = new Node(*node->left);
            aux_node = new Node(*node->right);
            // aux_val = node->right->value;

            aux_op->left = node->right;
            aux_op->value = "|";
            op->right = op->left;
            op->left = aux_node;
            op->value = "|";
            node->right = aux_op;
            node->left = op;
            node->value = "&";
        }
        else if ( node->right->value == "&" && (this->isVariable(node->left->value) || this->isBoolean(node->left->value)))
        {
            op = new Node(*node->right);
            aux_op = new Node(*node->right);
            aux_node = new Node(*node->left); 

            aux_op->left = node->left;
            aux_op->value = "|";
            op->right = op->left;
            // op->left = op->right;
            op->left = aux_node;
            op->value = "|";
            node->right = aux_op;
            node->left = op;
            node->value = "&";
        }
    }


    return node;
}



void ExpressionTree::build_Simplified(const std::string& expr) {

    this->clear(root);
    this->root = nullptr;
    std::stack<Node*> stack;
    Node* aux_r;//, *aux_r_2;
    Node* aux_l;//, *aux_l_2;
    Node* op ;//, *aux_op;

    std::istringstream iss(expr);
    std::string token;

    while (iss >> token) {
        if (!isOperator(token)) {
            stack.push(new Node(token)); // operando
        } 
        else if (isNegation(token)){
            if (stack.size() < 1)
                throw std::runtime_error("Negacion inválida");
            aux_r = stack.top(); 
            stack.pop();

            aux_r->negated = !aux_r->negated;
            if (this->isOperator(token))
                aux_r = simplify_formula(aux_r);
            stack.push(aux_r);
        }
        else {
            if (stack.size() < 2)
                throw std::runtime_error("Expresión postfija inválida");
            aux_r = stack.top(); 
            stack.pop();
            aux_l = stack.top(); 
            stack.pop();

            op = new Node(token);
            op->left = aux_l;
            op->right = aux_r;
            
            
        op = simplify_formula(op);
            


            // (A ⇔ B) ⇔ ((A ⇒ B) ∧ (B ⇒ A))
            // (A ⇔ B) ⇔ ((¬A ∨ B) ∧ (¬B ∨ A))


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

//¬
//∧ 
//∨ 
//⊕ 
//⇒ 
//⇔
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
        if (node->value == std::string("&")) //∧ 
        {
            // std::cout << val_l << " & "<< val_r << " = " << (val_l & val_r) << std::endl;
            res = (val_l & val_r);
        }
        else if (node->value == std::string("|")) //∨ 
        {
            // std::cout << val_l << " | "<< val_r << " = " << (val_l | val_r) << std::endl;
            res = (val_l | val_r);
        }
        else if (node->value == std::string("^")) //⊕
        {
            // std::cout << val_l << " == "<< val_r << " = " << (val_l == val_r) << std::endl;
            res = (val_l ^ val_r);
        }
        else if (node->value == std::string(">")) //⇒ 
        {
            // std::cout << !val_l << " > "<< val_r << " = " << (!val_l | val_r) << std::endl;
            res = !val_l | val_r;
        }
        else if (node->value == std::string("=")) //⇔
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
    res += this->translateValue(node->value);
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

std::string ExpressionTree::postorder(Node* node) const {
    std::string str = "";

    if (!node) return str;
    str += this->postorder(node->left);
    str += this->postorder(node->right);
    str += node->value;
    if (node->negated)
        str += "!"; 
    return str;
}


void ExpressionTree::printPreOrder(void) const
{
    this->preorder(this->root);
    std::cout << std::endl;
}

std::string ExpressionTree::printPostOrder(void) const
{
    return this->postorder(this->root);
}