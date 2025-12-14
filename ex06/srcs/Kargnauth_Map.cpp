#include "boole.hpp"




Kargnauth_Map::Kargnauth_Map()
{
    return;
}

Kargnauth_Map::~Kargnauth_Map()
{
    return;
}


void Kargnauth_Map::generate_kmap(const std::string& expr)
{
    std::set<std::string> vars = obtainVariables(expr);
    std::set<std::string>::iterator it;
    std::map<std::string, bool> input;
    int gray_r,gray_c, rows,cols;

    this->table.generate_table(expr);
    this->tree.build_Simplified(expr);

    int n = vars.size();
    if (n < 2 )
    {
        std::cerr << "Needs at least 2 or more variables to deploy a kargnauth map" << std::endl;
        return;
    }

    // Divide in left & right
    this->kmap_rows_vars.clear(); //Left side of the map
    this->kmap_cols_vars.clear(); //Right side of the map

    it = vars.begin();
    for (int i = 0; i < (n / 2); i++, ++it)
        kmap_rows_vars.push_back(*it);

    for (; it != vars.end(); ++it)
        kmap_cols_vars.push_back(*it);

    rows = 1 << this->kmap_rows_vars.size();
    cols = 1 << this->kmap_cols_vars.size();

    this->kmap.assign(rows, std::vector<bool>(cols, false));
    for (int i = 0; i < rows; i++)
    {
        gray_r = grey_map(i);
        for (int j = 0; j < cols; j++)
        {
            gray_c = grey_map(j);
            input.clear();
            for (int b = 0; b < (int)kmap_rows_vars.size(); b++)
                input[kmap_rows_vars[b]] = (gray_r >> (kmap_rows_vars.size() - 1 - b)) & 1;  //We insert into the input the value of the respective letter on the left separation

            for (int b = 0; b < (int)kmap_cols_vars.size(); b++)
                input[kmap_cols_vars[b]] = (gray_c >> (kmap_cols_vars.size() - 1 - b)) & 1; //We insert into the input the value of the respective letter on the right separation

            this->kmap[i][j] = this->tree.calculate(input); //We insert the result into the kmap table
        }
    }
}



void Kargnauth_Map::print_kmap(void) const
{
    int _grey_code;
    int rows = kmap.size();
    int cols = kmap[0].size();

    std::cout << std::endl << "Kargnauth Map" << std::endl;
    std::cout << "       ";
    for (int i = 0; i < (int)this->kmap_cols_vars.size(); i++)
        std::cout << this->kmap_cols_vars[i];
    std::cout << std::endl;
    std::cout << "       ";

    for (int c = 0; c < cols; c++) {
        int gc = grey_map(c);
        for (int b = this->kmap_cols_vars.size() - 1; b >= 0; b--)
            std::cout << ((gc >> b) & 1);
        std::cout << " ";
    }
    std::cout << std::endl;

    for (int r = 0; r < rows; r++) {
        for (int i = 0; i < (int)this->kmap_rows_vars.size(); i++)
            std::cout << this->kmap_rows_vars[i];

        _grey_code = grey_map(r);
        std::cout << " ";
        for (int b = this->kmap_rows_vars.size() - 1; b >= 0; b--)
            std::cout << ((_grey_code >> b) & 1);
        std::cout << " | ";

        for (int c = 0; c < cols; c++)
            std::cout << this->kmap[r][c] << "   ";
        std::cout << std::endl;
    }
}

//THIS NEEDS STILL SOME WORK TO DO
bool Kargnauth_Map::check_sector(int y ,int x, int y_end, int x_end, int mode)
{
    int x_start = 0, y_start = 0;
    Cube area;


    while (y_start < y_end)
    {
        if (y+y_start >= (int)this->kmap.size() )
        {
                // std::cout << "Wrap around y" << std::endl;
                y -= this->kmap.size();
        }
        
        while (x_start < x_end)
        {
            if (x+x_start >= (int)this->kmap[0].size() )
            {
                // std::cout << "Wrap around x" << std::endl;
                x -= this->kmap[0].size();

            }
            // std::cout << "Compruebo"<< y+y_start << x+x_start << "->" << this->kmap[y+y_start][x+x_start] << std::endl;
            if (mode)
            {
                this->kmap_unchecked[y+y_start][x+x_start] = false;
                area.columns.insert(y+y_start);
                area.rows.insert(x+x_start);
            }
            if (this->kmap[y+y_start][x+x_start] == false)
                return false;
            x_start++;
        }
        x_start = 0;
        y_start++;
    }

    if (mode)
    {
        this->validated_areas.push_back(area);
        // std::cout << "Added arena" << std::endl;
    }

    
    return true;
}

//THIS NEEDS STILL SOME WORK TO DO 
//(NEEDS TO PRIORITICE WHAT TO CHECK FIRST)
bool Kargnauth_Map::find_aceptable_group (int col, int row)
{ 
    size_t size_rows = this->kmap.size();
    size_t size_cols = this->kmap[0].size();
    int n_max_casillas = size_rows * size_cols;
    int x_size, y_size;
    int group_size = 2;
    std::stack<int> group_sizes;

    for (int i = 1; i < n_max_casillas; i= i * 2)
    group_sizes.push(i);
    while (group_size > 1)
    {
        group_size = group_sizes.top();
        group_sizes.pop();
        // std::cout << "Agrupando de " << group_size << " en " << group_size << std::endl; 
        x_size = group_size;
        y_size = 1;
        while (y_size <= group_size)
        {
            // std::cout << "Prueba de y: " << col << " x: " << row  << " a y:" << y_size << " x: " << x_size << std::endl;
            if (check_sector(col,row,y_size,x_size, 0))
            {
                // std::cout << "Prueba de y: " << col << " x: " << row  << " a y:" << y_size << " x: " << x_size << " es buena" << std::endl;
                // std::cout << "La prueba es buena!" << std::endl;
                check_sector(col,row,y_size,x_size, 1);
                // this->kmap_unchecked[col][row] = false;
                return true;
            }
            // else
                // std::cout << "La prueba es mala!" << std::endl;
            // check_sector(col,row,y_size,x_size);
            y_size = y_size * 2;
            x_size = x_size / 2;
        }
    }

    return true;
}


std::string Kargnauth_Map::kmap_to_formula_2()
{
    size_t size_rows = this->kmap.size();
    size_t size_cols = this->kmap[0].size();
    this->kmap_unchecked = this->kmap;   

    // std::cout << "Tamaño:" << this->kmap_unchecked.size() << " & " << this->kmap_unchecked[0].size() << std::endl;

    for (size_t i = 0; i < size_rows; i++)
    {
        for (size_t j = 0; j < size_cols; j++)
        {
            if ( this->kmap[i][j] == true && this->kmap_unchecked[i][j] == true) //CHECK IF that hold is not being checked
                find_aceptable_group(i,j);
        }
    }
    this->elavorate_formula();
    return "";
}
  



std::vector<std::vector<int>> generateGrayCode(int amount_variables) {
    int mask ,code ;
    int size = 1 << amount_variables;  // 2^n
    std::vector<std::vector<int>> gray(size, std::vector<int>(amount_variables));

    for (int i = 0; i < size; i++) {
        code = grey_map(i);

        for (int bit = 0; bit < amount_variables; bit++) {
            mask = 1 << (amount_variables - 1 - bit);
            if ((code & mask))
                gray[i][bit] = 1;
            else
                gray[i][bit] = 0;
        }
    }
    return gray;
}

std::vector<int> Kargnauth_Map::detectChanges(const std::vector<std::vector<int>> gray, std::set<int> columns) {
    bool same;
    int n = gray[0].size();
    std::vector<int> result(n, 2);  // 0=fixed as negative, 1=fixed as positive 1, 2=changes/not what we want
    int firstBit;
    int firstIndex = *columns.begin();

    for (int var = 0; var < n; var++) {
        firstBit = gray[firstIndex][var];
        same = true;

        for (int idx : columns) {
            if (gray[idx][var] != firstBit) {
                same = false;
                break;
            }
        }

        if (same) 
            result[var] = firstBit;
        else      
            result[var] = 2; // don't care
    }

    return result;
}


void Kargnauth_Map::elavorate_formula()
{
    std::vector<std::vector<int>> aux_left, aux_right;
    std::vector<int> result;
    std::string formula = " ";
    std::string aux;

    aux_left  = generateGrayCode(kmap_rows_vars.size());
    aux_right = generateGrayCode(kmap_cols_vars.size());

    for (size_t x = 0; x < validated_areas.size(); x++) {
        
        if (x != 0)
            formula += " + ";
        aux = "";
        if (DEBUG)
            this->validated_areas[x].visualize();
        result = detectChanges(aux_left,this->validated_areas[x].columns);
        for (size_t i = 0; i < result.size(); i++) {
            if (DEBUG)
            {
                if (result[i] == 0) 
                    std::cout << "Var " << kmap_rows_vars[i] << " = 0" << std::endl;
                else if (result[i] == 1) 
                    std::cout << "Var " << kmap_rows_vars[i] << " = 1" << std::endl;
                else 
                    std::cout << "Var " << kmap_rows_vars[i] << " = don't care" << std::endl;
            }

            if (result[i] == 2) 
                continue;
            aux += kmap_rows_vars[i];
            if (result[i] == 0) 
                aux += " ! " ;
        }
        result = detectChanges(aux_right,this->validated_areas[x].rows);
        for (size_t i = 0; i < result.size(); i++) {
            if (DEBUG)
            {
                if (result[i] == 0) 
                    std::cout << "Var " << kmap_cols_vars[i] << " = 0" << std::endl;
                else if (result[i] == 1) 
                    std::cout << "Var " << kmap_cols_vars[i] << " = 1" << std::endl;
                else 
                    std::cout << "Var " << kmap_cols_vars[i] << " = don't care" << std::endl;
            }

            if (result[i] == 2) 
                continue;
            aux += kmap_cols_vars[i];
            if (result[i] == 0) 
                aux += " ! " ;
        }

        formula += aux;
    }

    std::cout << " Formula Original :  "<< tree.printInOrderMath() << std::endl;
    std::cout << " Formula Simple :  "<< formula << std::endl;
        
}