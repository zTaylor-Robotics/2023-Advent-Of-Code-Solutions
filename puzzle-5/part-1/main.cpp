#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main(){
    int ans = 0;
    std::string file_name = "../../../puzzle-5.txt";
    std::vector<int> seeds;

    std::string line;
    std::ifstream file(file_name);

    //fill vector<int> seeds with the seeds
    //figure out a method for breaking apart the mapping data into an algorithm

    std::cout << ans << std::endl;
    system("pause");
    return 0;
}

void getPuzzle(std::vector<std::vector<int>> &puzzle, std::string file_name){
    std::string line;
    std::ifstream file(file_name);
    int line_num = 0;
    int count = 0;
    while(std::getline(file, line)){
        puzzle.push_back(std::vector<int>());
        for(char& c: line){
            if(count > 9){
                puzzle[line_num].push_back(int(c));
            }
            count++;
        }
        count = 0;
        line_num++;
    }
    return;
}