#include "ACO.h"

double ACO::exe(double alpha, double beta, vector<double> x, vector<double> y, int run, int iteration, int nant, double q)
{
    //initialize
    ALPHA = alpha;
    BETA = beta;
    Q = q;
    nCities = x.size();
    nAnts = nant;
    double result = 0.0;
    create_distance_table(x, y);
    //show_distance_table();
    for (int r = 0; r < run; r++)
    {
        pheromone_table.resize(nCities, vector<double>(nCities, 0.1));
        prefer_table.resize(nCities, vector<double>(nCities));
        double min = 9999999.9;
        Ant bestAnt;
        for (int i = 0; i < iteration; i++)
        {

            ants.resize(nant, Ant(nCities));
            update_prefer_table();
            release_ant();
            update_pheromone_table();
            for (int a = 0; a < nant; a++)
            {
                //ants[a].showpath();
                if (min > ants[a].total_distance)
                {
                    min = ants[a].total_distance;
                    bestAnt.clone(ants[a]);
                }
            }
            ants.clear();
            //cout << min << endl;
            //bestAnt.showpath();
        }
        result += min;
        cout << "No.\t" << r + 1 << " Round:\t" << min << endl;
        pheromone_table.clear();
    }
    return result / run;
}
void ACO::create_distance_table(vector<double> x, vector<double> y)
{
    distance_table.resize(nCities, vector<double>(nCities, 0.0));
    for (int i = 0; i < nCities; i++)
    {
        for (int j = 0; j < nCities; j++)
        {
            distance_table[i][j] = pow(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2),0.5);
            distance_table[j][i] = distance_table[i][j];
        }
    }
}
void ACO::update_prefer_table()
{
    for (int i = 0; i < nCities; i++)
    {
        for (int j = 0; j < nCities; j++)
        {
            prefer_table[i][j] = pow(pheromone_table[i][j], ALPHA) * pow(distance_table[i][j], BETA);
            prefer_table[j][i] = prefer_table[i][j];
        }
    }
}
void ACO::release_ant()
{
    for (int a = 0; a < nAnts; a++)
    {

        int Start = random() % nCities;
        ants[a].path.push_back(Start);
        ants[a].visited[Start] = true;
        for (int i = 1; i < nCities; i++)
        {
            int next_point;
            next_point = select_next_city(ants[a]);
            ants[a].path.push_back(next_point);
            ants[a].visited[next_point] = true;
            ants[a].total_distance += distance_table[Start][next_point];
            Start = next_point;
        }
        ants[a].total_distance += distance_table[ants[a].path[nCities - 1]][ants[a].path[0]];
    }
}
void ACO::update_pheromone_table()
{
    for (int i = 0; i < nCities; i++)
    {
        for (int j = 0; j < nCities; j++)
        {
            pheromone_table[i][j] *= Q;
        }
    }
    for (int i = 0; i < nAnts; i++)
    {
        double delta_r = 200 / ants[i].total_distance;
        for (int j = 0; j < nCities; j++)
        {
            int indexS = ants[i].path[j], indexE = ants[i].path[(j + 1) % nCities];
            pheromone_table[indexS][indexE] += delta_r;
            pheromone_table[indexE][indexS] += delta_r;
        }
    }
}
int ACO::select_next_city(Ant ant)
{
    //Calculate the ratio of city that hasn't been visited
    double sum = 0.0;
    int start_point = ant.path[ant.path.size() - 1];
    for (int j = 0; j < nCities; j++)
    {
        if (ant.visited[j])
            continue;
        sum += prefer_table[start_point][j];
    }
    vector<double> ratio;
    for (int j = 0; j < nCities; j++)
    {
        if (ant.visited[j])
            ratio.push_back(0);
        else
            ratio.push_back(prefer_table[start_point][j] / sum);
    }
    //Select the next city
    double flag = random_ratio();
    for (int j = 0; j < nCities; j++)
    {
        if (!ant.visited[j])
        {
            flag -= ratio[j];
            if (flag < 0)
                return j;
        }
    }
}

void ACO::show_distance_table()
{
    for (vector<double> list : distance_table)
    {
        for (double distance : list)
        {
            printf("%-4.2f ",distance);
        }
        cout << endl;
    }
}

Ant::Ant(int nCities)
{
    visited.resize(nCities, false);
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
    path.clear();
    path.assign(ant.path.begin(), ant.path.end());
}