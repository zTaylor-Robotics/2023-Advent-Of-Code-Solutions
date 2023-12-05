#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define GAME_DELIMITER ';'
#define COLOR_DELIMITER ','


void update_colors(std::string, std::string, int&, int&, int&);

int main(){
    int ans = 0; int line_num = 0;
    std::string line;
    //temp values for number of cubes in a game
    int tmpr = 0; int tmpg = 0; int tmpb = 0;
    bool line_state = 1;
    std::ifstream file("puzzle-2.txt");
    std::string num;
    std::string color;

    while(std::getline(file, line)){
        auto it = line.begin();
        tmpr = 0; tmpg = 0; tmpb = 0;

        while(*it != ':'){
            it++;
            continue;
        }
        it++;

        num.clear(); color.clear();
        while(it != line.end()){
            if(*it == COLOR_DELIMITER || *it == GAME_DELIMITER){
                update_colors(color, num, tmpr, tmpg, tmpb);
                color.clear(); num.clear();
            }else if(isdigit(*it)){
                num += *it;
            }else{
                color += *it;
            }
            it++;
            if(it == line.end()){
                update_colors(color, num, tmpr, tmpg, tmpb);
            }
        }
        ans += tmpr*tmpg*tmpb;
    }
    std::cout << ans << std::endl;
    system("pause");
    return 0;
}

void update_colors(std::string color, std::string num, int& red, int& green, int& blue){
    int temp = stoi(num);

    if(color.find("red") != std::string::npos){
        if(temp > red) red = temp;
    }else if(color.find("green") != std::string::npos){
        if(temp > green) green = temp;
    }else if(color.find("blue") != std::string::npos){
        if(temp > blue) blue = temp;
    }

    return;
}
