#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include "PSO.h"
using namespace std;

int main(int argc, char *argv[])
{
    //Common
    int Run = 30;
    int Algorithm = 0;
    int Population = 20;
    int m = 3;
    double result = 0.0;
    Ans answer;
    vector<vector<double>> distance_table;
    const char *source;
    source = "test/eil51.txt";
    //PSO
    int Iteration_PSO = 100;
    double w = 0.2, c1 = 0.3, c2 = 0.5;
    vector<double> x, y;
    //ACO
    int Iteration_ACO = 10;
    int nAnts = 20;

    srand(time(NULL));
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        switch (arg[0])
        {
        case '-':
            switch (arg[1])
            {
            //Algorithm
            case 'A':
                i++;
                switch (argv[i][0])
                {
                //PSO
                case 'P':
                    Algorithm = 0;
                    break;
                }
                break;
            //Common
            case 'p':
                i++;
                Population = atoi(argv[i]);
                break;
            case 'r':
                i++;
                Run = atoi(argv[i]);
                break;
            case 's':
                i++;
                source = argv[i];
                break;
            case 'm':
                i++;
                m = atoi(argv[i]);
                break;

            //PSO
            case 'i':
                i++;
                Iteration_PSO = atoi(argv[i]);
                break;
            case 'c':
                i++;
                c1 = atof(argv[i]);
                i++;
                c2 = atof(argv[i]);
                break;
            //ACO
            case 'I':
                i++;
                Iteration_ACO = atoi(argv[i]);
                break;
            case 'n':
                i++;
                nAnts = atoi(argv[i]);
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
        file >> x_buf >> y_buf;
        for (int i = 0; i < m; i++)
        {
            x.push_back(x_buf);
            y.push_back(y_buf);
        }

        while (file >> x_buf >> y_buf)
        {
            x.push_back(x_buf);
            y.push_back(y_buf);
        }
        file.close();
        distance_table = create_distance_table(x, y);
        switch (Algorithm)
        {
        //PSO
        case 0:
        {
            PSO pso = PSO(Population, w, c1, c2, distance_table, nAnts , m);
            answer = pso.exe(Run, Iteration_PSO, Iteration_ACO);
        }
        break;
        default:
            break;
        }
        cout << "Result Writing" << endl;
        fstream file;
        string buffer;
        string filename = "Output/Result_M_" + to_string(m) + "_ACO_" + to_string(Iteration_ACO) + "_PSO_" + to_string(Iteration_PSO) + ".txt";
        file.open(filename, ios::out);
        for (int i = 0; i < Iteration_PSO; i++)
        {
            for (int j = 0; j < Iteration_ACO; j++)
            {
                buffer = to_string(i * Iteration_ACO + (j + 1)) + "\t" + to_string(answer.resultrecord[i]) + "\n";
                file << buffer;
            }
        }
        file.close();

        cout << "Path Writing" << endl;

        filename = "Output/Path_M_" + to_string(m) + "_ACO_" + to_string(Iteration_ACO) + "_PSO_" + to_string(Iteration_PSO) + ".txt";
        file.open(filename, ios::out);
        for (int i = 0; i < x.size(); i++)
        {
            buffer = to_string(x[answer.bestant.path[i]]) + "\t" + to_string(y[answer.bestant.path[i]]) + "\n";
            file << buffer;
        }
        buffer = to_string(x[answer.bestant.path[0]]) + "\t" + to_string(y[answer.bestant.path[0]]) + "\n";
        file << buffer;
        file.close();

        showpath(answer.bestant.path);
        showpath(answer.bestant.visited);
        printf("M = %d  bestresult = %.2lf\n", m, answer.bestant.total_distance);
        printf("avgresult = %.2lf\n", answer.resultrecord[Iteration_PSO - 1]);
    }
    return 0;
}