#ifndef Com_C
#define Com_C
#include <vector>
#include <iostream>

using namespace std;

double random_ratio();
int evaluate(vector<bool>bitstring);
void clonestring(vector<bool>&bitstring, vector<bool>new_bitstring);
void bitchange(vector<bool>&bitstring);
#endif