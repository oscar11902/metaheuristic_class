#ifndef HC_C
#define HC_C
#include <iostream>
#include <vector>
#include "Common.h"

class HC
{
private:
    void initstring(std::vector<bool> &);
    void bitchange(std::vector<bool> &);

public:
    double exe(std::vector<bool> , int ,int);
};

#endif
