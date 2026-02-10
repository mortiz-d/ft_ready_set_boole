#ifndef KARGNAUTHMAP_HPP
#define KARGNAUTHMAP_HPP

#include "base.hpp"

class Cube {        
    public:
        set<int> columns;
        set<int> rows;

        Cube(void);
        ~Cube(void);
        void visualize();
};

class Kargnauth_Map {
    private:
        TruthTable table;
        ExpressionTree tree;
        vector<string> kmap_rows_vars;
        vector<string> kmap_cols_vars;
        vector<vector<bool>> kmap;
        vector<vector<bool>> kmap_unchecked;
        vector<Cube> validated_areas; //kargnaught

        bool find_aceptable_group(int col, int row);
        bool check_sector(int y ,int x, int y_end, int x_end, int mode);
        vector<int> detectChanges(const vector<vector<int>> gray, set<int> columns);
        string elavorate_formula(void);
        void appendVarsRPN( const vector<int>& changes, const vector<string>& vars, string& out, int& varsCount); //extension of elavorate formula :v
    public:
        Kargnauth_Map(void);
        ~Kargnauth_Map(void);

        bool generate_kmap(const string& expr);
        void print_kmap(void) const;
        string kmap_agrupations();
};

#endif