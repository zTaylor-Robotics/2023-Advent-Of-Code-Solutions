#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <ctime>

void readFile(std::vector<std::vector<char>> &, std::ifstream &);
void printGalaxies(std::vector<std::vector<char>> &);
void expand(std::vector<std::vector<char>> &);
void map(std::vector<std::pair<int, int>> &, std::vector<std::vector<char>> &);
int getLengths(std::vector<std::pair<int, int>> &);
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::clock_t t = std::clock();

  std::string file_name = "./data.in";
  std::ifstream file(file_name);
  std::vector<std::vector<char>> galaxies;

  readFile(galaxies, file);
  expand(galaxies);
  // printGalaxies(galaxies);

  std::vector<std::pair<int, int>> gmap;
  map(gmap, galaxies);
  int results = getLengths(gmap);
  std::cout << "Total sum of lengths: " << results << std::endl;

  // system("pause");
  std::cout << "Total Execution time: "
            << (std::clock() - t) / (float)CLOCKS_PER_SEC << " seconds"
            << std::endl;
  return 0;
}

void readFile(std::vector<std::vector<char>> &gmap, std::ifstream &file) {
  std::string line;
  int rows = 0;
  bool exp_flag;

  while (file >> line) {
    gmap.push_back(std::vector<char>());
    exp_flag = true;
    for (char c : line) {
      gmap[rows].push_back(c);
      if (c == '#')
        exp_flag = false;
    }
    if (exp_flag) {
      gmap.push_back(std::vector<char>(gmap[rows].size(), '.'));
      rows++;
    }
    rows++;
  }
  return;
}

void printGalaxies(std::vector<std::vector<char>> &gmap) {
  for (auto rows : gmap) {
    for (auto cols : rows) {
      std::cout << cols;
    }
    std::cout << std::endl;
  }
  return;
}

void expand(std::vector<std::vector<char>> &gmap) {
  bool exp_flag = true;

  unsigned long j = 0;
  while (j < gmap[0].size()) {
    exp_flag = true;
    for (unsigned long i = 0; i < gmap.size(); i++) {
      if (gmap[i][j] == '#')
        exp_flag = false;
    }
    if (exp_flag) {
      for (auto &row : gmap) {
        row.insert(row.begin() + j, '.');
      }
      j++;
    }
    j++;
  }
  return;
}

void map(std::vector<std::pair<int, int>> &gmap,
         std::vector<std::vector<char>> &g) {
  for (unsigned long i = 0; i < g.size(); i++) {
    for (unsigned long j = 0; j < g[0].size(); j++) {
      if (g[i][j] == '#') {
        gmap.push_back({i, j});
      }
    }
  }
  std::cout << "Number of galaxies: " << gmap.size()
            << " Number of pairs: " << (gmap.size() * (gmap.size() - 1) / 2)
            << std::endl;
  return;
}

int getLengths(std::vector<std::pair<int, int>> &gmap) {
  int result = 0;
  for (unsigned long root = 0; root < gmap.size() - 1; root++) {
    for (unsigned long pair = root + 1; pair < gmap.size(); pair++) {
      result += abs((gmap[pair].first - gmap[root].first)) +
                abs((gmap[pair].second - gmap[root].second));
    }
  }
  return result;
}