#ifndef SA_C
#define SA_C
#include <iostream>
#include <vector>
#include<math.h>
#include "Common.h"
class SA{
    private:
        int Start_Temp;
        int End_Temp;
        double current_temp;
        bool Determination(int , int);
    public:
        double exe(int , int , int , double ,  std::vector <bool>);
};
#endif
