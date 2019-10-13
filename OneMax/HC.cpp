#include "HC.h"
#include "Common.h"

using namespace std;

double HC::exe(vector<bool> bitstring, int runs, int iterators)
{
    double result = 0.0;
    int round = runs;
    while (round--)
    {
        //Initialize
        initstring(bitstring);
        int time = iterators;
        int value = evaluate(bitstring);
        while (time--)
        {
            //Transfer
            vector<bool> tmpstring;
            clonestring(tmpstring, bitstring);
            bitchange(tmpstring);
            //Evalueate
            int newvalue = evaluate(tmpstring);
            //Determine
            if (newvalue > value)
            {
                value = newvalue;
                clonestring(bitstring, tmpstring);
            }
        }
        result += value;
    }
    result /= runs;
    return result;
}
