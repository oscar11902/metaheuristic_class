#ifndef Com_C
#define Com_C
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

double random_ratio();
double evaluate(vector<vector<double>> &distance_table, vector<int> &path);
void initpath(vector<int> &bitstring);
void swap(int &x, int &y);
vector<vector<double>> create_distance_table(vector<double> &x, vector<double> &y);
#endif