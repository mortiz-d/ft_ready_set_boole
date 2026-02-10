#ifndef BOOLE_HPP
#define BOOLE_HPP

#include "base.hpp"


set<string> obtainVariables(const string& expr);



int adder(int a, int b);
int multiplier(int a, int b);
int grey_map(int value);
int reverse_grey(int num);
string see_binary(int value);

bool        eval_formula(const string str);             //ex03
void        print_truth_table(const string str);        //ex04
string      negation_normal_form(const string str);     //ex05
string      math_simplified_formula(const string str);  //ex05 - tests
string      math_complex_formula(const string str);     //ex05 - tests
string      conjunctive_normal_form(const string str);  //ex06
bool        sat(const string str);                      //ex07
#endif