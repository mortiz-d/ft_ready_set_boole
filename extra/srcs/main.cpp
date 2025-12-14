#include "boole.hpp"
// #include "expression_tree.cpp"

int main() {
    ExpressionTree tree;

    // Ejemplo simple: 1 1 +
    std::string expr = "1 1 + 2 +";
    tree.build(expr);

    std::cout << "Inorden: ";   
    // tree.printInOrder();
    std::cout << "Inrden: ";  tree.printInOrder();  // ((1 + 1) + 2)
    std::cout << "Preorden: ";  tree.printPreOrder();  // + + 1 1 2
    std::cout << "Postorden: "; tree.printPostOrder(); // 1 1 + 2 +
    std::cout << "Result: " << tree.calculate() << std::endl;// 4
    // std::cout << "Resultado: " << tree.evaluate() << "\n";

}