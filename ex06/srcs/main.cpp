#include "../../files/include/base.hpp"

void check_formula(const string str)
{
    ExpressionTree tree;
    TruthTable table;
    Kargnauth_Map map;

    try
    {   
        cout << "FORMULA '" << str << "'" <<endl;
        tree.build_Simplified(str);
        tree.normalize_to_the_Right();
        table.generate_table(str);
        table.display_table();

        if (map.generate_kmap(str))
            map.print_kmap(); 
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
    }
    
    return;
}

void test (string str)
{
    string aux;

    aux = conjunctive_normal_form(str);

    cout << str << endl;
    cout << aux << endl;
    check_formula(str);
    check_formula(aux);

}

int main() {
    
    // test("A B | C | D |");

    // test("A B & C & D &");

    test("A B & ! C ! | ");

    test("A"); //GRITA ERROR


    // test("A B C & | D |");
    // test("A B C D | | &");
    // test("A B &");
    // test("A B C D F & | |  & ");
    
    return 0;
}