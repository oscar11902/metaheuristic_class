#include "TS.h"

using namespace std;

double TS::exe(int Array_Size, int runs, int iterators, vector<bool> bitstring)
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
            while (space_search(tmpstring))
            {
                tmpstring.clear();
                clonestring(tmpstring, bitstring);
                bitchange(tmpstring);
            }
            //Evalueate
            int newvalue = evaluate(tmpstring);
            //Determine
            if (newvalue > value)
            {
                value = newvalue;
                clonestring(bitstring, tmpstring);
            }
            else
            {
                if (Searched_Space.size() == Array_Size)
                {
                    Searched_Space.erase(Searched_Space.begin());
                }
                Searched_Space.push_back(tmpstring);
            }
        }
        result += value;
    }
    result /= runs;
    return result;
}

bool TS::vector_compare(vector<bool> vector_a, vector<bool> vector_b)
{
    for (int i = 0; i < vector_a.size(); i++)
    {

        if (vector_a[i] != vector_b[i])
        return false;
    }
    return true;
}
bool TS::space_search(vector<bool> search_target)
{
    if(search_target.size()==0)return false;
    for (int i = 0; i < Searched_Space.size(); i++)
    {
        if (vector_compare(Searched_Space[i], search_target))
        {
            return true;
        }
    }
    return false;
}