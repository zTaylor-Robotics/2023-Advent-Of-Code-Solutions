#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <time.h>
#include <vector>

void readFile(std::vector<std::vector<int>> &, std::ifstream &);
int getHistory(std::vector<int> &);

int main() {
  std::clock_t t = std::clock();

  std::string file_name = "./data.txt";
  std::ifstream file(file_name);

  std::vector<std::vector<int>> data;
  readFile(data, file);

  int ret = 0;

  for (auto &row : data) {
    ret += row[0] - getHistory(row);
  }

  std::cout << "Sum of History: " << ret << std::endl;
  // system("pause");
  std::cout << "Total Execution time: "
            << (std::clock() - t) / (float)CLOCKS_PER_SEC << " seconds"
            << std::endl;
  return 0;
}

void readFile(std::vector<std::vector<int>> &data, std::ifstream &file) {
  std::string line;
  int count = -1;

  while (std::getline(file, line)) {
    auto it = line.begin();
    auto its = it;
    data.push_back(std::vector<int>());
    count++;
    while (it != line.end()) {
      while (*it != ' ' && it != line.end()) {
        it++;
      }
      data[count].push_back(std::stoi(std::string(its, it)));
      if (it == line.end())
        break;
      it++;
      its = it;
    }
  }
  return;
}

int getHistory(std::vector<int> &row) {
  if (std::all_of(row.begin(), row.end(), [](int i) {
        if (i != 0)
          return false;
        return true;
      }))
    return 0;
  std::vector<int> temp;
  for (int i = 0; i < row.size() - 1; i++) {
    temp.push_back(row[i + 1] - row[i]);
  }

  int val = temp[0] - getHistory(temp);
  return val;
}