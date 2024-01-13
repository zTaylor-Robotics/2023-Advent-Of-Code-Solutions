#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>

unsigned long readFile(std::ifstream &);
unsigned long long getNum(std::vector<char> &, std::vector<unsigned long> &); //returns the number of good combinations of springs
void countGoodConfigs(std::vector<char> &, std::vector<unsigned long> &, std::vector<unsigned long> &, unsigned long &, unsigned long &, unsigned long);

std::vector<char> buildConfig(std::vector<unsigned long>, std::vector<unsigned long> &);
std::vector<char> buildTest(std::vector<unsigned long>, std::vector<unsigned long> &, unsigned long);
bool cmpConfig(std::vector<char> &, std::vector<char> &);


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
unsigned long long getNum(std::vector<char> &springs, std::vector<unsigned long> &groups){
    unsigned long count1 = 0; //temp, change this
    unsigned long count2 = 0;

    std::vector<unsigned long> values(groups.size() + 1, 0); //initialize the empty value vector to kick off recursion
    unsigned long R = springs.size();

    for(unsigned long g: groups){
        R -= g;
    }
    R -= groups.size() - 1;
    values[0] = R;

    countGoodConfigs(springs, values, groups, count1, R, 0);

    values.clear();

    unsigned long length = groups.size();
    for(unsigned long i = 0; i < length; i++) groups.push_back(groups[i]);

    values = std::vector<unsigned long>(groups.size() + 1, 0);
    
    length = springs.size();
    springs.push_back('?');
    for(unsigned long j = 0; j < length; j++) springs.push_back(springs[j]);
    
    R = springs.size();
    
    for(unsigned long g: groups){
        R -= g;
    }
    R -= groups.size() - 1;
    values[0] = R;

    countGoodConfigs(springs, values, groups, count2, R, 0);
    
    return (count2*count2*count2*count2)/(count1*count1*count1);
}

void countGoodConfigs(std::vector<char> &springs, std::vector<unsigned long> &vals, std::vector<unsigned long> &groups, unsigned long &count, unsigned long &R, unsigned long depth){
    if(depth >= (vals.size() - 1)){
        std::vector<char> temp = buildConfig(vals, groups);
        if(cmpConfig(springs, temp)){
            count++;
        }
        return;
    }

    for(unsigned long i = 0; i <= vals[depth]; i++){
        std::vector<unsigned long> temp = vals;
        temp[depth] -= i;
        temp[depth+1] = R;
        for(unsigned long j = 0; j <= depth; j++){
            temp[depth+1] -= temp[j];
        }

        std::vector<char> test = buildTest(temp, groups, depth);
        if(cmpConfig(springs, test)){
            countGoodConfigs(springs, temp, groups, count, R, depth + 1);
        }
    }

    return;
}

bool cmpConfig(std::vector<char> &springs, std::vector<char> &config){
    for(unsigned long i = 0; i < config.size(); i++){
        if(springs[i] == '.' && config[i] == '#'){
            return false;
        }else if(springs[i] == '#' && config[i] == '.'){
            return false;
        }
    }
    return true;
}

std::vector<char> buildConfig(std::vector<unsigned long> vals, std::vector<unsigned long> &groups){
    std::vector<char> config;

    for(unsigned long i = 1; i < vals.size() - 1; i++) vals[i]++; //add in the necessary . between groups of springs

    for(unsigned long i = 0; i < vals.size(); i++){
        for(unsigned long j = 0; j < vals[i]; j++){config.push_back('.');}
        if(i < (vals.size() - 1)){for(unsigned long k = 0; k < groups[i]; k++){config.push_back('#');}}
    }
    return config;
}

std::vector<char> buildTest(std::vector<unsigned long> vals, std::vector<unsigned long> &groups, unsigned long depth){
    std::vector<char> test;

    for(unsigned long i = 1; i < vals.size() - 1; i++) vals[i]++; //add in the necessary . between groups of springs
        
    for(unsigned long i = 0; i <= depth; i++){
        for(unsigned long j = 0; j < vals[i]; j ++) test.push_back('.');
        for(unsigned long k = 0; k < groups[i]; k ++) test.push_back('#');
    }
    return test;
}