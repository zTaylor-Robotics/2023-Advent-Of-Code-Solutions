#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <time.h>
#include <vector>

#define HORIZONTAL_PIPE '-'
#define VERTICAL_PIPE '|'
#define NE_JOINT 'L'
#define SE_JOINT 'F'
#define SW_JOINT '7'
#define NW_JOINT 'J'
#define START_POINT 'S'

std::pair<int, int> readFile(std::vector<std::vector<char>> &, std::ifstream &);
int getMaxDistance(std::pair<int, int> &, std::vector<std::vector<char>> &);
void getNextDir(std::vector<std::vector<char>> &, std::vector<int>&);
void print_map(std::vector<std::vector<char>> &);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::clock_t t = std::clock();

  std::string file_name = "./data.txt";
  std::ifstream file(file_name);

  std::pair<int, int> start_pos;
  std::vector<std::vector<char>> pipe_map;

  start_pos = readFile(pipe_map, file);

  std::cout << "Start Point: (" << start_pos.first << ", " << start_pos.second
            << ")" << std::endl;

  int answer = getMaxDistance(start_pos, pipe_map);
  std::cout << "Max Depth: " << answer << std::endl;
  // system("pause");
  std::cout << "Total Execution time: "
            << (std::clock() - t) / (float)CLOCKS_PER_SEC << " seconds"
            << std::endl;
  return 0;
}

std::pair<int, int> readFile(std::vector<std::vector<char>> &pmap,
                             std::ifstream &file) {
  std::string line;
  std::pair<int, int> start_pos = {0, 0};
  int vdepth = 0;
  int hdepth = 0;
  while (file >> line) {
    pmap.push_back(std::vector<char>());
    for (char &c : line) {
      if (c == START_POINT)
        start_pos = {vdepth, hdepth};
      pmap[vdepth].push_back(c);
      hdepth++;
    }
    vdepth++;
    hdepth = 0;
  }
  return start_pos;
}

int getMaxDistance(std::pair<int, int> &start_pos,
                   std::vector<std::vector<char>> &pmap) {
  std::vector<std::vector<char>> path_map(
      pmap.size(), std::vector<char>(pmap[0].size(), '.'));


  // print_map(path_map);
  //  establish the followers and their depth level
  std::vector<int> pf1 = {start_pos.first, start_pos.second, 0}; //0 equals current move direction
  int depth = 0;
  std::vector<int> pf2 = {start_pos.first, start_pos.second, 0}; //0 equals current move direction

  path_map[pf1[0]][pf1[1]] = pmap[pf1[0]][pf1[1]];

  int sy = start_pos.first; int sx = start_pos.second;
  //first step is to determine the directions of the pipes leading from start
  //the next direction to move is based on int values, 1 = North, 2 = East, 3 = South, 4 = West
  if(pmap[sy - 1][sx] == '7' || pmap[sy - 1][sx] == '|' || pmap[sy - 1][sx] == 'F') pf1[2] = 1;
  if(pmap[sy][sx+1] == '7' || pmap[sy - 1][sx] == '-' || pmap[sy - 1][sx] == 'J'){
    if(pf1[2] > 0 && pf2[2] == 0) pf2[2] = 2;
    else if(pf1[2] == 0) pf1[2] = 2;
  }
  if(pmap[sy - 1][sx] == 'J' || pmap[sy - 1][sx] == '|' || pmap[sy - 1][sx] == 'L'){
    if(pf1[2] > 0 && pf2[2] == 0) pf2[2] = 3;
    else if(pf1[2] == 0) pf1[2] = 3;
  }
  if(pmap[sy - 1][sx] == 'L' || pmap[sy - 1][sx] == '-' || pmap[sy - 1][sx] == 'F'){
    if(pf1[2] > 0 && pf2[2] == 0) pf2[2] = 4;
    else if(pf1[2] == 0) pf1[2] = 4;
  }

  std::cout << pf1[2] << " " << pf2[2] << std::endl;
  depth++;
  getNextDir(pmap, pf1);
  getNextDir(pmap, pf2);

  // start with both followers and trace the pipe
  while (path_map[pf1[0]][pf1[1]] == '.' ||
         path_map[pf2[0]][pf2[1]] == '.') {
    // add current element to the path_map for tracking to see if pf1 or pf2
    // crosses paths at some point
    path_map[pf1[0]][pf1[1]] = pmap[pf1[0]][pf1[1]];
    path_map[pf2[0]][pf2[1]] = pmap[pf2[0]][pf2[1]];
    getNextDir(pmap, pf1);
    getNextDir(pmap, pf2);
    depth++;
    //go to the next iteration of the path
  }
  print_map(path_map);
  return depth - 1;
}

void getNextDir(std::vector<std::vector<char>> &pmap, std::vector<int>&follower){
  switch(follower[2]){
  case 1: //north
    if(pmap[follower[0] - 1][follower[1]] == '7') follower[2] = 4;
    else if(pmap[follower[0] - 1][follower[1]] == '|') follower[2] = 1;
    else follower[2] = 2;
    follower[0]--; 
    return;

  case 2: //east
    if(pmap[follower[0]][follower[1] + 1] == '7') follower[2] = 3;
    else if(pmap[follower[0]][follower[1] + 1] == '-') follower[2] = 2;
    else follower[2] = 1;
    follower[1]++; 
    return;

  case 3: //south
    if(pmap[follower[0] + 1][follower[1]] == 'L') follower[2] = 2;
    else if(pmap[follower[0] + 1][follower[1]] == '|') follower[2] = 3;
    else follower[2] = 4;
    follower[0]++; 
    return;

  case 4: //west
    if(pmap[follower[0]][follower[1] - 1] == 'L') follower[2] = 1;
    else if(pmap[follower[0]][follower[1] - 1] == '-') follower[2] = 4;
    else follower[2] = 3;
    follower[1]--; 
    return;
  }

  return;
}

void print_map(std::vector<std::vector<char>> &pmap) {
  for (auto &row : pmap) {
    for (auto &column : row) {
      std::cout << column;
    }
    std::cout << std::endl;
  }
  return;
}
