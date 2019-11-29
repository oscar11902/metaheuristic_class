#include "Common.h"

using namespace std;

double random_ratio()
{
    return rand() / (RAND_MAX + 1.0);
}

double evaluate(vector<vector<double>> &distance_table, vector<int> &path)
{
    double total_distance = 0;
    int start_city, end_city;
    for (int i = 0; i < distance_table.size() - 1; i++)
    {
        start_city = path[i];
        end_city = path[i + 1];
        total_distance += distance_table[start_city][end_city];
    }
    return total_distance + distance_table[path[path.size() - 1]][path[0]];
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
            random_City = rand() % nCities;
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