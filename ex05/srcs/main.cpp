#include "../../files/include/boole.hpp"

int test (string value)
{
    string str = "";
    string math_c = "";
    string math_s = "";
    int res = 0;

    str = negation_normal_form(value);
    math_s = math_simplified_formula(value);
    math_c = math_complex_formula(value);
    //tirarse por la ventana? opcional :eyes:
    cout
    << left << setw(12) << value           // Columna 1
    << setw(6)  << ":"                     // Columna 2
    << setw(15) << str                     // Columna 3
    << setw(35) << math_s                  // Columna 4
    << setw(35) << math_c                  // Columna 5
    << endl;

    return res;
}

int main() {

    cout << "INPUT         OUTPUT             SIMPLIFIED FORMULA           BASIC FORMULA      " << endl;
    test("A B & !");
    
    test("A B | !");

    test("A B | !");

    test("A B >");
    
    test("A B = ");
    
    test("A B | C & !");
    

    // println!("{}", negation_normal_form("AB="));
    // // AB&A!B!&|
    // println!("{}", negation_normal_form("AB|C&!"));
    // // A!B!&C!|

    //Ley de eliminacion de la doble negacion
    // cout  << "Elimination of double negation law" << endl;
    // negation_normal_form("A !");
    // negation_normal_form("A ! !");
    

    //Ley de Material condition
    // cout  << "Material condition law" << endl;
    // negation_normal_form("A B >");

    //Ley de Equivalence
    // cout  << "Equivalence law" << endl;
    // negation_normal_form("A B =");
    // negation_normal_form("A B >");
    // negation_normal_form(" A B & A ! B ! & |");
   


    //Ley de morgan
    // cout  << "Morgan law" << endl;
    // negation_normal_form("A B | !");
    // negation_normal_form("A B | !!");
    // negation_normal_form("A B & !");
    // negation_normal_form("A B & ! !");

    //Ley de distribucion
    // cout  << "Distribution law" << endl;
    // negation_normal_form("B C | A & ");
    // negation_normal_form("A B C | & ");

    // negation_normal_form("B C & A | ");
    // negation_normal_form("A B C & | ");

    // "AB|!"
    return 0;
}