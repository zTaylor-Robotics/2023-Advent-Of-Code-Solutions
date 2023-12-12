#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <time.h>

void readFile(std::map<int, int> &, std::ifstream &);
int getScore(std::string);
char getType(std::string &);
long long getResult(std::map<int, int> &);

void printList(std::map<int, int> &);

int main(){
    std::clock_t t = std::clock();

    std::string file_name = "./puzzle-7.txt";
    std::ifstream file(file_name);
    std::map<int, int> list;

    readFile(list, file);
    //printList(list);
    long long result = getResult(list);

    std::cout << "Result: " << result << std::endl;
    //system("pause");
    std::cout << "Total Execution time: " <<  (std::clock() - t ) / (float)CLOCKS_PER_SEC << " seconds" << std::endl;
    return 0;
}

void readFile(std::map<int, int> &map, std::ifstream &file){
    std::string line;
    std::string hand;
    int bid = 0;
    char type;

    while(std::getline(file, line)){
        auto it = line.begin();
        auto hand_start = it;

        while(it != line.end()){
            if(*it == ' '){
                it++;
                map[getScore(std::string(hand_start, it - 1))] = std::stoi(std::string(it, line.end()));
                break;
            }
            it++;
        }
    }
    return;
}

//turn the hand into a hex string where each card position plays individually into the value leading with type
int getScore(std::string hand){
    std::string score = {getType(hand)};
    for(char& c: hand){
        switch(c){
            case 'A': score += 'E'; break;
            case 'K': score += 'D'; break;
            case 'Q': score += 'C'; break;
            case 'J': score += 'B'; break;
            case 'T': score += 'A'; break;
            default:  score += c;
        }
    }
    return std::stoi(score, nullptr, 16);
}


/*
    The Types are as follows:
        F: 5 of a kind
        E: 4 of a kind
        D: Full House
        C: 3 of a kind
        B: Two Pairs
        A: One Pair
        9: High Card
*/
char getType(std::string &hand){
    std::map<int, int> hand_map;
    for(char& c: hand){
        switch(c){
            case 'A': hand_map[std::stoi("E", nullptr, 16)]++; break;
            case 'K': hand_map[std::stoi("D", nullptr, 16)]++; break;
            case 'Q': hand_map[std::stoi("C", nullptr, 16)]++; break;
            case 'J': hand_map[std::stoi("B", nullptr, 16)]++; break;
            case 'T': hand_map[std::stoi("A", nullptr, 16)]++; break;
            default:  hand_map[std::stoi(std::string(1, c), nullptr, 16)]++;
        }
    }
    switch(hand_map.size()){
        case 1: return 'F';
        case 2: 
            for(auto& pair: hand_map){
                if(pair.second == 4 || pair.second == 1) return 'E';
                if(pair.second == 2 || pair.second == 3) return 'D';
            }
        case 3: 
            for(auto& pair: hand_map){
                if(pair.second == 3) return 'C';
                if(pair.second == 2) return 'B';
            }
        case 4: return 'A';
        case 5: return '9';
    }
    return '9';
}

long long getResult(std::map<int, int> &list){
    long long result = 0;
    int count = 1;
    for(auto& line: list){
        result += count * line.second;
        count++;
    }
    return result;
}

void printList(std::map<int, int> &list){
    for(auto& line: list){
        std::cout << line.first << " " << line.second << std::endl;
    }
    return;
}