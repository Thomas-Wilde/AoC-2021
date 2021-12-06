#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// ========================================================== //
bool
loadFile(string filename, ifstream& data) {
  data.open(filename);
  if (!data.is_open()) {
    cout << filename << " not opened" << endl;
    return false;
  }
  return true;
}
// ---------------------------------------------------------- //
vector<int>
loadFishData(string filename) {
  vector<int> fishes;
  ifstream    data;
  // --- open the file
  if (!loadFile(filename, data))
    return fishes;
  // ---
  string fish = "";
  while (getline(data, fish, ','))
    fishes.push_back(atoi(fish.c_str()));

  cout << "loaded " << fishes.size() << "fishes" << endl;
  for (int i : fishes)
    cout << i << " ";
  cout << endl;
  return fishes;
}

// ---------------------------------------------------------- //
void
simulateFishes(vector<int>& fishes) {
  int content = fishes.size();
  for (int i = 0; i < content; ++i) {
    int& fish = fishes[i];
    fish--;
    if (fish == -1) {
      fish = 6;
      fishes.push_back(8);
    }
  }
}

// ---------------------------------------------------------- //
void
printFishes(vector<int>& fishes) {
  cout << fishes.size() << " fishes";
  if (fishes.size() < 30) {
    cout << ": ";
    for (int& val : fishes)
      cout << val << ",";
  }
  cout << endl;
}

// ---------------------------------------------------------- //
long
simulateFishPopulation(vector<int>& fishes, int days) {
  array<long, 9> days_to_breed;
  for (long& entry : days_to_breed)
    entry = 0;
  // ---
  for (int& fish : fishes)
    days_to_breed[fish]++;
  // ---
  for (int day = 0; day < days; ++day) {
    array<long, 9> next_day;
    next_day[0]   = days_to_breed[1];
    next_day[1]   = days_to_breed[2];
    next_day[2]   = days_to_breed[3];
    next_day[3]   = days_to_breed[4];
    next_day[4]   = days_to_breed[5];
    next_day[5]   = days_to_breed[6];
    next_day[6]   = days_to_breed[7] + days_to_breed[0];
    next_day[7]   = days_to_breed[8];
    next_day[8]   = days_to_breed[0];
    days_to_breed = next_day;
  }

  long count = 0;
  for (long& val : days_to_breed)
    count += val;
  return count;
}

// ========================================================== //
int
main(int argc, char const* argv[]) {
  // computeBestBoard();
  vector<int> fishes  = loadFishData("input_fish.dat");
  vector<int> fishes0 = loadFishData("input_fish.dat");
  cout << "Initial state:   ";
  printFishes(fishes);

  for (int i = 1; i < 257; ++i) {
    // simulateFishes(fishes);
    // cout << "After " << ((i < 10) ? " " : "") << i << " day(s): ";
    // printFishes(fishes);
    cout << "Simulate popula.: " << simulateFishPopulation(fishes0, i) << endl;
  }

  return 0;
}
