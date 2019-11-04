#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include "ACO.h"
using namespace std;

int main(int argc, char *argv[])
{
    vector<bool> bitstring;
    //Common
    int runs = 30, iterators = 1000;
    double avgresult = 0.0;
    int algorithm = 0;
    double result = 0.0;
    //ACO
    int nant = 20;
    double alpha = 1, beta = 3, q = 0.9;
    vector<double> x, y;
    const char *source;
    source = "test/eil51.txt";
    srand(time(NULL));
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        switch (arg[0])
        {
        case '-':
            switch (arg[1])
            {
            //Common
            case 'a':
                i++;
                alpha = atof(argv[i]);
                break;
            case 'b':
                i++;
                beta = atof(argv[i]);
                break;
            case 'i':
                i++;
                iterators = atoi(argv[i]);
                break;
            case 'n':
                i++;
                nant = atoi(argv[i]);
                break;
            case 'q':
                i++;
                q= atof(argv[i]);
                break;
            case 'r':
                i++;
                runs = atoi(argv[i]);
                break;
            case 's':
                i++;
                source = argv[i];
                break;
            }
            break;
        default:
            break;
        }
    }
    fstream file;
    file.open(source, ios::in);
    if (!file)
    {
        cout << "No such File" << endl;
        cout << source << endl;
    }
    else
    {
        double x_buf, y_buf;
        while (file >> x_buf >> y_buf)
        {
            x.push_back(x_buf);
            y.push_back(y_buf);
        }
        file.close();
        /*
        for (int i = 0; i < x.size(); i++)
        {
            cout << x[i] << " " << y[i] << endl;
        }
        */
        switch (algorithm)
        {
        case 0:
        {
            ACO aco;
            result = aco.exe(alpha, beta, x, y, runs, iterators, nant, q);
        }

        default:
            break;
        }
        printf("result = %.2lf\n", result);
    }
    return 0;
}