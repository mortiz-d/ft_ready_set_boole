#include "boole.hpp"
// #include "expression_tree.cpp"


void test(const std::string& expr)
{
    ExpressionTree tree;

    tree.build(expr);

    std::cout << tree.printInOrderMath() << " = " << tree.calculate() << std::endl;

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