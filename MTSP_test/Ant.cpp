#include "Ant.h"

Ant::Ant(int nCities)
{
    visited.resize(nCities, false);
    path.reserve(nCities);
    total_distance = 0;
}

void Ant::showpath()
{
    for (int point : path)
    {
        cout << point << " ";
    }
    cout << endl;
}

void Ant::clone(Ant ant)
{
    total_distance = ant.total_distance;
    path = ant.path;
    visited = ant.visited;
}