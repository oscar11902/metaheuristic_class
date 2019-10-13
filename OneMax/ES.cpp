#include "ES.h"

using namespace std;

double ES::exe(vector<bool> bitstring, int time, bool timeout)
{
    int max = 0;
    int length = bitstring.size();
    clock_t start = clock();
    while (max < length)
    {
        int i = 0;
        while (1)
        {
            if (timeout)
            {
                double execute = (clock() - start) / CLOCKS_PER_SEC;
                if (time < execute)
                    return max;
            }
            if (bitstring[i])
            {
                bitstring[i] = false;
                i++;
            }
            else
            {
                bitstring[i] = true;
                break;
            }
            
        }
        int newvalue = evaluate(bitstring);
        max = max < newvalue ? newvalue : max;
    }
    return max;
}