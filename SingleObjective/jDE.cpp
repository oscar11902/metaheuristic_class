#include "jDE.h"

jDE::jDE(Fitness &ff, int NP, int dim, double r1 = 0.1, double r2 = 0.1, double Fl = 0.1, double Fu = 0.9)
{
    this->NP = NP;
    this->dim = dim;
    this->ff = &ff;
    this->r1 = r1;
    this->r2 = r2;
    this->Fl = Fl;
    this->Fu = Fu;
    this->upb = this->ff->getupperbound();
    this->lwb = this->ff->getlowerbound();
}

void jDE::init()
{
    x.clear();
    v.clear();
    u.clear();
    x.resize(NP);
    v.resize(NP);
    u.resize(NP);
    fitness.resize(2 * NP, 99999);
    gbest.resize(dim + 2);
    best = NULL;
    for (int i = 0; i < NP; i++)
    {
        vector<double> tmp(dim + 2);
        for (int j = 0; j < dim; j++)
        {
            tmp.push_back((upb - lwb) * random_ratio() + lwb);
        }
        //F
        tmp.push_back(Fl + random_ratio() * 0.9);
        //CR
        tmp.push_back(random_ratio());
        fitness[i] = ff->getfitness(tmp, dim);
        x.push_back(tmp);
        v.push_back(tmp);
        u.push_back(tmp);
        if (best < fitness[i] || best == NULL)
        {
            best = fitness[i];
            gbest = x[i];
        }
    }
}

void jDE::mutation()
{
    for (int i = 0; i < NP; i++)
    {
        int a, b, c;
        a = rand() % NP;
        b = rand() % NP;
        while (b == a)
            b = rand() % NP;
        c = rand() % NP;
        while (c == a || c == b)
            c = rand() % NP;
        for (int j = 0; j < dim; j++)
        {
            v[i][j] = x[a][j] - x[i][dim] * (x[b][j] - x[c][j]);
            if (v[i][j] > upb)
                v[i][j] = 2 * upb - v[i][j];
            if (v[i][j] < lwb)
                v[i][j] = 2 * lwb - v[i][j];
        }
    }
}

void jDE::crossover()
{
    for (int i = 0; i < NP; i++)
    {
        int randj = rand() % NP;
        for (int j = 0; j < dim; j++)
        {
            u[i][j] = (random_ratio() < x[i][dim + 1] || j == randj) ? v[i][j] : x[i][j];
        }
    }
}

void jDE::update()
{
    for (int i = 0; i < NP; i++)
    {
        if (random_ratio() < r1)
            x[i][dim] = Fl + random_ratio() * Fu;
        if (random_ratio() < r2)
            x[i][dim + 1] = random_ratio();
    }
}

void jDE::evaluation()
{
    for (int i = 0; i < NP; i++)
    {
        fitness[NP + i] = ff->getfitness(u[i], dim);
    }
}

void jDE::selection()
{
    for (int i = 0; i < NP; i++)
    {
        if (fitness[i] > fitness[NP + i])
        {
            x[i] = u[i];
            fitness[i] = fitness[NP + i];
            if (best > fitness[i])
            {
                best = fitness[i];
                gbest = x[i];
            }
        }
    }
}

double jDE::exec(int run = 30, int iteration = 1000)
{
    Recorder rc(iteration);
    for (int r = 0; r < run; r++)
    {
        printf("Run:%3d\n", r + 1);
        init();
        for (int i = 0; i < iteration; i++)
        {
            mutation();
            crossover();
            update();
            evaluation();
            selection();
            rc.record[i] += best;
        }
        printf("Best = %lf", best);
    }
    rc.cal_result(run);
    printf("\n\n Average Best = %lf", rc.get_result());
    return rc.get_result();
}