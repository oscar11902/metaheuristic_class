#ifndef GA_C
#define GA_C
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class GA
{
private:
    vector<vector<bool>> geneset;
    vector<int> valueset;
public:
    double exe(vector<bool> bitstring, int run, int iterator, int num_gene, double mutation_rate , bool selection_method);
    void selection_rotation();
    void selection_(); 
    void crossover();
    void mutation(double mutation_rate); 
};

#endif
