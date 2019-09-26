#include<iostream>
#include "Common.h"

using namespace std;

int evaluate (vector<bool> bitstring){
    int counter = 0;
    for(bool bit: bitstring){
        if(bit)counter++;
    }
    return counter;
}