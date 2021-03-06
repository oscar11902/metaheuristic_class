#ifndef Com_C
#define Com_C
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

double random_ratio();
double evaluate(vector<vector<double>> &distance_table, vector<int> &path);
void evaluateset(vector<vector<double>> &distance_table, vector<vector<int>> &geneset, vector<double> &valueset);
void initpath(vector<int> &bitstring);
void showallpath(vector<vector<int>> &pathset);
void showpath(vector<int> &path);
void show_distance_table(vector<vector<double>> &distance_table);
void city_overwirte_check(vector<int> &path);
int is_in_path(vector<int>&path , int &x);
void swap(int &x, int &y);
vector<vector<double>> create_distance_table(vector<double> &x, vector<double> &y);
#endif