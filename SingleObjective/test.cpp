#include <iostream>
#include <vector>
#include "Common.h"
#include "FitnessFunction.h"
#include "jDE.h"
#include "Recorder.h"

using namespace std;

int main()
{
    int dim = 30 , NP =30;
    int iteration = 1000;
    Fitness *ff = new Ackley;
    Recorder rc(1000);
    jDE de(ff,NP,dim,0.1,0.1,0.1,0.9);
    de.exec(30,1000);

    return 0;
}