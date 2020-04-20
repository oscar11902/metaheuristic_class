#ifndef GA_C
#define GA_C
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class GA
{
private:
    vector<vector<int>> geneset;
    vector<double> distanceset;
    vector<vector<double>> distance_table;
    int population;
    int nCities;
    int selection_method;
    int crossover_method;
    double mutation_rate;
    double crossover_rate;

public:
    double exe(vector<vector<double>> distance_table, double mutation, double crossover, int selection_method, int crossover_method, int runs, int iterators, int population);
    void selection();
    void crossover();
    void mutation();
    void selection_roulette();
    void selection_random();
    vector<int> crossover_PMX(vector<int> &path1, vector<int> &path2);
    vector<int> crossover_CX(vector<int> &path1, vector<int> &path2);
    vector<int> crossover_OX(vector<int> &path1, vector<int> &path2);
};

#endif
