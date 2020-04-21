#include "Recorder.h"

Recorder::Recorder(int iteration)
{
    record.resize(iteration, 0.0);
}
void Recorder::to_file(string filename = "record.txt"){
    fstream file;
    file.open(filename , ios::out);
    if(!file){
        cout << filename << " can't be opened.\n";
    }else{
        for (double num : record){
            file << num<< endl;
        }
        file.close();
    }

}
void Recorder::cal_result(int run){
    for(int i = 0 ; i < record.size() ; i++){
        record[i] /= run;
    }
}
double Recorder::get_result(){
    return record[record.size()-1];
}

