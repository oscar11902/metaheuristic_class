#include "GA.h"

using namespace std;

double GA::exe(vector<vector<double>> distance_table, double mutation_rate, double crossover, int selection_method, int crossover_method, int runs, int iterators, int population)
{
    cout << "Into GA" << endl;
    double result = 0.0;
    int round = runs;
    this->population = population;
    this->distance_table = distance_table;
    this->mutation_rate = mutation_rate;
    this->crossover_rate = crossover;
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
        cout << "INIT FINISHED" << endl;

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
            cout << "SELECTION FINISHED" << endl;
            showpath(geneset[0]);
            switch (crossover_method)
            {
            case 0:
                crossover_PMX();
                break;
            case 1:
                crossover_CX();
                break;
            case 2:
                crossover_OX();
                break;
            }

            cout << "CROSSOVER FINISHED" << endl;
            showpath(geneset[0]);
            mutation();
            cout << "MUTATION FINISHED" << endl;
            showpath(geneset[0]);
            evaluateset(distance_table, geneset, distanceset);
            cout << "EVALUEATION FINISHED" << endl;
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
        sum += 1 / value;
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
    cout << "INTO SELECTION" << endl;
    vector<vector<int>> new_geneset;
    for (int i = 0; i < population; i++)
    {
        int min_index = -1;
        int min_value = INT32_MAX;
        cout << "BAD ALLOC" << endl;
        vector<bool> check_point(nCities, false);
        for (int j = 0; j < 3; j++)
        {
            int index = random() % nCities;
            while (check_point[index])
            {
                index = random() % nCities;
            }
            check_point[index] = true;
            if (min_value > distanceset[index])
            {
                min_value = distanceset[index];
                min_value = index;
            }
        }
        new_geneset.push_back(geneset[min_index]);
    }
    geneset.clear();
    geneset = new_geneset;
    cout << "GET OUT FROM SELECTION" << endl;
}
void GA::crossover_PMX()
{
    for (int i = 0; i < geneset.size(); i += 2)
    {
        if (random_ratio() < crossover_rate)
        {
            //隨機產生兩個位置
            int point1 = rand() % nCities, point2 = rand() % nCities;
            //排序
            cout << point1 << " " << point2 <<endl;
            if (point1 > point2)
                swap(point1, point2);
            cout << point1 << " " << point2 <<endl;
            vector<int> tmp1, tmp2;
            //紀錄需要對調的城市
            for (int index = point1; index <= point2; index++)
            {
                tmp1.push_back(geneset[i][index]);
                tmp2.push_back(geneset[i + 1][index]);
                swap(geneset[i][index], geneset[i + 1][index]);
            }
            //記錄城市的連結
            vector<int> number_position(nCities, -1);
            vector<vector<int>> linked_list;
            for (int i = 0; i < tmp1.size(); i++)
            {
                int key = tmp1[i];
                int index = i;
                vector<int> tmp_list;
                while (number_position[key] == -1)
                {
                    tmp_list.push_back(key);
                    number_position[key] = linked_list.size();
                    key = tmp2[index];
                    for (int i = 0; i < tmp1.size(); i++)
                    {
                        if (key == tmp1[i])
                        {
                            index = i;
                            break;
                        }
                    }
                }
                linked_list.push_back(tmp_list);
                tmp_list.clear();
            }
            //更換重複的
            for (int index = point2 + 1; index < nCities + point1; index++)
            {
                int key = geneset[i][index % nCities];
                int list_index = number_position[key];
                if (list_index != -1)
                {
                    int list_length = linked_list[list_index].size();
                    for (int j = 0; j < list_length; j++)
                    {
                        if (linked_list[list_index][j] == key)
                        {
                            geneset[i][index % nCities] = linked_list[list_index][(j + 1) % list_length];
                        }
                    }
                }
            }
            for (int index = point2 + 1; index < nCities + point1; index++)
            {
                int key = geneset[i + 1][index % nCities];
                int list_index = number_position[key];
                if (list_index != -1)
                {
                    int list_length = linked_list[list_index].size();
                    for (int j = 0; j < list_length; j++)
                    {
                        if (linked_list[list_index][j] == key)
                        {
                            geneset[i + 1][index % nCities] = linked_list[list_index][(j + 1) % list_length];
                        }
                    }
                }
            }
        }
    }
}
void GA::crossover_CX()
{
    for (int i = 0; i < geneset.size(); i += 2)
    {
        if (random_ratio() < crossover_rate)
        {
            int point1 = rand() % nCities, point2 = rand() % nCities;
            if (point1 > point2)
                swap(point1, point2);
            vector<int> tmp1, tmp2;
            for (int index = point1; index <= point2; index++)
            {
                tmp1.push_back(geneset[i][index]);
                tmp2.push_back(geneset[i + 1][index]);
            }
        }
    }
}
void GA::crossover_OX()
{
    for (int i = 0; i < geneset.size(); i += 2)
    {
        if (random_ratio() < crossover_rate)
        {
            int point1 = rand() % nCities, point2 = rand() % nCities;
            if (point1 > point2)
                swap(point1, point2);
            vector<int> tmp1, tmp2;
            for (int index = point1; index <= point2; index++)
            {
                tmp1.push_back(geneset[i][index]);
                tmp2.push_back(geneset[i + 1][index]);
            }
        }
    }
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
            for (int index = 0; index < ((point1 + point2) / 2 - point1); index++)
            {
                swap(geneset[point1 + index], geneset[point2 - index]);
            }
        }
    }
}