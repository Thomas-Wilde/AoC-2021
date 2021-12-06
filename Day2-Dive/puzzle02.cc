#include <fstream>
#include <iostream>

using namespace std;

bool
computePath(string data_file, int& hori, int& verti) {
  ifstream data(data_file);
  if (!data.is_open()) {
    cout << data_file << " not opened" << endl;
    return false;
  }
  // ---
  hori        = 0;
  verti       = 0;
  string line = "";
  while (getline(data, line)) {
    int dist = atoi(&line[line.length() - 1]);
    // cout << dist << endl;
    if (line.at(0) == 'f') {
      hori += dist;
      // cout << " forward" << endl;
    }
    if (line.at(0) == 'd')
      verti += dist;
    if (line.at(0) == 'u')
      verti -= dist;
  }
  return true;
}

bool
computePathWithAim(string data_file, int& hori, int& verti) {
  ifstream data(data_file);
  if (!data.is_open()) {
    cout << data_file << " not opened" << endl;
    return false;
  }
  // ---
  hori        = 0;
  verti       = 0;
  int    aim  = 0;
  string line = "";
  while (getline(data, line)) {
    int dist = atoi(&line[line.length() - 1]);
    // cout << dist << endl;
    if (line.at(0) == 'f') {
      hori += dist;
      verti += dist * aim;
    }
    if (line.at(0) == 'd')
      aim += dist;
    if (line.at(0) == 'u')
      aim -= dist;
  }
  return true;
}

int
main(int argc, char const* argv[]) {
  cout << "compute vertical and horitzontal position" << endl;
  int hori  = 0;
  int verti = 0;
  computePath("input.dat", hori, verti);
  cout << "horizontal: " << hori << endl;
  cout << "vertical:   " << verti << endl;
  cout << "product:    " << hori * verti << endl;

  hori  = 0;
  verti = 0;
  computePathWithAim("input.dat", hori, verti);
  cout << "compute path with aim" << endl;
  cout << "horizontal: " << hori << endl;
  cout << "vertical:   " << verti << endl;
  cout << "product:    " << hori * verti << endl;

  return 0;
}
