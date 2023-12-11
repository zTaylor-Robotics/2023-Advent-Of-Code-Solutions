#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <time.h>

void readFile(std::vector<std::vector<int>> &, std::ifstream &);
int getNumWins(int, int);
bool isWinner(int, int, int);

int main(){
    std::clock_t t = std::clock();

    std::string file_name = "./puzzle-6.txt";
    std::ifstream file(file_name);

    std::vector<std::vector<int>> data; //vector where each row reprents [time][record]
    int output = 1; //logs the multiple of the number of wins per data point

    readFile(data, file); //grab the times and records from the input file

    //Grab the number of wins per point and multiply them by the previous wins.
    for(auto& point: data){
        output *= getNumWins(point[0], point[1]);
        std::cout << getNumWins(point[0], point[1]) << std::endl;
    }

    //system("pause");
    std::cout << "The result of multiplying the number of ways to win each race: " << output << std::endl;
    std::cout << "Total Execution time: " <<  (std::clock() - t ) / (float)CLOCKS_PER_SEC << " seconds" << std::endl;
    return 0;
}

void readFile(std::vector<std::vector<int>> &data, std::ifstream &file){
    std::string line;
    std::vector<int> temp;
    bool num_start = 0;
    bool resize_complete = 0;

    while(std::getline(file, line)){
        auto it = line.begin();
        auto int_start = it;
        auto int_end = it;

        while(it != line.end()){
            if(isdigit(*it)){
                if(!num_start){
                    int_start = it;
                    num_start = true;
                }
            }else{
                if(num_start){
                    int_end = it;

                    if(!resize_complete){
                        data.push_back(std::vector<int>(2, 0));
                    }

                    temp.push_back(std::stoi(std::string(int_start, int_end)));
                    num_start = false;
                }
            }
            it++;
        }
        if(num_start){
            int_end = it;

            if(!resize_complete){
                data.push_back(std::vector<int>(2, 0));
            }

            temp.push_back(std::stoi(std::string(int_start, int_end)));
            num_start = false;
        }

        for(int i = 0; i < temp.size(); i++){
            data[i][resize_complete] = temp[i];
        }

        temp.clear();
        resize_complete = true;
    }
    return;
}


int getNumWins(int time, int record){
    int ret = 0;

    int right_zero = 0.5*time + 0.5*std::sqrt(std::pow(time, 2) - 4*record - 4);
    int left_zero  = 0.5*time - 0.5*std::sqrt(std::pow(time, 2) - 4*record - 4) + 1;

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