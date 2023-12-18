#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <time.h>
#include <vector>

#define PIPE_CHAR ' '
#define HORIZONTAL_PIPE '-'
#define VERTICAL_PIPE '|'
#define NE_JOINT 'L'
#define SE_JOINT 'F'
#define SW_JOINT '7'
#define NW_JOINT 'J'
#define START_POINT 'S'
#define ASSUMPTION                                                             \
  false // 0 for one assumption 1 for another assumption for our first
        // definition
        // of internal edge

std::pair<int, int> readFile(std::vector<std::vector<char>> &, std::ifstream &);
void getPathMap(std::pair<int, int> &, std::vector<std::vector<char>> &,
                std::map<std::pair<int, int>, std::vector<bool>> &);
void getNextDir(std::vector<std::vector<char>> &, std::vector<int> &);
void addEdge(std::vector<std::vector<char>> &,
             std::map<std::pair<int, int>, std::vector<bool>> &,
             std::vector<int> &, std::pair<bool, bool> &);
int findIntSpaces(std::vector<std::vector<char>> &,
                  std::map<std::pair<int, int>, std::vector<bool>> &);
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

  std::map<std::pair<int, int>, std::vector<bool>> edges;
  getPathMap(start_pos, pipe_map, edges);
  print_map(pipe_map);
  std::cout << std::endl;
  int num_enclosed = findIntSpaces(pipe_map, edges);
  print_map(pipe_map);

  std::cout << "Number of enclosed spaces = " << num_enclosed << std::endl;
  // print_map(pipe_map);
  //  system("pause");
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

void getPathMap(std::pair<int, int> &start_pos,
                std::vector<std::vector<char>> &pmap,
                std::map<std::pair<int, int>, std::vector<bool>> &edge_map) {

  std::vector<std::vector<char>> path_map(
      pmap.size(), std::vector<char>(pmap[0].size(), '0'));

  std::vector<bool> temp_edge_def = {1, 1, 1,
                                     1}; // 0 = outside edge, 1 = inside edge

  //---CAPTURE INIITIAL STATES---
  // first step is to determine the directions of the pipes leading from start
  // the next direction to move is based on int values, 1 = North, 2 = East, 3 =
  // South, 4 = West
  std::vector<int> pf1 = {start_pos.first, start_pos.second,
                          0}; // 0 equals current move direction
  path_map[pf1[0]][pf1[1]] =
      PIPE_CHAR; // chart the first path element in the path map

  int sy = start_pos.first;
  int sx = start_pos.second;

  if (sy != 0) {
    if (pmap[sy - 1][sx] == '7' || pmap[sy - 1][sx] == '|' ||
        pmap[sy - 1][sx] == 'F') {
      if (pf1[2] == 0)
        pf1[2] = 1;
      temp_edge_def[0] = 0;
    }
  }
  if (sx != 0) {
    if (pmap[sy][sx - 1] == 'L' || pmap[sy][sx - 1] == '-' ||
        pmap[sy][sx - 1] == 'F') {
      if (pf1[2] == 0)
        pf1[2] = 4;
      temp_edge_def[3] = 0;
    }
  }
  if (pmap[sy][sx + 1] == '7' || pmap[sy][sx + 1] == '-' ||
      pmap[sy][sx + 1] == 'J') {
    if (pf1[2] == 0)
      pf1[2] = 2;
    temp_edge_def[1] = 0;
  }
  if (pmap[sy + 1][sx] == 'J' || pmap[sy + 1][sx] == '|' ||
      pmap[sy + 1][sx] == 'L') {
    if (pf1[2] == 0)
      pf1[2] = 3;
    temp_edge_def[2] = 0;
  }

  // give temp_edge_def its intial values
  if (!temp_edge_def[0] && !temp_edge_def[1]) {
    temp_edge_def[2] = ASSUMPTION; // L
    temp_edge_def[3] = ASSUMPTION;
  } else if (!temp_edge_def[0] && !temp_edge_def[2]) {
    temp_edge_def[1] = !ASSUMPTION; //|
    temp_edge_def[3] = ASSUMPTION;
  } else if (!temp_edge_def[0] && !temp_edge_def[3]) {
    temp_edge_def[1] = !ASSUMPTION; // J
    temp_edge_def[2] = !ASSUMPTION;
  } else if (!temp_edge_def[1] && !temp_edge_def[2]) {
    temp_edge_def[0] = ASSUMPTION; // F
    temp_edge_def[3] = ASSUMPTION;
  } else if (!temp_edge_def[1] && !temp_edge_def[3]) {
    temp_edge_def[0] = ASSUMPTION; //-
    temp_edge_def[2] = !ASSUMPTION;
  } else if (!temp_edge_def[2] && !temp_edge_def[3]) {
    temp_edge_def[0] = ASSUMPTION; // 7
    temp_edge_def[1] = ASSUMPTION;
  }

  // store the S point into the edge map
  edge_map[{sy, sx}] = temp_edge_def;

  // set initial inheritance
  std::pair<bool, bool> inheritance = {ASSUMPTION, !ASSUMPTION};

  getNextDir(pmap, pf1); // grabs the next section of the pipe and the
                         // direction its outlet goes to
  //----TRACE THE PIPE AND CREATE EDGE MAP----
  while (path_map[pf1[0]][pf1[1]] == '0') {
    // add current element to the path_map for tracking to see if pf1 goes back
    // to origin
    path_map[pf1[0]][pf1[1]] = PIPE_CHAR; // P is for Pipe
    addEdge(pmap, edge_map, pf1, inheritance);
    getNextDir(pmap, pf1);
    // go to the next iteration of the path
  }
  pmap = path_map;
  return;
}

void getNextDir(std::vector<std::vector<char>> &pmap,
                std::vector<int> &follower) {
  switch (follower[2]) {
  case 1: // north
    if (pmap[follower[0] - 1][follower[1]] == '7')
      follower[2] = 4;
    else if (pmap[follower[0] - 1][follower[1]] == '|')
      follower[2] = 1;
    else
      follower[2] = 2;
    follower[0]--;
    return;

  case 2: // east
    if (pmap[follower[0]][follower[1] + 1] == '7')
      follower[2] = 3;
    else if (pmap[follower[0]][follower[1] + 1] == '-')
      follower[2] = 2;
    else
      follower[2] = 1;
    follower[1]++;
    return;

  case 3: // south
    if (pmap[follower[0] + 1][follower[1]] == 'L')
      follower[2] = 2;
    else if (pmap[follower[0] + 1][follower[1]] == '|')
      follower[2] = 3;
    else
      follower[2] = 4;
    follower[0]++;
    return;

  case 4: // west
    if (pmap[follower[0]][follower[1] - 1] == 'L')
      follower[2] = 1;
    else if (pmap[follower[0]][follower[1] - 1] == '-')
      follower[2] = 4;
    else
      follower[2] = 3;
    follower[1]--;
    return;
  }

  return;
}

void addEdge(std::vector<std::vector<char>> &pmap,
             std::map<std::pair<int, int>, std::vector<bool>> &emap,
             std::vector<int> &pf, std::pair<bool, bool> &in) {
  char pipe = pmap[pf[0]][pf[1]];
  int next_dir = pf[2];
  switch (pipe) {
  case 'L':
    if (next_dir == 1) {
      emap[{pf[0], pf[1]}] = {false, false, in.first, in.first};
      return;
    }
    emap[{pf[0], pf[1]}] = {false, false, in.second, in.second};
    return;
  case '|':
    if (next_dir == 1) {
      emap[{pf[0], pf[1]}] = {false, in.second, false, in.first};
      return;
    }
    emap[{pf[0], pf[1]}] = {false, in.first, false, in.second};
    return;
  case 'J':
    if (next_dir == 1) {
      emap[{pf[0], pf[1]}] = {false, in.second, in.second, false};
      return;
    }
    emap[{pf[0], pf[1]}] = {false, in.first, in.first, false};
    return;
  case 'F':
    if (next_dir == 2) {
      emap[{pf[0], pf[1]}] = {in.first, false, false, in.first};
      return;
    }
    emap[{pf[0], pf[1]}] = {in.second, false, false, in.second};
    return;
  case '-':
    if (next_dir == 2) {
      emap[{pf[0], pf[1]}] = {in.first, false, in.second, false};
      return;
    }
    emap[{pf[0], pf[1]}] = {in.second, false, in.first, false};
    return;
  case '7':
    if (next_dir == 3) {
      emap[{pf[0], pf[1]}] = {in.first, in.first, false, false};
      return;
    }
    emap[{pf[0], pf[1]}] = {in.second, in.second, false, false};
    return;
  }
}

int findIntSpaces(std::vector<std::vector<char>> &pmap,
                  std::map<std::pair<int, int>, std::vector<bool>> &emap) {
  bool flag;
  int count = 0;
  for (int i = 1; i < pmap.size() - 1; i++) {
    for (int j = 1; j < pmap[0].size() - 1; j++) {
      flag = false;
      if (pmap[i][j] == '0') {
        if (pmap[i - 1][j] == '0' || pmap[i][j - 1] == '0')
          flag = false; // if 0 is above, this means that this zero is connect
                        // to the outside so move on
        else if (pmap[i - 1][j] == 'I' ||
                 pmap[i][j - 1] == 'I') { // if either of these are I, then we
                                          // can assume that this is also I
          flag = true;
        } else {
          // check north for inside or outside if inside we know that this space
          // is inside
          if (pmap[i - 1][j] == PIPE_CHAR) {
            if (emap[{i - 1, j}][2])
              flag = true;
          }
          // check east for inside or outside
          if (pmap[i][j + 1] == PIPE_CHAR) {
            if (emap[{i, j + 1}][3])
              flag = true;
          }
          // check south for inside or outside
          if (pmap[i + 1][j] == PIPE_CHAR) {
            if (emap[{i + 1, j}][0])
              flag = true;
          }
          // check west for inside or outside
          if (pmap[i][j - 1] == PIPE_CHAR) {
            if (emap[{i, j - 1}][1])
              flag = true;
          }
        }
        if (flag) {
          count++;
          pmap[i][j] = 'I';
        }
      }
    }
  }
  return count;
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
