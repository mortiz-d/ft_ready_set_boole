#include "../../files/include/boole.hpp"

void test(const string str)
{
    print_truth_table(str);
}

int main() {

    // test("B ! A | ");
    // test("A B & C & D ! |");
    // test("A B & C |");
    print_truth_table("A B = ");
    print_truth_table("A B > ");
}