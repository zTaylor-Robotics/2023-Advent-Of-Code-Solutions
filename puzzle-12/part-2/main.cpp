#include <cstdlib>
#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <vector>
#include <map>
#include <ctime>

unsigned long readFile(std::ifstream &);

unsigned long long getNum(std::vector<char> &, 
                          std::vector<unsigned long> &); //returns the number of good combinations of springsss

unsigned long long recurse(std::vector<char> &, 
                           std::vector<unsigned long> &, 
                           std::map<std::pair<unsigned long, std::vector<char>>, unsigned long long> &,
                           unsigned long);

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    std::clock_t t = std::clock();

    std::string file_name = "./data.in";
    std::ifstream file(file_name);

    unsigned long result = readFile(file);
    //system("pause");
    std::cout << "Result = " << result << std::endl;
    std::cout << "Total Execution time: " <<  (std::clock() - t ) / (float)CLOCKS_PER_SEC << " seconds" << std::endl;
    return 0;
}

unsigned long readFile(std::ifstream &file){
    std::string line, temp;
    std::vector<char> springs;
    std::vector<unsigned long> groups;
    unsigned long long count = 0;
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
        count += getNum(springs, groups);
    }
    return count;
}

//generate possible strings and compare each string with the base strings: springs
unsigned long long getNum(std::vector<char> &springs, 
                          std::vector<unsigned long> &groups){

    unsigned long long count = 0;
    std::map<std::pair<unsigned long, std::vector<char>>, unsigned long long> memo;
    unsigned long depth = 0;
    count = recurse(springs, groups, memo, depth);

    return count;
}

unsigned long long recurse(std::vector<char> &springs, 
                           std::vector<unsigned long> &groups, 
                           std::map<std::pair<unsigned long, std::vector<char>>, unsigned long long> &memo,
                           unsigned long depth){
    unsigned long long count = 0;

    if(depth == (groups.size() - 1)){
      return 1;
    }

    count += recurse(springs, groups, memo, depth + 1);
    return count;
}