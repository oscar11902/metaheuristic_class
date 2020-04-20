#include "ACO.h"

ACO::ACO(vector<vector<double>> distance_table, int nAnts, int m)
{
    this->distance_table = distance_table;
    this->nAnts = nAnts;
    this->nCities = distance_table.size();
    this->m = m;
    limit = 20;
    pheromone_table.resize(nCities, vector<double>(nCities, 0.1));
    prefer_table.resize(nCities, vector<double>(nCities));
    BestAnt = Ant();
    BestAnt.total_distance = 9999999.9;
}

Ant ACO::exe(double alpha, double beta, int iteration, double q)
{
    //initialize
    ALPHA = alpha;
    BETA = beta;
    Q = q;
    //record
    /*
    result_record.resize(iteration, 0.0);
    char *output;
    fstream file;
    fstream pathfile;
    pathfile.open("path.txt", ios::out);
    sprintf(output, "Output_a_%lf_b_%lf_q_%lf.txt", alpha, beta, q);
    */
    for (int i = 0; i < iteration; i++)
    {
        ants.resize(nAnts, Ant(nCities));
        update_prefer_table();
        release_ant();
        for (int a = 0; a < nAnts; a++)
        {
            //ants[a].showpath();
            if (BestAnt.total_distance > ants[a].total_distance && city_visit_check(ants[a].visited))
            {
                BestAnt.clone(ants[a]);
            }
        }
        update_pheromone_table();
        /*
        result_record[i] += BestAnt.total_distance;
        file << i + 1 << " " << BestAnt.total_distance << "\n";
        */

        ants.clear();

        //cout << min << endl;
        //bestAnt.showpath();
    }
    return BestAnt;
}
void ACO::update_prefer_table()
{
    for (int i = 0; i < nCities; i++)
    {
        for (int j = i; j < nCities; j++)
        {
            if (distance_table[i][j] == 0)
                continue;
            prefer_table[i][j] = pow(pheromone_table[i][j], ALPHA) * pow((1 / distance_table[i][j]), BETA);
            prefer_table[j][i] = prefer_table[i][j];
        }
    }
}
void ACO::release_ant()
{
    // Ant Move
    int Start, next_point;
    for (int a = 0; a < nAnts; a++)
    {

        Start = rand() % m;
        ants[a].path.push_back(Start);
        ants[a].visited[Start] = true;
        int counter = 0;
        for (int i = 1; i < nCities; i++)
        {
            next_point = select_next_city(ants[a]);
            if (counter > limit)
            {
                next_point = rand() % m;
                while (ants[a].visited[next_point])
                    next_point = rand() % m;
            }
            if (next_point < m)
                counter = 0;
            else
                counter++;
            cout << counter << endl;
            ants[a].path.push_back(next_point);
            ants[a].visited[next_point] = true;
            Start = next_point;
        }
        if (city_visit_check(ants[a].visited))
            ants[a].total_distance = count_distance(ants[a].path);
        else
            ants[a].total_distance = 999999999.9;
        // 2 - opt
        /*
        vector<int> tmp_path;
        int tmp;
        double tmp_distance;
        for (int indexS = 1; indexS < nCities; indexS++)
        {
            for (int indexE = 0; indexE < indexS; indexE++)
            {
                tmp_path = ants[a].path;
                int limit = (indexS - indexE) >> 1;
                for (int i = 0; i < limit; i++)
                {
                    tmp = tmp_path[indexE + i];
                    tmp_path[indexE + i] = tmp_path[indexS - i];
                    tmp_path[indexS - i] = tmp;
                }
                tmp_distance = count_distance(tmp_path);
                if (tmp_distance < ants[a].total_distance)
                {
                    ants[a].total_distance = tmp_distance;
                    ants[a].path = tmp_path;
                }
            }
        }
        */
    }
}
void ACO::update_pheromone_table()
{
    for (int i = 0; i < nCities; i++)
    {
        for (int j = 0; j < nCities; j++)
        {
            pheromone_table[i][j] *= Q;
        }
    }
    for (int i = 0; i < nAnts; i++)
    {
        double delta_r = 1.0 / ants[i].total_distance;
        for (int j = 0; j < nCities; j++)
        {
            int indexS = ants[i].path[j], indexE = ants[i].path[(j + 1) % nCities];
            pheromone_table[indexS][indexE] += delta_r;
            pheromone_table[indexE][indexS] += delta_r;
        }
    }
    double delta_r = 1.0 / BestAnt.total_distance;
    for (int j = 0; j < nCities; j++)
    {
        int indexS = BestAnt.path[j], indexE = BestAnt.path[(j + 1) % nCities];
        pheromone_table[indexS][indexE] += delta_r;
        pheromone_table[indexE][indexS] += delta_r;
    }
}
int ACO::select_next_city(Ant &ant)
{
    //Calculate the ratio of city that hasn't been visited
    double sum = 0.0;
    int start_point = ant.path[ant.path.size() - 1];
    for (int j = 0; j < nCities; j++)
    {
        if (ant.visited[j])
            continue;
        sum += prefer_table[start_point][j];
    }
    //Select the next city
    double flag = sum * random_ratio();
    for (int j = 0; j < nCities; j++)
    {
        if (!ant.visited[j])
        {
            flag -= prefer_table[start_point][j];
            if (flag < 0)
                return j;
        }
    }
}

void ACO::show_distance_table()
{
    for (vector<double> list : distance_table)
    {
        for (double distance : list)
        {
            printf("%-4.2f ", distance);
        }
        cout << endl;
    }
}

double ACO::count_distance(vector<int> &path)
{
    double total_distance = 0;
    for (int i = 0; i < path.size() - 1; i++)
    {
        total_distance += distance_table[path[i]][path[i + 1]];
    }
    total_distance += distance_table[path[path.size() - 1]][path[0]];
    return total_distance;
}