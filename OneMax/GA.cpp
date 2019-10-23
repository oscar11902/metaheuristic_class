#include "GA.h"

using namespace std;

double GA::exe(vector<bool> bitstring, int run, int iterator, int num_gene, double mutation_rate , bool selection_method)
{
    double result = 0.0;
    int round = run;
    
    geneset.resize(num_gene,bitstring);
    while (round--)
    {
        //Initialize
        double round_result = 0.0;
        geneset.clear();
        valueset.clear();
        int time = iterator;
        for(vector<bool> string :geneset){
            initstring(string);
        } 
        valueset.resize(num_gene);
        evaluateset(geneset , valueset);
        while (time--)
        {
            if(selection_method){
                selection_rotation();
            }else{
                selection_rotation();
            }
            crossover();
            mutation(mutation_rate);
            evaluateset(geneset , valueset);
        }
        for(int value : valueset){
            round_result +=value;
        } 
        round_result /= geneset.size();
        result+= round_result;
    }    
    result /= run;
    return result;
}
void GA::selection_rotation(){
    vector<double> gene_ratio;
    double sum = 0.0;
    for(int value : valueset){
        sum+= value;
    }
    for(int i = 0 ; i < valueset.size() ; i++){
        gene_ratio.push_back(valueset[i]/sum);
    }
    vector<vector<bool>> new_geneset;
    for(int i = 0 ; i < geneset.size() ; i++){
        double flag = random_ratio();
        for(int j = 0 ; j < geneset.size() ; j++){
            flag -=gene_ratio[i];
            if(flag < 0 )new_geneset.push_back(geneset[i]); 
        }
    }
    geneset.clear();
    geneset.assign(new_geneset.begin() , new_geneset.end());
}
void GA::selection_(){

}
void GA::mutation(double mutation_rate){
    for(int i = 0 ; i < geneset.size() ; i++){
        if(random_ratio() < mutation_rate){
            int index = rand()%geneset[i].size();
            geneset[i][index] = !geneset[i][index];
        }
    }
}
void GA::crossover(){
    for(int i = 0 ; i < geneset.size() ; i+=2){
        int flag = rand()%geneset[i].size();
        for(int j = flag ; j < geneset[i].size() ; i++){
            bool tmp = geneset[i][j];
            geneset[i][j] = geneset[i+1][j];
            geneset[i+1][j] = tmp;
        } 
    }
}