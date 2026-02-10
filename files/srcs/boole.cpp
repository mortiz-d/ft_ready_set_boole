#include "boole.hpp"


//ex03
bool eval_formula(const string str)
{
    ExpressionTree tree;
    
    try
    {
        tree.build(str);
    }
    catch(const exception& e)
    {
        return false;
    }
    return true;

}

//ex04
void print_truth_table(const string str)
{
    TruthTable table;

    table.generate_table(str);
    table.display_table();
}

//ex05
string negation_normal_form(const string str)
{
    ExpressionTree tree;

    tree.build_Simplified(str);
    return tree.printPostOrder();
}

string math_simplified_formula(const string str)
{
    ExpressionTree tree;

    tree.build_Simplified(str);
    return tree.printInOrderMath();
}

string math_complex_formula(const string str)
{
    ExpressionTree tree;

    tree.build(str);
    return tree.printInOrderMath();
}

//ex06
string conjunctive_normal_form(const string str)
{
    ExpressionTree  tree_result;
    Kargnauth_Map map;
    string result = " ";
    try 
    {
        if (map.generate_kmap(str))
            result = map.kmap_agrupations();

        tree_result.build_Simplified(str);
        tree_result.normalize_to_the_Right();
        result = tree_result.printPostOrder();
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return result;
    
}

//ex07
bool sat(const string str)
{
    ExpressionTree tree;
    TruthTable table;
    int result = 0;

    try
    {   
        // cout << "FORMULA '" << expr << "'" <<endl;
        table.generate_table(str);
        // table.display_table();
        result = table.get_nbr_posibilities();
        // cout << "There are '" << result << "' results" <<endl;
        if (result != 0)
            return true;
        return false;
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
    }

    return false;
}
