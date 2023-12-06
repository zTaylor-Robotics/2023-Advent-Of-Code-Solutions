#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void getPuzzle(std::vector<std::vector<int>> &, std::string);
void printArr(std::vector<std::vector<int>> &);
void printWinLog(std::vector<bool> &);
bool isNum(int);
int getNum(std::vector<int>);
void reset(std::vector<bool> &);

int main(){
    int ans = 0;
    std::string file_name = "../../../puzzle-4.txt";
    std::vector<std::vector<int>> puzzle;
    std::vector<bool> win_log(100, 0);
    int win_count = 0; int count = 0;
    std::vector<int> temp;

    //copy puzzle from file into a vector array
    getPuzzle(puzzle, file_name);
    std::vector<int> cards_won_log(puzzle.size(), 1);

    //iterate through the array row by row
    for(int i = 0; i < puzzle.size(); i++){
        //if(cards_won_log[i] == 0) break;
        //clear out the win_log to setup the next set
        reset(win_log);
        count = 0;
        //iterate through the winning numbers and fill the winlog.
        for(int j = 0; j < 32; j++){
            if(isNum(puzzle[i][j])){
                temp.push_back(puzzle[i][j] - 48);
            }else if(temp.size() != 0){
                win_log[getNum(temp)] = true;
                temp.clear();
            }
        }

        //iterate through the the numbers and count how many winning values exist
        for(int j = 32; j < puzzle[0].size(); j++){
            if(isNum(puzzle[i][j])){
                temp.push_back(puzzle[i][j] - 48);
            }else if(temp.size() != 0){
                if(win_log[getNum(temp)]){
                    count++;
                }
                temp.clear();
            }
        }
        if(temp.size() != 0){
            if(win_log[getNum(temp)]){
                count++;
            }
            temp.clear();
        }

        for(int n = 0; n < count; n++){
            if(i+n+1 < cards_won_log.size()){
                cards_won_log[i+n+1] += cards_won_log[i];
            }
        }
    }
    for(int i = 0; i < cards_won_log.size(); i++){
        ans += cards_won_log[i];
    }
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

void printArr(std::vector<std::vector<int>> &arr){
    for(int i = 0; i < arr.size(); i++){
        for(int j = 0; j < arr[0].size(); j++){
            std::cout << char(arr[i][j]);
        }
        std::cout << std::endl;
    }
    return;
}

void printWinLog(std::vector<bool> &wlog){
    for(int i = 0; i < wlog.size(); i++){
        std::cout << i << ": " << wlog[i] << " | ";
    }
    std::cout << std::endl;
    return;
}

bool isNum(int num){
    if(num >= 48 && num <= 57){
        return 1;
    }
    return 0;
}

int getNum(std::vector<int> v_num){
    int ret = 0;
    for(int i = 0; i < v_num.size(); i++){
        ret += (pow(10, (v_num.size() - i - 1)) * v_num[i]);
    }
    return ret;
}

void reset(std::vector<bool> &arr){
    arr.clear();
    arr = std::vector<bool>(100,false);
    return;
}