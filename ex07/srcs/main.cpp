#include "../../files/include/base.hpp"

void test (string str)
{
    cout << str << endl;
    cout << sat(str) << endl;
}

int main() {
    
    test("A B | C | D |");

    test("A B & C & D &");
    
    test("A B & ! C ! | ");

    test("A A ! &");

    test("A A ^");

    // test("A"); //GRITA ERROR

    // test("A B C & |");
//     cout << "-------------" << endl;

    // test("A B C & | D |");
    // test("A B C D | | &");
    // test("A B &");
    // test("A B C D F & | |  & ");
    
    return 0;
}