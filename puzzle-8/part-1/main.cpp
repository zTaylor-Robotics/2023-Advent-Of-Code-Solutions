#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <time.h>

void getTurnList(std::vector<bool> &, std::ifstream &);
void getNumSteps();

int main(){
    std::clock_t t = std::clock();

    //stores the file to be pointed to later
    std::string file_name = "./puzzle-8.txt";
    std::ifstream file(file_name);

    //get the list of turns made
    std::vector<bool> turn_list;
    getTurnList(turn_list, file); //Fetches the turns from the file



    std::cout << std::endl;
    //system("pause");
    std::cout << "Total Execution time: " <<  (std::clock() - t ) / (float)CLOCKS_PER_SEC << " seconds" << std::endl;
    return 0;
}

void getTurnList(std::vector<bool> &list, std::ifstream &file){
    std::string line;
    std::getline(file, line);

    for(char& c: line){
        if(c == 'L') list.push_back(false);
        else if(c == 'R') list.push_back(true);
    }

    std::getline(file, line); //get the blank line underneath the turn list
    return;
}
