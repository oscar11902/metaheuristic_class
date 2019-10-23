#include <iostream>
#include "Common.h"

using namespace std;

double random_ratio()
{
    return rand() / (RAND_MAX + 1.0);
}

int evaluate(vector<bool> bitstring)
{
    int counter = 0;
    for (bool bit : bitstring)
    {
        if (bit)
            counter++;
    }
    return counter;
}

void evaluateset(vector<vector<bool>> geneset , vector<int> &valueset){
    for(int i = 0 ; i < valueset.size() ; i++){
            valueset[i] = evaluate(geneset[i]);
        }
}

void initstring(vector<bool> &bitstring)
{
    for (int i = 0; i < bitstring.size(); i++)
    {
        bitstring[i] = (rand() & 1) ? true : false;
    }
}
void bitchange(vector<bool> &bitstring)
{
    int index = rand() % bitstring.size();
    bitstring[index] = !bitstring[index];
}

void clonestring(vector<bool> &newstring, vector<bool> orignstring)
{
    newstring.clear();
    newstring.assign(orignstring.begin(), orignstring.end());
}