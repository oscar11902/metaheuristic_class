#include "HC.h"

using namespace std;

void HC::initstring(vector<bool> &bitstring)
{
    for (bool bit : bitstring)
    {
        bit = (rand() & 1) ? true : false;
    }
}
void HC::bitchange(vector<bool> &bitstring)
{
    int index = rand() % bitstring.size();
    bitstring[index] = !bitstring[index];
}

double HC::exe(vector<bool> bitstring, int runs, int iterators)
{
    double result = 0.0;
    int round = runs;
    while (round--)
    {
        initstring(bitstring);
        int time = iterators;
        int value = evaluate(bitstring);
        while (time--)
        {
            bitchange(bitstring);
            int newvalue = evaluate(bitstring);
            value = newvalue > value ? newvalue : value;
        }
        result += value;
    }
    result /= runs;
    return result;
}
