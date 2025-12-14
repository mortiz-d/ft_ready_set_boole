#include "boole.hpp"
// #include "expression_tree.cpp"


std::string negation_normal_form(const std::string& expr)
{
    ExpressionTree tree;

    tree.build_Simplified(expr);
    // std::cout << tree.printInOrderMath() << std::endl;
    return tree.printPostOrder();
}

std::string math_simplified_formula(const std::string& expr)
{
    ExpressionTree tree;

    tree.build_Simplified(expr);
    // std::cout << tree.printInOrderMath() << std::endl;
    return tree.printInOrderMath();
}

std::string math_complex_formula(const std::string& expr)
{
    ExpressionTree tree;

    tree.build(expr);
    // std::cout << tree.printInOrderMath() << std::endl;
    return tree.printInOrderMath();
}


int test (std::string value)
{
    std::string str = "";
    std::string math_c = "";
    std::string math_s = "";
    int res = 0;

    str = negation_normal_form(value);
    math_s = math_simplified_formula(value);
    math_c = math_complex_formula(value);
    //tirarse por la ventana? opcional :eyes:
    std::cout
    << std::left << std::setw(12) << value      // Columna 1
    << std::setw(6)  << ":"                     // Columna 2
    << std::setw(15) << str                     // Columna 3
    << std::setw(35) << math_s                  // Columna 4
    << std::setw(35) << math_c                  // Columna 5
    << std::endl;

    // std::cout << value << " : " << str << " " << math  << std::endl;


    return res;
}

int main() {

    std::cout << "INPUT         OUTPUT             SIMPLIFIED FORMULA           BASIC FORMULA      " << std::endl;
    test("A B & !");
    
    test("A B | !");

    test("A B | !");

    test("A B >");
    
    test("A B = "); //Discutir la forma de distribuir la ley de equivalencia
    
    test("A B | C & !");
    

    // println!("{}", negation_normal_form("AB="));
    // // AB&A!B!&|
    // println!("{}", negation_normal_form("AB|C&!"));
    // // A!B!&C!|

    //Ley de eliminacion de la doble negacion
    // std::cout  << "Elimination of double negation law" << std::endl;
    // negation_normal_form("A !");
    // negation_normal_form("A ! !");
    

    //Ley de Material condition
    // std::cout  << "Material condition law" << std::endl;
    // negation_normal_form("A B >");

    //Ley de Equivalence
    // std::cout  << "Equivalence law" << std::endl;
    // negation_normal_form("A B =");
    // negation_normal_form("A B >");
    // negation_normal_form(" A B & A ! B ! & |");
   


    //Ley de morgan
    // std::cout  << "Morgan law" << std::endl;
    // negation_normal_form("A B | !");
    // negation_normal_form("A B | !!");
    // negation_normal_form("A B & !");
    // negation_normal_form("A B & ! !");

    //Ley de distribucion
    // std::cout  << "Distribution law" << std::endl;
    // negation_normal_form("B C | A & ");
    // negation_normal_form("A B C | & ");

    // negation_normal_form("B C & A | ");
    // negation_normal_form("A B C & | ");

    // "AB|!"
    return 0;
}