#ifndef PSO_H
#define PSO_H
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <fstream>
#include <thread>
#include "Ant.h"
#include "ACO.h"
#include "Common.h"

using namespace std;

class PSO
{
private:
    //setting argument 
    int Run, Iteration_PSO, Iteration_ACO, nParticle , nAnts;
    vector<vector<double>> distance_table;
    vector<double> globalbest , resultrecord;
    Ant bestant;
    Ans answer;
    double w, c1, c2;

    //particle element
    vector<vector<double>> position, bestposition, velocity;
    vector<ACO> aco;
    vector<double> particlebest;

public:
    PSO(){};
    PSO(int nParticle, double w, double c1, double c2, vector<vector<double>> distance_table, int nAnts);
    Ans exe(int Run, int Iteration_PSO, int Iteration_ACO);
    void evaluation(int Iteration_ACO);
    void move();
};

#endif