#include "boole.hpp"


bool sat(const std::string& expr)
{
    ExpressionTree tree;
    TruthTable table;
    int result = 0;

    try
    {   
        // std::cout << "FORMULA '" << expr << "'" <<std::endl;
        table.generate_table(expr);
        // table.display_table();
        result = table.get_nbr_posibilities();
        // std::cout << "There are '" << result << "' results" <<std::endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    if (result != 0)
        return true;
    return false;
}

void test (std::string str)
{
    std::cout << str << std::endl;
    std::cout << sat(str) << std::endl;
}

int main() {
    
    test("A B | C | D |");

    test("A B & C & D &");
    
    test("A B & ! C ! | ");

    test("A A ! &");

    test("A A ^");

    // test("A"); //GRITA ERROR

    // test("A B C & |");
//     std::cout << "-------------" << std::endl;

    // test("A B C & | D |");
    // test("A B C D | | &");
    // test("A B &");
    // test("A B C D F & | |  & ");
    
    return 0;
}