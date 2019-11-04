#ifndef ACO_H
#define ACO_H
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <fstream>
#include "Common.h"

using namespace std;

class Ant
{
public:
    Ant(){}
    Ant(int nCities);
    vector<bool> visited;
    vector<int> path;
    double total_distance = 0;
    void showpath();
    void clone(Ant ant);
};

class ACO
{
private:
    vector<vector<double>> distance_table;
    vector<vector<double>> pheromone_table;
    vector<vector<double>> prefer_table;
    vector<double>result_record;
    vector<Ant> ants;
    double ALPHA, BETA, Q, RO;
    int nCities , nAnts;

public:
    double exe(double alpha, double beta, vector<double> x, vector<double> y, int run, int iteration, int nant , double q);
    void create_distance_table(vector<double> x, vector<double> y);
    void update_prefer_table();
    void release_ant();
    void update_pheromone_table();
    void show_distance_table();
    int select_next_city(Ant ant);
    double count_distance(vector<int> path);
};

#endif