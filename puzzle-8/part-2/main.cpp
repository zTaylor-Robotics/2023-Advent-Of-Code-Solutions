#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <time.h>

void getTurnList(std::vector<bool> &, std::ifstream &);
void getMap(std::map<std::string, std::pair<std::string, std::string>> &, std::ifstream &);
int getNumSteps(std::map<std::string, std::pair<std::string, std::string>> &, std::vector<bool> &);

void printMap(std::map<std::string, std::pair<std::string, std::string>> &);

int main(){
    std::clock_t tot = std::clock();

    //stores the file to be pointed to later
    std::string file_name = "./puzzle-8.txt";
    std::ifstream file(file_name);

    //get the list of turns made
    std::vector<bool> turn_list;
    getTurnList(turn_list, file); //Fetches the turns from the file

    //create map containing all the steps as [key][value] pairs where the key is the
    //milestone and the value is a pair(left milestone,right milestone)
    std::map<std::string, std::pair<std::string, std::string>> ms_map;
    getMap(ms_map, file);


    //this is a very bruteforce method for getting the number of steps
    //primarily because of the puzzle context
    int numsteps = getNumSteps(ms_map, turn_list);

    std::cout << "Number of Steps: " << numsteps << std::endl;

    //system("pause");
    std::cout << "Total Execution time: " <<  (std::clock() - tot ) / (float)CLOCKS_PER_SEC << " seconds" << std::endl;
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

void getMap(std::map<std::string, std::pair<std::string, std::string>> &map, std::ifstream &file){
    std::string line, key, left, right;

    while(std::getline(file, line)){
        key = line.substr(0, 3);
        left = line.substr(7, 3);
        right = line.substr(12, 3);
        map[key] = std::pair<std::string, std::string> (left, right);
    }

    return;
}

int getNumSteps(std::map<std::string, std::pair<std::string, std::string>> &map, std::vector<bool> &step){
    std::string current_milestone = "AAA";
    int count = 0; int vect_it = 0;

    while(current_milestone != "ZZZ"){
        if(vect_it == step.size()) vect_it = 0;

        if(step[vect_it]) current_milestone = map[current_milestone].second;
        else current_milestone = map[current_milestone].first;
        count++;
        vect_it++;
    }

    return count;
}

void printMap(std::map<std::string, std::pair<std::string, std::string>> &map){
    for(auto& row: map){
        std::cout << row.first << " = (" << row.second.first << ", " << row.second.second << ")" << std::endl;
    }
    return;
}

