#include "GA.h"

using namespace std;

double GA::exe(vector<vector<double>> distance_table, double mutation_rate, double crossover_rate, int selection_method, int crossover_method, int runs, int iterators, int population)
{
    //cout << "Into GA" << endl;
    double result = 0.0;
    int round = runs;
    this->population = population;
    this->distance_table = distance_table;
    this->mutation_rate = mutation_rate;
    this->crossover_rate = crossover_rate;
    this->selection_method = selection_method;
    this->crossover_method = crossover_method;

    nCities = distance_table.size();
    while (round--)
    {
        //Initialize
        double round_result = 0.0;
        geneset.clear();
        distanceset.clear();
        geneset.resize(population, vector<int>(nCities, 0));
        int time = iterators;
        //cout << "INIT START" << endl;
        for (int i = 0; i < geneset.size(); i++)
        {
            initpath(geneset[i]);
        }
        distanceset.resize(population, 0.0);
        evaluateset(distance_table, geneset, distanceset);
        //cout << "INIT FINISHED" << endl;

        while (time--)
        {
            switch (selection_method)
            {
            case 0:
                selection_roulette();
                break;
            case 1:
                selection_random();
                break;
            }
            crossover();
            mutation();
            evaluateset(distance_table, geneset, distanceset);
        }

        for (double value : distanceset)
        {
            round_result += value;
        }

        round_result /= geneset.size();
        result += round_result;
    }
    result /= runs;
    return result;
}
void GA::selection_roulette()
{
    vector<double> gene_ratio;
    double sum = 0.0;
    for (double value : distanceset)
    {
        sum += (1 / value);
    }
    for (int i = 0; i < population; i++)
    {
        gene_ratio.push_back((1 / distanceset[i]) / sum);
    }
    vector<vector<int>> new_geneset;
    for (int i = 0; i < population; i++)
    {
        double flag = random_ratio();
        for (int j = 0; j < geneset.size(); j++)
        {
            flag -= gene_ratio[j];
            if (flag < 0)
            {
                new_geneset.push_back(geneset[j]);
                break;
            }
        }
    }
    geneset.clear();
    geneset = new_geneset;
}
void GA::selection_random()
{
    vector<vector<int>> new_geneset;
    for (int i = 0; i < population; i++)
    {
        int min_index = -1;
        int min_value = INT32_MAX;
        vector<bool> check_point(population, false);
        for (int j = 0; j < 3; j++)
        {
            int index = rand() % population;
            while (check_point[index])
            {
                index = rand() % population;
            }
            check_point[index] = true;
            if (min_value > distanceset[index])
            {
                min_value = distanceset[index];
                min_index = index;
            }
        }
        new_geneset.push_back(geneset[min_index]);
    }
    geneset.clear();
    geneset = new_geneset;
}

void GA::crossover()
{

    for (int i = 0; i < geneset.size(); i += 2)
    {
        if (random_ratio() < crossover_rate)
        {
            vector<int> tmp1, tmp2;
            switch (crossover_method)
            {
            case 0:
                tmp1 = crossover_PMX(geneset[i], geneset[i + 1]);
                tmp2 = crossover_PMX(geneset[i + 1], geneset[i]);
                break;
            case 1:
                tmp1 = crossover_CX(geneset[i], geneset[i + 1]);
                tmp2 = crossover_CX(geneset[i + 1], geneset[i]);
                break;
            case 2:
                tmp1 = crossover_OX(geneset[i], geneset[i + 1]);
                tmp2 = crossover_OX(geneset[i + 1], geneset[i]);
                break;
            }
            geneset[i] = tmp1;
            geneset[i + 1] = tmp2;
        }
    }
}

vector<int> GA::crossover_PMX(vector<int> &path1, vector<int> &path2)
{
    vector<int> child(nCities, -1);
    int point1 = rand() % nCities, point2 = rand() % nCities;
    if (point1 > point2)
        swap(point1, point2);
    for (int index = point1; index < point2; index++)
    {
        child[index] = path1[index];
    }
    for (int index = point1; index < point2; index++)
    {
        int V = path2[index];
        int V_index_in_child = -1;
        int index_in_path2 = -1;
        //尋找path2在範圍內是否有不在child中的值
        V_index_in_child = is_in_path(child, V);
        if (V_index_in_child == -1)
        {
            index_in_path2 = is_in_path(path2, path1[index]);
            while (point1 <= index_in_path2 && index_in_path2 < point2)
            {
                index_in_path2 = is_in_path(path2, path1[index_in_path2]);
            }
            child[index_in_path2] = V;
        }
    }
    for (int i = 0; i < nCities; i++)
    {
        if (child[i] == -1)
            child[i] = path2[i];
    }
    return child;
}
vector<int> GA::crossover_CX(vector<int> &path1, vector<int> &path2)
{
    vector<int> child(nCities, -1);
    int index = rand() % nCities;
    while (is_in_path(child, path1[index]) == -1)
    {
        child[index] = path2[index];
        index = is_in_path(path1, child[index]);
    }
    int key = 0;
    for (int i = 0; i < nCities; i++)
    {
        if (is_in_path(child, path2[i]) == -1)
        {
            for (int j = key; j < nCities; j++)
            {
                if (child[j] == -1)
                {
                    child[j] = path2[i];
                    key = j+1;
                    break;
                }
            }
        }
    }
    return child;
}
vector<int> GA::crossover_OX(vector<int> &path1, vector<int> &path2)
{
    vector<int> child(nCities, -1);
    int point1 = rand() % nCities, point2 = rand() % nCities;
    if (point1 > point2)
        swap(point1, point2);
    for (int index = point1; index < point2; index++)
    {
        child[index] = path1[index];
    }
    int key = 0;
    for (int i = 0; i < nCities; i++)
    {
        if (is_in_path(child, path2[i]) == -1)
        {
            for (int j = key; j < nCities; j++)
            {
                if (child[j] == -1)
                {
                    child[j] = path2[i];
                    key++;
                    break;
                }
            }
        }
    }
    return child;
}
void GA::mutation()
{
    for (int i = 0; i < geneset.size(); i++)
    {
        if (random_ratio() < mutation_rate)
        {
            int point1 = rand() % nCities, point2 = rand() % nCities;
            if (point1 > point2)
                swap(point1, point2);
            for (int index = 0; index < ((point2 - point1) / 2); index++)
            {
                swap(geneset[i][point1 + index], geneset[i][point2 - index]);
            }
        }
    }
}