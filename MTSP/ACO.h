#ifndef ACO_H
#define ACO_H
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <fstream>
#include "Ant.h"
#include "Common.h"

using namespace std;


class ACO
{
private:
    vector<vector<double>> distance_table;
    vector<vector<double>> pheromone_table;
    vector<vector<double>> prefer_table;
    vector<double> result_record;
    vector<Ant> ants;
    Ant BestAnt;
    double ALPHA, BETA, Q, RO;
    int nCities, nAnts;

public:
    ACO(){};
    ACO(vector<vector<double>> distance_table, int nAnts);
    Ant exe(double alpha, double beta, int iteration, double q);
    void update_prefer_table();
    void release_ant();
    void update_pheromone_table();
    void show_distance_table();
    int select_next_city(Ant &ant);
    double count_distance(vector<int> path);
};

#endif