#include "FitnessFunction.h"

double Ackley::getfitness(vector<double> array, int dim)
{
    double alpha = 0;
    for (int i = 0; i < dim; i++)
    {
        alpha += array[i] * array[i];
    }
    alpha /= dim;

    double beta = 0;
    for(int i = 0; i < dim; i++){
        beta += cos(2 * M_PI * array[i]);
    } 
    beta/=dim;

    return -20 * exp(-0.2 * sqrt(alpha)) - exp(beta) + 20 + exp(1);
}

int Ackley::getrealdim(int dim)
{
    return dim;
}

Ackley::Ackley()
{
    upperbound = 32.768;
    lowerbound = -32.768;
}