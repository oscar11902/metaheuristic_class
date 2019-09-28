#include <iostream>
#include <vector>
#include <time.h>
#include "HC.h"
#include "ES.h"


using namespace std;

int main(int argc, char *argv[])
{
    vector<bool> bitstring;
    int runs = 30, iterators = 1000, length = 100 , timelimit = 600;
    double avgresult = 0.0;
    int algorithm = 0;
    bool timeout = false;
    srand(time(NULL));
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        switch (arg[0])
        {
        case '-':
            switch (arg[1])
            {
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
            case 't':
                i++;
                timelimit = atoi(argv[i]);
                break;
            case 'o':
                i++;
                if(atoi(argv[i])>0)timeout = true;
                break;
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
                }
                break;
            }
            break;
        default:
            break;
        }
    }
    bitstring.resize(length,false);
    if(!algorithm){
        HC hc;
        avgresult = hc.exe(bitstring , runs , iterators);
    }else{
        ES es;
        avgresult = es.exe(bitstring , timelimit , timeout);
    }
    printf("result = %.2lf\n", avgresult);
    return 0;
}