#include "boole.hpp"
// #include "expression_tree.cpp"


void test(const std::string& expr)
{
    TruthTable table;
    (void)expr;
    table.generate_table(expr);
    table.display_table();
    // tree.build(expr);

    // std::cout << tree.printInOrderMath() << std::endl;
    // std::cout << tree.calculate() << std::endl;
    

}

// std::string see_binary2(unsigned int value)
// {
//     std::string res = "";
//     int total_bits = (sizeof(value)*BITS);
//     for (int i = total_bits - 1; i >= 0; --i)
//     {
//         if (value & (1 << i))
//             res += "1";
//         else
//             res +=  "0";
//     }
//     return res;
// }

int main() {

    // test("B ! A | ");
    // test("A B & C & D ! |");
    // test("A B & C |");
    test("A B = ");
    test("A B > ");
    // unsigned int i = 1;
    // std::cout  << i << " : "<< see_binary2(i) << std::endl;
}