#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

#define EXPANSE 1000000

void readFile(std::vector<std::vector<char>> &, std::ifstream &);
void printGalaxies(std::vector<std::vector<char>> &);
void expand(std::vector<std::vector<char>> &);
void map(std::vector<std::pair<int, int>> &, std::vector<std::vector<char>> &);
long long getLengths(std::vector<std::pair<int, int>> &,
                     std::vector<std::vector<char>> &);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::clock_t t = std::clock();

  std::string file_name = "./data.in";
  std::ifstream file(file_name);
  std::vector<std::vector<char>> galaxies;

  readFile(galaxies, file);
  expand(galaxies);
  //printGalaxies(galaxies);

  std::vector<std::pair<int, int>> gmap;
  map(gmap, galaxies);

  long long results = getLengths(gmap, galaxies);
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
      for (auto &c : gmap[rows]) {
        c = '-';
      }
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

  int j = 0;
  while (j < gmap[0].size()) {
    exp_flag = true;
    for (int i = 0; i < gmap.size(); i++) {
      if (gmap[i][j] == '#')
        exp_flag = false;
    }
    if (exp_flag) {
      for (int i = 0; i < gmap.size(); i++) {
        gmap[i][j] = '|';
      }
    }
    j++;
  }
  return;
}

void map(std::vector<std::pair<int, int>> &gmap,
         std::vector<std::vector<char>> &g) {
  for (int i = 0; i < g.size(); i++) {
    for (int j = 0; j < g[0].size(); j++) {
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

long long getLengths(std::vector<std::pair<int, int>> &gmap,
                     std::vector<std::vector<char>> &g) {
  int s_count = 0;
  std::vector<int> cols(g[0].size(), 0);
  std::vector<int> rows(g[0].size(), 0);

  for (int i = 0; i < g.size(); i++) {
    if (g[i][0] == '-') {
      s_count++;
    }
    rows[i] = s_count;
  }

  s_count = 0;
  for (int j = 0; j < g.size(); j++) {
    if (g[0][j] == '|') {
      s_count++;
    }
    cols[j] = s_count;
  }

  long long result = 0;
  int temp_r = 0;
  int temp_c = 0;
  for (int root = 0; root < gmap.size() - 1; root++) {
    for (int pair = root + 1; pair < gmap.size(); pair++) {
      temp_r = (rows[gmap[pair].first] - rows[gmap[root].first]) * EXPANSE -
               1 * (rows[gmap[pair].first] - rows[gmap[root].first]);
      temp_c = (cols[gmap[pair].second] - cols[gmap[root].second]) * EXPANSE -
               1 * (cols[gmap[pair].second] - cols[gmap[root].second]);
      result += abs((gmap[pair].first + temp_r - gmap[root].first)) +
                abs((gmap[pair].second + temp_c - gmap[root].second));
      // std::cout << temp_r << " " << temp_c << std::endl;
    }
  }
  return result;
}