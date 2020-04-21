#ifndef RECORDER_C
#define RECORDER_C

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Recorder{
    public:
        vector<double> record;
        Recorder(int iteration);
        void to_file(string filename);
        void cal_result(int run);
        double get_result();
};


#endif