#include "boole.hpp"

std::string conjunctive_normal_form(const std::string& expr)
{
    ExpressionTree  tree_result;
    Kargnauth_Map map;
    std::string result = " ";
    try 
    {
        if (map.generate_kmap(expr))
            result = map.kmap_agrupations();

        tree_result.build_Simplified(expr);
        tree_result.normalize_to_the_Right();
        result = tree_result.printPostOrder();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return result;
    
}



void test (std::string str)
{
    std::string aux;

    aux = conjunctive_normal_form(str);

    std::cout << str << std::endl;
    std::cout << aux << std::endl;
    check_formula(str);
    check_formula(aux);

}

int main() {
    
    // test("A B | C | D |");

    // test("A B & C & D &");

    test("A B & ! C ! | ");

    test("A"); //GRITA ERROR

    // test("A B C & |");
//     std::cout << "-------------" << std::endl;

    // test("A B C & | D |");
    // test("A B C D | | &");
    // test("A B &");
    // test("A B C D F & | |  & ");
    
    return 0;
}