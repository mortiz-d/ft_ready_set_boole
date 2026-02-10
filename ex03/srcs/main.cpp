#include "../../files/include/boole.hpp"

void test(string expr)
{
    ExpressionTree tree;
    bool res;

    res = eval_formula(expr);
    if (res)
    {
        tree.build(expr);
        cout << expr << " ==> " << tree.printInOrderMath() << " ==> "<< res << endl;
    }    
    else
        cout << expr << " ==> "<< res << endl;


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