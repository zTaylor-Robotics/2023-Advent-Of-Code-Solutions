#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(){
    std::ifstream file("../../../puzzle-3.txt");
    std::vector<std::vector<int>> arr;

    std::string line;
    int line_num = 0;
    while(std::getline(file, line)){
        arr.push_back(std::vector<int>());
        for(char& c: line){
            arr[line_num].push_back(int(c));
        }
        line_num++;
    }

    for(int i = 0; i < arr.size(); i++){
        for(int j = 0; j < arr[0].size(); j++){
            
        }
    }

    system("pause");
    return 0;
}
