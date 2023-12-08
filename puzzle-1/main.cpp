#include <iostream>
#include <fstream>
#include <string>

char isNumInString(std::string);

int main(){
    int ans = 0; int count = 0; int test = 0;
    char first, last, tmpc;
    std::string temp, num, line;
    std::ifstream ifs("../../puzzle-1.txt");
    
    while(std::getline(ifs, line)){
        count = 0;
        first = ' ';
        last = ' ';
        temp.clear();
        num.clear();
        for(char& c: line){
            test = isNumInString(num);
            if((int(test) - int('0')) > 0){
                num = num.back();
                if(count == 0){
                    first = test;
                    count++;
                }
                last = test;
                if(isdigit(c)){
                    last = c;
                }else num += c;
            }else if(isdigit(c)){
                num.clear();
                if(count == 0){
                    first = c;
                    count++;
                }
                last = c;
            }else{
                num += c;
            }
        }
        test = isNumInString(num);
        if((int(test) - int('0')) > 0){
            num.clear();
            if(count == 0){
                first = test;
                count++;
            }
            last = test;
        }
        temp += first;
        temp += last;
        ans += stoi(temp);
    }
    ifs.close();

    std::cout << ans << std::endl;

    system("pause");
    return 0;
}

char isNumInString(std::string num){
    if(num.find("one") != std::string::npos) return '1';
    if(num.find("two") != std::string::npos) return '2';
    if(num.find("three") != std::string::npos) return'3';
    if(num.find("four") != std::string::npos) return '4';
    if(num.find("five") != std::string::npos) return '5';
    if(num.find("six") != std::string::npos) return '6';
    if(num.find("seven") != std::string::npos) return '7';
    if(num.find("eight") != std::string::npos) return '8';
    if(num.find("nine") != std::string::npos) return '9';
    return '0';
}
