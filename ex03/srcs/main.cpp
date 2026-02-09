#include "boole.hpp"
// #include "expression_tree.cpp"


void test(const std::string& expr)
{
    ExpressionTree tree;
    std::map<std::string, bool> _input_var;

    tree.build(expr);

    std::cout << tree.printInOrderMath() << " = " << tree.calculate(_input_var) << std::endl;

}

int main() {

    test("0 0 | ");
    test("0 1 | ");
    test("1 1 | ");
    test("0 0 & ");
    test("0 1 & ");
    test("1 1 & ");
    test("0 0 > ");
    test("0 1 > ");
    test("1 0 > ");
    test("1 1 > ");
    test("0 0 = ");
    test("0 1 = ");
    test("1 0 = ");
    test("1 1 = ");
    test("0 0 ^ ");
    test("0 1 ^ ");
    test("1 0 ^ ");
    test("1 1 ^ ");
    test("0");
    test("0 !");
    test("1 !");
    test("1 0 ! & ! ");
    test("1 0 ! & 1 1 & &");


}