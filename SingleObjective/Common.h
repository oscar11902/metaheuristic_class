#ifndef Com_C
#define Com_C
#include <vector>

using namespace std;

double random_ratio();
int evaluate(vector<bool>bitstring);
void evaluateset(vector<vector<bool>> geneset , vector<int> &valueset);
void clonestring(vector<bool>&bitstring, vector<bool>new_bitstring);
void bitchange(vector<bool>&bitstring);
void initstring(vector<bool>&bitstring);
void evaluateset(vector<vector<bool>> geneset , vector<int> &valueset);
#endif