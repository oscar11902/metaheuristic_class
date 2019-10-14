#include "SA.h"
#include "Common.h"

using namespace std;

bool SA::Determination(int value, int newvalue)
{
    double delta = 0.0 - value + newvalue;
    return exp(delta / current_temp);
}

double SA::exe(int ST, int ET, int runs, double ratio, vector<bool> bitstring)
{
    double result = 0.0;
    int round = runs;
    Start_Temp = ST;
    End_Temp = ET;
    while (round--)
    {
        //Initialize
        current_temp = Start_Temp + 0.0;
        initstring(bitstring);
        int value = evaluate(bitstring);
        while (current_temp > End_Temp)
        {
            //Transfer
            vector<bool> tmpstring;
            clonestring(tmpstring, bitstring);
            bitchange(tmpstring);
            //Evalueate
            int newvalue = evaluate(tmpstring);
            //Determine
            if (random_ratio() < Determination(value, newvalue))
            {
                if (newvalue > value)
                    value = newvalue;
                clonestring(bitstring, tmpstring);
            }
            current_temp *= ratio;
            //cout << value << endl;
        }
        result += value;
    }
    result /= runs;
    return result;
}
