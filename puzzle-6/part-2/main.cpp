#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <time.h>

void readFile(long long &, long long &, std::ifstream &);
long long getNumWins(long long, long long);

int main(){
    std::clock_t t = std::clock();

    std::string file_name = "./puzzle-6.txt";
    std::ifstream file(file_name);

    long long time = 0; long long record = 0;

    readFile(time, record, file); //grab the times and records from the input file

    //system("pause");
    std::cout << "The result number of ways to win the race: " << getNumWins(time, record) << std::endl;
    std::cout << "Total Execution time: " <<  (std::clock() - t ) / (float)CLOCKS_PER_SEC << " seconds" << std::endl;
    return 0;
}

void readFile(long long &time, long long &record, std::ifstream &file){
    std::string line;
    std::string int_value;
    bool time_flag = true;

    while(std::getline(file, line)){
        auto it = line.begin();
        auto int_start = it;
        auto int_end = it;

        while(it != line.end()){
            if(isdigit(*it)){
                int_value = int_value + *it;
            }
            it++;
        }
        
        if(time_flag){
            std::cout << int_value << std::endl;
            time = std::stoll(int_value);
            time_flag = false;
            int_value.clear();
        }else{
            std::cout << int_value << std::endl;
            record = std::stoll(int_value);
            return;
        }
    }
    return;
}


long long getNumWins(long long time, long long record){
    long long ret = 0;

    long long right_zero = 0.5*time + 0.5*std::sqrt(std::pow(time, 2) - 4*record - 4);
    long long left_zero  = 0.5*time - 0.5*std::sqrt(std::pow(time, 2) - 4*record - 4) + 1;

    ret = right_zero - left_zero + 1;

    /*
    for(int i = 0; i < time; i++){
        if(isWinner(time, time - i, record)) ret++;
    }
    */
    return ret;
}

bool isWinner(int time, int time_held, int record){
    if(record < time_held*(time - time_held)) return true;
    return false;
}