#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <time.h>

void readFile(std::ifstream &);

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    std::clock_t t = std::clock();

    std::string file_name = "./data.in";
    std::ifstream file(file_name);

    //system("pause");
    std::cout << "Total Execution time: " <<  (std::clock() - t ) / (float)CLOCKS_PER_SEC << " seconds" << std::endl;
    return 0;
}

void readFile(std::ifstream &file){
    std::string line;

    while(file >> line){

    }
    return;
}
