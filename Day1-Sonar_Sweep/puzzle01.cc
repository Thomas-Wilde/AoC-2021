#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<int>
loadData(string filename) {
  vector<int> result;

  ifstream data(filename);
  if (!data.is_open()) {
    cout << filename << " not opened" << endl;
    return result;
  }
  // ---
  string line = "";
  while (getline(data, line))
    result.push_back(atoi(line.c_str()));
  return result;
}

// ---------------------------------------------------------- //
int
computeInreaseCount(vector<int> data) {
  int count = 0;
  for (int i = 0; i < data.size() - 1; ++i)
    if (data[i] < data[i + 1])
      ++count;
  return count;
}

// ---------------------------------------------------------- //
int
computeInreaseCountWindow(vector<int> data, int window_size) {
  int count = 0;
  for (int i = 0; i < data.size() - window_size; ++i) {
    int val_A = 0;
    int val_B = 0;
    for (int j = 0; j < window_size; ++j) {
      val_A += data[i + j];
      val_B += data[i + j + 1];
    }
    if (val_A < val_B)
      count++;
  }
  return count;
}

int
main(int argc, char const* argv[]) {
  cout << "loading data" << endl;
  auto data = loadData("input.dat");
  cout << "number of increases: ";
  cout << computeInreaseCount(data) << endl;
  cout << "number of increases in window: ";
  cout << computeInreaseCountWindow(data, 3) << endl;

  return 0;
}
