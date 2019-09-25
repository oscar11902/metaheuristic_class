#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    vector<bool> bitstring;
    int runs, iterators, length;
    double avgresult = 0.0;
    int algorithm = 0;
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
    printf("length = %d\nruns = %d\niterators = %d\nalgorthm = %d\n" ,length , runs , iterators , algorithm);
    return 0;
}