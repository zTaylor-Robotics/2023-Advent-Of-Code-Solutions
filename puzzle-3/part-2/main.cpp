#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool isStar(int);
bool isNum(int);
bool isTwoNum(std::vector<std::vector<int>> &, int, int);
int getTwoNumProd(std::vector<std::vector<int>> &, int, int);
void printPuzzle(std::vector<std::vector<int>>);
int getNum(std::vector<int>);

int main(){
    int ans = 0;
    std::ifstream file("../../../puzzle-3.txt");
    std::vector<std::vector<int>> puzzle;

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

    for(int i = 0; i < puzzle.size(); i++){
        for(int j = 0; j < puzzle[0].size(); j++){
            //test the squares around the star for the presence of the two numbers
            //if the two numbers exist, get their product
            if(isStar(puzzle[i][j])){
                if(isTwoNum(puzzle, i, j)){
                    ans += getTwoNumProd(puzzle, i, j);
                }
            }
        }
    }

    std::cout << ans << std::endl;
    system("pause");
    return 0;
}

bool isStar(int num){
    if(num == 42) return true;
    return false;
}

bool isNum(int num){
    if(num >= 48 && num <= 57){
        return true;
    }
    return false;
}

void printPuzzle(std::vector<std::vector<int>> map){
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[0].size(); j++){
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool isTwoNum(std::vector<std::vector<int>> &arr, int x, int y){
    bool row_flag = false;
    int nums = 0;
    for(int i = -1; i < 2; i++){
        row_flag = false;
        for(int j = -1; j < 2; j++){
            if(isNum(arr[i + x][j + y])){
                if(row_flag != true){
                    row_flag = true;
                    nums++;
                }
            }else{
                row_flag = false;
            }
        }
    }
    if(nums == 2) return true;
    return false;
}

int getTwoNumProd(std::vector<std::vector<int>> &arr, int x, int y){

    //map the position of numbers
    std::vector<std::vector<bool>> num_pos;
    int line_num = 0;
    for(int i = -1; i < 2; i++){
        num_pos.push_back(std::vector<bool>());
        for(int j = -1; j < 2; j++){
            if(isNum(arr[i + x][j + y])){
                num_pos[line_num].push_back(1);
            }else{
                num_pos[line_num].push_back(0);
            }
        }
        line_num++;
    }

    //extrapolate the full number based on the position of the number flags
    int ret = 1;
    bool num_flag = false;
    bool num1_flag = false;
    bool num2_flag = false;
    std::vector<int> temp;

    for(int i = -1; i < 2; i++){
        num_flag = false; // removes the flag when going to the next row
        for(int j = -3; j < 4; j++){
            //fills the check to see if the current temp indeed contains one of the adjacent numbers
            if(j >= -1 && j <= 1){
                if(num_pos[i+1][j+1]){
                    num_flag = true;
                }
            }
            if(isNum(arr[i + x][j + y])){
                temp.push_back(arr[i + x][j + y] - 48);
            }else if(temp.size() != 0 && !num_flag){
                temp.clear();
            }else if(temp.size() != 0 && num_flag){
                std::cout << getNum(temp) << " ";
                ret *= getNum(temp);
                temp.clear();
                num_flag = false;
            }
        }
        if(temp.size() != 0 && num_flag){
            std::cout << getNum(temp) << " ";
            ret *= getNum(temp);
            temp.clear();
            num_flag = false;
        }
    }
    std::cout << ret << std::endl;
    return ret;
}

int getNum(std::vector<int> v_num){
    int ret = 0;
    for(int i = 0; i < v_num.size(); i++){
        ret += (pow(10, (v_num.size() - i - 1)) * v_num[i]);
    }
    return ret;
}