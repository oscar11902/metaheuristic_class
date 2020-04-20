#include "PSO.h"

PSO::PSO(int nParticle, double w, double c1, double c2, vector<vector<double>> distance_table, int nAnts ,int m)
{
    this->nParticle = nParticle;
    this->nAnts = nAnts;
    this->m = m;
    this->w = w;
    this->c1 = c1;
    this->c2 = c2;
    this->distance_table = distance_table;
    answer.bestant.total_distance = 999999999999.9;
}

Ans PSO::exe(int Run, int Iteration_PSO, int Iteration_ACO)
{
    this->Run = Run;
    vector<double> resultrecord(Iteration_PSO, 0.0);
    for (int r = 0; r < Run; r++)
    {
        bestant = Ant(distance_table.size());
        bestant.total_distance = 999999999999.9;
        position.resize(nParticle, vector<double>(3));
        for (int i = 0; i < nParticle; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                position[i][k] = random_ratio() * 10;
            }
        }
        bestposition.resize(nParticle, vector<double>(3, 0.0));
        velocity.resize(nParticle, vector<double>(3, 0.0));
        aco.resize(nParticle, ACO(distance_table, nAnts ,m));
        particlebest.resize(nParticle, 99999999.9);

        evaluation(Iteration_ACO);

        for (int i = 0; i < Iteration_PSO; i++)
        {
            move();
            evaluation(Iteration_ACO);
            //    if (i % 10 == 0)
            //       cout << endl;
            //    cout << bestant.total_distance << '\t';
            resultrecord[i] += bestant.total_distance;
            //   cout << (i+1)*Iteration_ACO << ". " << bestant.total_distance << endl;
        }
        /*
        cout << endl;
        showpath(bestant.path);
        showpath(bestant.visited);
        cout << globalbest[0] << ' ' << globalbest[1] << ' ' << globalbest[2] << endl; 
        */
        if (answer.bestant.total_distance > bestant.total_distance)
        {
            answer.bestant.clone(bestant);
        }

        bestant = NULL;
        position.clear();
        bestposition.clear();
        velocity.clear();
        aco.clear();
        particlebest.clear();
    }
    for (int i = 0; i < Iteration_PSO; i++)
    {
        resultrecord[i] /= Run;
    }
    answer.resultrecord = resultrecord;
    return answer;
}

void PSO::evaluation(int Iteration_ACO)
{
    Ant tmpant;
    for (int i = 0; i < nParticle; i++)
    {
        tmpant = aco[i].exe(position[i][0], position[i][1], Iteration_ACO, 0.9);
        //tmpant = aco[i].exe(4, 4, Iteration_ACO, 0.9);
        if (tmpant.total_distance < particlebest[i])
        {
            for (int k = 0; k < 3; k++)
            {
                bestposition[i][k] = position[i][k];
            }
            particlebest[i] = tmpant.total_distance;

            if (tmpant.total_distance < bestant.total_distance)
            {
                bestant.clone(tmpant);
                globalbest = position[i];
            }
        }
    }
    for(int i = 0 ; i < nParticle ; i++){
        
    }
}

void PSO::move()
{
    for (int i = 0; i < nParticle; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            velocity[i][k] = w * velocity[i][k] + c1 * random_ratio() * (bestposition[i][k] - position[i][k]) + c2 * random_ratio() * (globalbest[k] - position[i][k]);
        }
        for (int k = 0; k < 3; k++)
        {
            position[i][k] += velocity[i][k];
            if (position[i][k] >= 10)
                position[i][k] = 10;
            if (position[i][k] <= 1)
                position[i][k] = 1;
        }
    }
}