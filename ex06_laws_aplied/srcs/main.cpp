#include "boole.hpp"
// #include "expression_tree.cpp"


std::string negation_normal_form(const std::string& expr)
{
    ExpressionTree tree;

    tree.build_Simplified(expr);
    return tree.printPostOrder();
}

int diff (std::string value, std::string expected)
{
    if (value == expected)
        return 1;
    return 0;
}


int test (std::string value, std::string expected)
{
    std::string str = "";
    int res = 0;

    str = negation_normal_form(value);
    res = diff(str, expected);
    std::cout << str << " " << expected << " : " << res << std::endl;

    return res;
}

int main() {

    test("A B & !", "A!B!|");
    
    test("A B | !", "A!B!&");
    
    test("A B | C &", "AB|C&");
  
    test(" A B | C | D |", "ABCD|||");
    
    test("A B & C & D &", "ABCD&&&");
    
    test("A B & ! C ! |", "A!B!C!||");
    test("A B | ! C ! &", " A!B!C!&&");
    
    return 0;
}