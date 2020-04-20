#include <iostream>
#include <vector>
#include <time.h>
#include "GA.h"

using namespace std;

int main(int argc, char *argv[])
{
    vector<bool> bitstring;
    //Common
    int runs = 30, iterators = 1000, length = 100;
    double avgresult = 0.0;
    int algorithm = 0;
    //ES
    int timelimit = 600;
    bool timeout = false;
    //SA
    int Start_Temp = 300, End_Temp = 10;
    double ratio = 0.95;
    //TS
    int Array_Size = 7;
    //GA
    double mutation_rate = 1.0;
    int num_of_gene = 10;
    bool selection_branch =false;
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
                switch (argv[i][0])
                {
                case 'H':
                    algorithm = 0;
                    break;
                case 'E':
                    algorithm = 1;
                    break;
                case 'S':
                    algorithm = 2;
                    break;
                case 'T':
                    algorithm = 3;
                    break;
                case 'G':
                    algorithm = 4;
                    break;
                }
                break;
            case 'l':
                i++;
                length = atoi(argv[i]);
                break;
            case 'i':
                i++;
                iterators = atoi(argv[i]);
                break;
            case 'r':
                i++;
                runs = atoi(argv[i]);
                break;
            //ES
            case 't':
                i++;
                timelimit = atoi(argv[i]);
                break;
            case 'o':
                i++;
                if (atoi(argv[i]) > 0)
                    timeout = true;
                break;
            //SA
            case 's':
                i++;
                Start_Temp = atoi(argv[i]);
                break;
            case 'e':
                i++;
                End_Temp = atoi(argv[i]);
                break;
            case 'R':
                i++;
                ratio = atof(argv[i]);
            //TS
            case 'A':
                i++;
                Array_Size = atoi(argv[i]);
                break;
            //GA
            case 'm':
                i++;
                mutation_rate = atof(argv[i]);
                break;
            case 'n':
                i++;
                num_of_gene = atoi(argv[i]);
                break;
            case 'b':
                i++;
                if (atoi(argv[i]) > 0)
                    selection_branch = true;
                break;
            }
            break;
        default:
            break;
        }
    }
    bitstring.resize(length, false);
    switch (algorithm)
    {
    case 0:
    {
        HC hc;
        avgresult = hc.exe(bitstring, runs, iterators);
    }

    break;
    case 1:
    {
        ES es;
        avgresult = es.exe(bitstring, timelimit, timeout);
    }

    break;
    case 2:
    {
        SA sa;
        avgresult = sa.exe(Start_Temp, End_Temp, runs, ratio, bitstring);
    }

    break;
    case 3:
    {
        TS ts;
        avgresult = ts.exe(Array_Size, runs, iterators, bitstring);
    }
    break;
    case 4:
    {
        GA ga;
        avgresult = ga.exe(bitstring , runs , iterators , num_of_gene , mutation_rate , selection_branch);
    }
    default:
        break;
    }
    printf("result = %.2lf\n", avgresult);
    return 0;
}