#include "Common.h"

using namespace std;

double random_ratio()
{
    return rand() / (RAND_MAX + 1.0);
}

double evaluate(vector<vector<double>> &distance_table, vector<int> &path)
{
    double total_distance = 0.0;
    int start_city, end_city;
    for (int i = 0; i < distance_table.size() - 1; i++)
    {
        start_city = path[i];
        end_city = path[i + 1];
        total_distance += distance_table[start_city][end_city];
    }
    return total_distance + distance_table[path[path.size() - 1]][path[0]];
}

void evaluateset(vector<vector<double>> &distance_table, vector<vector<int>> &geneset, vector<double> &valueset)
{
    for (int i = 0; i < valueset.size(); i++)
    {
        valueset[i] = evaluate(distance_table, geneset[i]);
    }
}

void initpath(vector<int> &path)
{
    int nCities = path.size();
    vector<bool> visited_Cities(nCities, false);
    int random_City;
    for (int i = 0; i < nCities; i++)
    {
        random_City = rand() % nCities;
        while (visited_Cities[random_City])
        {
            random_City = (random_City + 1) % nCities;
        }
        visited_Cities[random_City] = true;
        path[i] = random_City;
    }
}

vector<vector<double>> create_distance_table(vector<double> &x, vector<double> &y)
{
    vector<vector<double>> distance_table;
    int nCities = x.size();
    distance_table.resize(nCities, vector<double>(nCities));
    for (int i = 0; i < nCities; i++)
    {
        for (int j = i; j < nCities; j++)
        {
            distance_table[i][j] = pow(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2), 0.5);
            distance_table[j][i] = distance_table[i][j];
        }
    }
    return distance_table;
}

void swap(int &x, int &y)
{
    x ^= y;
    y ^= x;
    x ^= y;
}

void showpath(vector<int> &path)
{
    for (int point : path)
    {
        cout << point << " ";
    }
    cout << endl;
}

void show_distance_table(vector<vector<double>> &distance_table)
{
    for (vector<double> list : distance_table)
    {
        for (double distance : list)
        {
            printf("%-4.2f ", distance);
        }
        cout << endl;
    }
}

void city_overwirte_check(vector<int> &path)
{
    int length = path.size();
    vector<bool> check_list(length);
    for (int n : path)
    {
        if (!check_list[n])
            check_list[n] = true;
        else
        {
            cout << "path error" << endl;
            break;
        }
    }
}

void showallpath(vector<vector<int>> &pathset)
{
    for (vector<int> path : pathset)
        showpath(path);
}

int is_in_path(vector<int>&path , int &x){
    for(int i = 0 ; i < path.size() ; i++){
        if(path[i] == x)return i;
    }
    return -1;
}