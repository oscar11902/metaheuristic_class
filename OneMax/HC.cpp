#include "HC.h"

using namespace std;

void HC::initstring(vector<bool> &bitstring)
{
    for (int i = 0 ; i < bitstring.size() ; i++)
    {
        bitstring[i] = (rand() & 1) ? true : false;
    }
}
void HC::bitchange(vector<bool> &bitstring)
{
    int index = rand() % bitstring.size();
    bitstring[index] = !bitstring[index];
}

void HC::clonestring(vector<bool> &newstring, vector<bool> orignstring)
{
    newstring.clear();
    newstring.assign(orignstring.begin(), orignstring.end());
}

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
