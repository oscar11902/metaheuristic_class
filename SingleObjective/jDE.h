#ifndef jDE_H
#define jDE_H

#include <vector>
#include "FitnessFunction.h"
#include "Recorder.h"
#include "Common.h"

using namespace std;

class jDE
{
private:
    int NP, dim;
    Fitness *ff;
    vector<vector<double>> x, v, u;
    vector<double> fitness;
    vector<double> gbest;
    double best, upb, lwb, r1, r2, Fl, Fu;

public:
    jDE(Fitness &ff, Recorder &rc, int NP, int dim, double r1, double r2, double Fl, double Fu);
    void init();
    void mutation();
    void crossover();
    void evaluation();
    void update();
    void selection();
    double exec(int run , int iteration);
};

#endif