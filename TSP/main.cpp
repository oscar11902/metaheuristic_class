#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include "ACO.h"
#include "GA.h"
using namespace std;

int main(int argc, char *argv[])
{
    vector<bool> bitstring;
    //Common
    int runs = 30, iterators = 1000;
    double avgresult = 0.0;
    int algorithm = 0;
    int population = 20;
    double result = 0.0;
    vector<vector<double>> distance_table;
    const char *source;
    source = "test/eil51.txt";
    //ACO
    double alpha = 1, beta = 3, q = 0.9;
    vector<double> x, y;
    //GA
    int crossover_method = 0;
    int selection_method = 0;
    double mutation = 0.05;
    double crossover = 0.4;
    srand(time(NULL));
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        switch (arg[0])
        {
        case '-':
            switch (arg[1])
            {
            case 'A':
                i++;
                switch (argv[i][0])
                {
                //ACO
                case 'A':
                    algorithm = 0;
                    break;
                //GA
                case 'G':
                    algorithm = 1;
                    break;
                }
                break;
            //Common
            case 'i':
                i++;
                iterators = atoi(argv[i]);
                break;
            case 'p':
                i++;
                population = atoi(argv[i]);
                break;
            case 'r':
                i++;
                runs = atoi(argv[i]);
                break;
            case 's':
                i++;
                source = argv[i];
                break;
            //ACO
            case 'a':
                i++;
                alpha = atof(argv[i]);
                break;
            case 'b':
                i++;
                beta = atof(argv[i]);
                break;
            case 'q':
                i++;
                q = atof(argv[i]);
                break;
            //GA
            case 'C':
                i++;
                switch (argv[i][0])
                {
                //PMX
                case 'P':
                    crossover_method = 0;
                    break;
                //CX
                case 'C':
                    crossover_method = 1;
                    break;
                //OX
                case 'O':
                    crossover_method = 2;
                    break;
                }
                break;
            case 'S':
                i++;
                switch (argv[i][0])
                {
                //Roaling Whell
                case 'R':
                    selection_method = 0;
                    break;
                //random
                case 'E':
                    selection_method = 1;
                    break;
                }
                break;
            case 'm':
                i++;
                mutation = atof(argv[i]);
                break;
            case 'c':
                i++;
                crossover = atof(argv[i]);
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
        distance_table = create_distance_table(x, y);
        switch (algorithm)
        {
        //ACO
        case 0:
        {
            ACO aco;
            result = aco.exe(alpha, beta, x, y, runs, iterators, population, q);
        }
        break;
        //GA
        case 1:
        {
            GA ga;
            result = ga.exe(distance_table, mutation, crossover, selection_method, crossover_method, runs, iterators, population);
        }

        default:
            break;
        }
        printf("result = %.2lf\n", result);
    }
    return 0;
}