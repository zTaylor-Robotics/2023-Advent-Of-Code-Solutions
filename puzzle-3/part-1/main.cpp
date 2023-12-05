#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool isSymbol(int);

int main(){
    std::ifstream file("../../../puzzle-3.txt");
    std::vector<std::vector<int>> puzzle;
    std::vector<std::vector<int>> adj_symbol_map;

    //copy puzzle into a 140x140 array
    std::string line;
    int line_num = 0;
    while(std::getline(file, line)){
        puzzle.push_back(std::vector<int>());
        for(char& c: line){
            puzzle[line_num].push_back(int(c));
        }
        line_num++;
    }

    //numbers are int values between 48 and 57 and the period spacer is int value 46, anything else is a symbol
    //two approaches to this problem: one, we could create a relational array where we put boolean true values in squares that are adjacent to symbols
    //then we test the array to see if a series of numbers are ever true
    //the second approach is to grab the small vector representing the number and test all adjacent cells at that moment.


    //Map the adjacent squares
    //First initialize adj_symbol_map with zeros
    int count = 0;
    for(int i = 0; i < puzzle.size(); i++){
        adj_symbol_map.push_back(std::vector<int>(puzzle[0].size(), 0));
    }

    //lets get the number of symbols
    for(int i = 1; i < puzzle.size(); i++){
        for(int j = 1; j < puzzle[0].size(); j++){
            
        }
    }

    std::cout << std::endl;
    system("pause");
    return 0;
}

bool isSymbol(int num){
    if(num != 46 && (48 > num || num > 57)) return true;
    return false;
}