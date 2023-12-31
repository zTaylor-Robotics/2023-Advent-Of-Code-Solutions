#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>

int readFile(std::ifstream &);
int getNumOpt(std::vector<char> &, std::vector<int> &);

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    std::clock_t t = std::clock();

    std::string file_name = "./data.in";
    std::ifstream file(file_name);

    int result = readFile(file);
    //system("pause");
    std::cout << "Result = " << result << std::endl;
    std::cout << "Total Execution time: " <<  (std::clock() - t ) / (float)CLOCKS_PER_SEC << " seconds" << std::endl;
    return 0;
}

int readFile(std::ifstream &file){
    std::string line, temp;
    std::vector<char> springs;
    std::vector<int> groups;
    int count = 0;
    bool swap = true;
    while(std::getline(file, line)){
        springs.clear(); groups.clear(); temp.clear(); swap = true;
        for(const char c: line){
            if(c == ' '){
                swap = false;
                continue;
            }
            if(swap){
                springs.push_back(c);
            }else{
                if(c == ','){
                    groups.push_back(std::stoi(temp));
                    temp.clear();
                }else temp+= c;
            }   
        }
        groups.push_back(std::stoi(temp));
        count += getNumOpt(springs, groups);
    }
    return count;
}

int getNumOpt(std::vector<char> &springs, std::vector<int> &groups){

    return 0;
}
