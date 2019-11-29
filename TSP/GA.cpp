#include "GA.h"

using namespace std;

double GA::exe(vector<vector<double>> distance_table, double mutation, double crossover, int selection_method, int crossover_method, int runs, int iterators, int population)
{
    double result = 0.0;
    int round = runs;
    this->population = population;
    this->distance_table = distance_table;
    this->mutation_rate = mutation;
    this->crossover_rate = crossover;
    this->selection_method = selection_method;

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
        distanceset.resize(nCities, 0.0);
        //cout << "INIT FINISHED" << endl;

        while (time--)
        {
            selection();
            crossover();
            mutation(mutation_rate);
            evaluateset(geneset, valueset);
        }
        for (int value : valueset)
        {
            round_result += value;
        }
        round_result /= geneset.size();
        result += round_result;
    }
    result /= run;
    return result;
}
void GA::selection_roulette()
{
    vector<double> gene_ratio;
    double sum = 0.0;
    for (int value : distanceset)
    {
        sum += value;
    }
    for (int i = 0; i < population; i++)
    {
        gene_ratio.push_back(distanceset[i] / sum);
    }
    vector<vector<bool>> new_geneset;
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
    geneset.assign(new_geneset.begin(), new_geneset.end());
}
void GA::selection_random();
void GA::crossover_PMX();
void GA::crossover_CX();
void GA::crossover_OX();
void GA::mutation()
{
    for (int i = 0; i < geneset.size(); i++)
    {
        if (random_ratio() < mutation_rate)
        {
            int point1 = rand()%nCities , point2 = rand()%nCities;
            if(point1 > point2)swap(point1 , point2);
            for(int index = 0 ; index < ((point1+point2)/2 - point1) ; index++){
                swap(geneset[point1+index] , geneset[point2-index]);
            }

        }
    }
}