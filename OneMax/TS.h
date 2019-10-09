#ifndef TS_C
#define TS_C
#include <iostream>
#include <vector>
#include "Common.h"
class TS{
    private:
        std::vector<std::vector <bool>> Searched_Space;
        bool vector_compare(std::vector <bool> ,std::vector <bool>);
        bool space_search(std::vector<std::vector <bool>> , std::vector <bool>);
    public:
        double exe(int , int , int , std::vector <bool>);
};
#endif