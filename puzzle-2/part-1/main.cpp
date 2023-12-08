#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define NUM_RED_CUBES 12
#define NUM_GREEN_CUBES 13
#define NUM_BLUE_CUBES 14
#define GAME_DELIMITER ';'
#define COLOR_DELIMITER ','

bool try_pair(std::string, std::string);

int main(){
    int ans = 0; int line_num = 0;
    std::string line;
    //temp values for number of cubes in a game
    int tmpr = 0; int tmpg = 0; int tmpb = 0;
    bool line_state = 1;
    std::ifstream file("../../../puzzle-2.txt");
    std::string num;
    std::string color;

    while(std::getline(file, line)){
        line_num++;
        auto it = line.begin();
        line_state = 1;

        while(*it != ':'){
            it++;
            continue;
        }
        it++;

        num.clear(); color.clear();
        while(it != line.end()){
            if(*it == COLOR_DELIMITER || *it == GAME_DELIMITER){
                line_state *= try_pair(color, num);
                color.clear(); num.clear();
            }else if(isdigit(*it)){
                num += *it;
            }else{
                color += *it;
            }
            it++;
            if(it == line.end()){
                line_state *= try_pair(color, num);
            }
        }

        if(line_state){
            ans += line_num;
            //std::cout << line_num << std::endl;
        }
    }
    std::cout << ans << std::endl;
    system("pause");
    return 0;
}

bool try_pair(std::string color, std::string num){
    if(color.find("red") != std::string::npos){
        if(stoi(num) > NUM_RED_CUBES){
            return false;
        }
    }else if(color.find("blue") != std::string::npos){
        if(stoi(num) > NUM_BLUE_CUBES){
            return false;
        }
    }else if(color.find("green") != std::string::npos){
        if(stoi(num) > NUM_GREEN_CUBES){
            return false;
        }
    }
    return true;
}
