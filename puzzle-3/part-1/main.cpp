#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool isSymbol(int);
void fillMap(std::vector<std::vector<bool>> &, std::vector<std::vector<int>>);
void printMap(std::vector<std::vector<bool>>);
int getNum(std::vector<int>);

int main(){
    int ans = 0;
    std::ifstream file("../../../puzzle-3.txt");
    std::vector<std::vector<int>> puzzle;
    std::vector<std::vector<bool>> adj_symbol_map;
    std::vector<int> temp; //used to help make full numbers

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

    fillMap(adj_symbol_map, puzzle);

    //go line by line through the puzzle grabbing a number sequence, compare that sequence to the adj_symbol_map, if one cell is true append the number to ans.
    bool flag = false;
    for(int i = 0; i < puzzle.size(); i++){
        for(int j = 0; j < puzzle[0].size(); j++){
            if(puzzle[i][j] >= 48 && puzzle[i][j] <= 57){
                temp.push_back(puzzle[i][j] - 48);
                if(adj_symbol_map[i][j] == true) flag = true;
            }else if(temp.size() != 0){
                if(flag){
                    ans += getNum(temp);
                    std::cout << getNum(temp) << std::endl;
                }
                temp.clear(); flag = false;
            }else flag = false;
        }
    }

    std::cout << ans << std::endl;
    system("pause");
    return 0;
}

bool isSymbol(int num){
    if(num != 46 && (48 > num || num > 57)) return true;
    return false;
}

void fillMap(std::vector<std::vector<bool>> &map, std::vector<std::vector<int>> ref){
    //Map the adjacent squares
    //First initialize the map with zeros
    int count = 0;
    for(int i = 0; i < ref.size(); i++){
        map.push_back(std::vector<bool>(ref[0].size(), false));
    }

    //set boolean true to every square that is adjacent to a symbol
    for(int i = 0; i < ref.size(); i++){
        for(int j = 0; j < ref[0].size(); j++){
            if(isSymbol(ref[i][j])){
                for(int m = 0; m < 3; m++){
                    for(int n = 0; n < 3; n++){
                        map[i - 1 + m][j - 1 + n] = true;
                    }
                }
            }
        }
    }
    return;
}

void printMap(std::vector<std::vector<bool>> map){
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[0].size(); j++){
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int getNum(std::vector<int> v_num){
    int ret = 0;
    for(int i = 0; i < v_num.size(); i++){
        ret += (pow(10, (v_num.size() - i - 1)) * v_num[i]);
    }
    return ret;
}