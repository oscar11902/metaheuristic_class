#include <iostream>
#include <vector>
#include <time.h>
#include "HC.h"
#include "ES.h"


using namespace std;

int main(int argc, char *argv[])
{
    vector<bool> bitstring;
    int runs = 30, iterators = 1000, length = 100;
    double avgresult = 0.0;
    int algorithm = 0;
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
        avgresult = es.exe(bitstring , runs , iterators);
    }
    printf("length = %d\nruns = %d\niterators = %d\nalgorthm = %d\n" ,length , runs , iterators , algorithm );
    printf("average result = %lf\n", avgresult);
    return 0;
}