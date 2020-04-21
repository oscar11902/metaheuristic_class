#ifndef FF_H
#define FF_H

#include <math.h>
#include <vector>

using namespace std;

class Fitness
{
protected:
    double upperbound;
    double lowerbound;

public:
    double getupperbound()
    {
        return upperbound;
    }

    double getlowerbound()
    {
        return lowerbound;
    }
    virtual int getrealdim(int dim) = 0;
    virtual double getfitness(vector<double> array, int dim) = 0;
};

class Ackley : public Fitness
{
public:
    Ackley();
    double getfitness(vector<double> array, int dim);
    int getrealdim(int dim);
};

#endif