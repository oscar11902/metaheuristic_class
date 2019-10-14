#ifndef TS_C
#define TS_C
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class TS
{
private:
    vector<vector<bool>> Searched_Space;

public:
    double exe(int Array_Size, int runs, int iterator, vector<bool>bitstring);
    bool vector_compare(vector<bool>, vector<bool>);
    bool space_search(vector<bool>);
};
#endif