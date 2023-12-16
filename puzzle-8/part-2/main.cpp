#include <time.h>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

void getTurnList(std::vector<bool> &, std::ifstream &);
void getMap(std::map<std::string, std::pair<std::string, std::string>> &,
            std::map<std::string, char> &, std::ifstream &);
bool checkGhosts(std::map<std::string, char> &);
long long
getNumSteps(std::map<std::string, std::pair<std::string, std::string>> &,
            std::map<std::string, char> &, std::vector<bool> &);

void printMap(std::map<std::string, std::pair<std::string, std::string>> &);

int main() {
  std::clock_t tot = std::clock();

  // stores the file to be pointed to later
  std::string file_name = "./puzzle-8.txt";
  std::ifstream file(file_name);

  // get the list of turns made
  std::vector<bool> turn_list;
  getTurnList(turn_list, file); // Fetches the turns from the file

  // create map containing all the steps as [key][value] pairs where the key is
  // the milestone and the value is a pair(left milestone,right milestone)
  std::map<std::string, std::pair<std::string, std::string>> ms_map;
  std::map<std::string, char> ghost_map;
  getMap(ms_map, ghost_map, file);

  // this is a very bruteforce method for getting the number of steps
  // primarily because of the puzzle context
  long long numsteps = getNumSteps(ms_map, ghost_map, turn_list);

  std::cout << "Number of Steps: " << numsteps << std::endl;

  // system("pause");
  std::cout << "Total Execution time: "
            << (std::clock() - tot) / (float)CLOCKS_PER_SEC << " seconds"
            << std::endl;
  return 0;
}

void getTurnList(std::vector<bool> &list, std::ifstream &file) {
  std::string line;
  std::getline(file, line);

  for (char &c : line) {
    if (c == 'L')
      list.push_back(false);
    else if (c == 'R')
      list.push_back(true);
  }

  std::getline(file, line); // get the blank line underneath the turn list
  return;
}

void getMap(std::map<std::string, std::pair<std::string, std::string>> &map,
            std::map<std::string, char> &gmap, std::ifstream &file) {
  std::string line, key, left, right;

  while (std::getline(file, line)) {
    key = line.substr(0, 3);
    left = line.substr(7, 3);
    right = line.substr(12, 3);
    map[key] = std::pair<std::string, std::string>(left, right);
    if (key[2] == 'A')
      gmap[key] = key[2];
  }

  return;
}

bool checkGhosts(std::map<std::string, char> &gmap) {
  for (auto &ghost : gmap) {
    if (ghost.second != 'Z')
      return 0;
  }
  return 1;
}

// this took much longer to get to the solution than desired
// it turns out that the ghosts paths are cyclic and the distance from a -> z =
// distance from z -> z this means that once we get the length of each path from
// the start we can find the least common multiple for all of the the paths and
// that will be the puzzles answer
long long
getNumSteps(std::map<std::string, std::pair<std::string, std::string>> &map,
            std::map<std::string, char> &gmap, std::vector<bool> &step) {
  int count = 0;
  int vect_it = 0;
  char check = ' ';
  std::string gtemp;
  long long result = 0;
  std::vector<long long> ghosts;

  // gets the number of steps to get to the first z which = the num of steps to
  // the next z
  for (auto &ghost : gmap) {
    vect_it = 0;
    count = 0;
    check = ghost.second;
    gtemp = ghost.first;

    while (check != 'Z') {
      if (vect_it == step.size())
        vect_it = 0;
      if (step[vect_it])
        gtemp = map[gtemp].second;
      else
        gtemp = map[gtemp].first;
      check = gtemp[2];
      vect_it++;
      count++;
    }
    ghosts.push_back(count);
  }

  // get LCM of the ghost paths
  result = ghosts[0];
  for (int i = 1; i < ghosts.size(); i++) {
    result = std::lcm(result, ghosts[i]);
  }

  return result;
}

void printMap(std::map<std::string, std::pair<std::string, std::string>> &map) {
  for (auto &row : map) {
    std::cout << row.first << " = (" << row.second.first << ", "
              << row.second.second << ")" << std::endl;
  }
  return;
}
