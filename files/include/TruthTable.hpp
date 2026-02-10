#ifndef TRUTHTABLE_HPP
#define TRUTHTABLE_HPP

#include "base.hpp"

class TruthTable {
    private:
        ExpressionTree tree;
        vector<vector<int>> _table;
        vector<string > _colum_order;
        int _n_rows;

        public:
        TruthTable(void);
        ~TruthTable(void);
        
        void generate_table(const string str);
        void display_table(void) const;
        int get_nbr_posibilities(void) const;
};


#endif