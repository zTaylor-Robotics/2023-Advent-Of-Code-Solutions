#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool isStar(int);
bool isNum(int);
bool isTwoNum(std::vector<std::vector<int>> &, int, int);
int getTwoNumProd(std::vector<std::vector<int>> &, int, int);
void printArr(std::vector<std::vector<int>>);
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

void printArr(std::vector<std::vector<int>> arr){
    for(int i = 0; i < arr.size(); i++){
        for(int j = 0; j < arr[0].size(); j++){
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printArr(std::vector<std::vector<bool>> arr){
        for(int i = 0; i < arr.size(); i++){
            for(int j = 0; j < arr[0].size(); j++){
                std::cout << arr[i][j] << " ";
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

    std::vector<int> temp;
    for(int i = -1; i < 2; i++){
        //reset variables to make sure there is no data carried from row to row
        temp.clear();
        num_flag = false; 

        for(int j = -3; j < 4; j++){
            //fills the check to see if the current temp indeed contains one of the adjacent numbers
            //num_flag will be true if the iterator is looking at a true value in num_pos (meaning that it is a number we care about)
            if(j >= -1 && j <= 1){
                if(num_pos[i+1][j+1]){
                    num_flag = true;
                }
            }

            //process the value at the i,j location
            if(isNum(arr[i + x][j + y])){ //check to see if it is a number, if it is push it to the array
                temp.push_back(arr[i + x][j + y] - 48);
            }else if(temp.size() != 0 && !num_flag){ //if it is not a number and num_flag is false, the delete temp because it contains a value we dont care about
                temp.clear();
            }else if(temp.size() != 0 && num_flag){ //if it is not a numberand num_flag is true, then temp is filled with a value we care about and want to store
                ret *= getNum(temp);
                temp.clear(); //clear temp and flag to allow us to find the next number if this is the first
                num_flag = false;
            }
        }
        //process temp for when the last value of the inner loop ends with a number
        if(temp.size() != 0 && num_flag){
            ret *= getNum(temp);
        }
    }
    return ret;
}

int getNum(std::vector<int> v_num){
    int ret = 0;
    for(int i = 0; i < v_num.size(); i++){
        ret += (pow(10, (v_num.size() - i - 1)) * v_num[i]);
    }
    return ret;
}