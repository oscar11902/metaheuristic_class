#include "GA.h"

using namespace std;

double GA::exe(vector<bool> bitstring, int run, int iterator, int num_gene, double mutation_rate, bool selection_method)
{
    double result = 0.0;
    int round = run;
    number_of_each_set = num_gene;
    geneset.resize(num_gene, bitstring);
    while (round--)
    {
        //Initialize
        double round_result = 0.0;
        geneset.clear();
        valueset.clear();
        int time = iterator;
        //cout << "INIT START" << endl;
        geneset.resize(num_gene, vector<bool>(bitstring.size(), false));
        for (int i = 0; i < geneset.size(); i++)
        {
            initstring(geneset[i]);
        }
        valueset.resize(num_gene);
        evaluateset(geneset, valueset);
        //cout << "INIT FINISHED" << endl;

        while (time--)
        {
            if (selection_method)
            {
                selection_roulette();
            }
            else
            {
                selection_();
            }
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
    for (int value : valueset)
    {
        sum += value;
    }
    for (int i = 0; i < valueset.size(); i++)
    {
        gene_ratio.push_back(valueset[i] / sum);
    }
    vector<vector<bool>> new_geneset;
    for (int i = 0; i < number_of_each_set; i++)
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
void GA::selection_()
{
    vector<vector<bool>> new_geneset;
    for (int i = 0; i < number_of_each_set; i++)
    {
        int max_index = -1;
        int max_value = -1;
        vector<bool> check_point(number_of_each_set, false);
        for (int j = 0; j < 3; j++)
        {
            int index = random() % number_of_each_set;
            while (check_point[index])
            {
                index = random() % number_of_each_set;
            }
            check_point[index] = true;
            if(max_value < valueset[index]){
                max_value = valueset[index];
                max_index = index;
            }
        }
        new_geneset.push_back(geneset[max_index]);
    }
    geneset.clear();
    geneset.assign(new_geneset.begin(), new_geneset.end());
}
void GA::mutation(double mutation_rate)
{
    for (int i = 0; i < geneset.size(); i++)
    {
        if (random_ratio() < mutation_rate)
        {
            int index = rand() % geneset[i].size();
            geneset[i][index] = !geneset[i][index];
        }
    }
}
void GA::crossover()
{
    for (int i = 0; i < geneset.size(); i += 2)
    {
        //cout << geneset[i].size() <<" " << geneset[i+1].size() << " ";
        int flag = rand() % geneset[i].size();
        for (int j = flag; j < geneset[i].size(); j++)
        {
            bool tmp = geneset[i][j];
            geneset[i][j] = geneset[i + 1][j];
            geneset[i + 1][j] = tmp;
        }
    }
}