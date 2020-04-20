#ifndef ANT_H
#define ANT_H
#include <iostream>
#include <vector>
#include "Common.h"

using namespace std;

class Ant
{
public:
    Ant(){};
    Ant(int nCities);
    vector<bool> visited;
    vector<int> path;
    double total_distance = 0;
    void showpath();
    void clone(Ant ant);
};

class Ans{
    public :
        Ant bestant;
        vector<double> resultrecord;
};
#endif


