#include "boole.hpp"
// #include "expression_tree.cpp"


std::string conjunctive_normal_form(const std::string& expr)
{
    ExpressionTree tree;
    TruthTable table;
    Kargnauth_Map map;

    tree.build_Simplified(expr);
    std::cout << expr << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << tree.printInOrder() << std::endl;
    std::cout << tree.printInOrderMath() << std::endl;
    std::cout << "-------------" << std::endl;
    table.generate_table(expr);
    table.display_table();
    std::cout << "-------------" << std::endl;

    map.generate_kmap(expr);
    map.print_kmap(); 
    map.kmap_to_formula_2();
    return "ejemplo";
}


int main() {

    // conjunctive_normal_form("A B | C | D |");

    // conjunctive_normal_form("A ");
    // conjunctive_normal_form("A B C & |");
    // conjunctive_normal_form("A B &");
    // conjunctive_normal_form("A B C D F & | |  & ");
    // conjunctive_normal_form("A A ! & B B ! & C C & | | ");

    conjunctive_normal_form("A B ! |");
    // conjunctive_normal_form("A B |");


    // conjunctive_normal_form("A B C D & | &");
    
    //  conjunctive_normal_form(" ");


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