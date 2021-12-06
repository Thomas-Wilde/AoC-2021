#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<string>
loadData(string filename) {
  vector<string> result;

  ifstream data(filename);
  if (!data.is_open()) {
    cout << filename << " not opened" << endl;
    return result;
  }
  // ---
  string line = "";
  while (getline(data, line))
    result.push_back(line);
  return result;
}

vector<int>
computeReport(vector<string> binary_numbers) {
  // ---
  int         digits = 12;
  vector<int> one_counts;
  one_counts.resize(digits);

  for (int i = 0; i < digits; ++i) {
    for (string number : binary_numbers)
      if (number.at(i) == '1')
        ++one_counts[i];
  }
  // for (int val : one_counts)
  //   cout << val << "  ";
  // cout << endl;

  return one_counts;
}

void
convertToDecimal(vector<int> one_counts, int data_size) {
  int gamma   = 0;
  int epsilon = 0;
  int mask    = 1;

  for (int i = one_counts.size() - 1; i >= 0; --i) {
    if (one_counts[i] - (data_size / 2) > 0)
      gamma = gamma | mask;
    else
      epsilon = epsilon | mask;
    mask *= 2;
  }

  cout << "γ = " << gamma << endl;
  cout << "ε = " << epsilon << endl;
  cout << "γ*ε = " << gamma * epsilon << endl;
}

// ---------------------------------------------------------- //
int
convertToDecimal(string binary) {
  int mask  = 1;
  int value = 0;

  for (int i = binary.length() - 1; i >= 0; --i) {
    if (binary.at(i) == '1')
      value = value | mask;
    mask *= 2;
  }
  return value;
}

int
computeOxygen(vector<string> data, int bit_pos) {
  if (data.size() == 1) {
    cout << data[0] << " " << bit_pos << endl;
    return convertToDecimal(data[0]);
  }

  for (auto val : data)
    cout << val << endl;
  cout << "---" << endl;
  cout << bit_pos << endl;
  cout << "---" << endl;

  auto one_counts = computeReport(data);
  for (auto val : one_counts)
    cout << val << endl;
  cout << "===" << endl;

  vector<string> sub_data;
  // auto-format:off
  for (string val : data) {
    if ((one_counts[bit_pos] >= data.size() / 2.0) && (val.at(bit_pos) == '1'))
      sub_data.push_back(val);
    if ((one_counts[bit_pos] < data.size() / 2.0) && (val.at(bit_pos) == '0'))
      sub_data.push_back(val);
  }
  return computeOxygen(sub_data, bit_pos + 1);
}

int
computeCO2(vector<string> data, int bit_pos) {
  if (data.size() == 1) {
    cout << data[0] << " " << bit_pos << endl;
    return convertToDecimal(data[0]);
  }

  for (auto val : data)
    cout << val << endl;
  cout << "---" << endl;

  auto one_counts = computeReport(data);

  vector<string> sub_data;
  // auto-format:off
  if (one_counts[bit_pos] < (data.size() / 2.0))
    for (string val : data)
      if (val.at(bit_pos) == '1')
        sub_data.push_back(val);

  if (one_counts[bit_pos] >= (data.size() / 2.0))
    for (string val : data)
      if (val.at(bit_pos) == '0')
        sub_data.push_back(val);

  return computeCO2(sub_data, bit_pos + 1);
}

int
main(int argc, char const* argv[]) {
  cout << "load data" << endl;
  auto data = loadData("input.dat");
  auto ones = computeReport(data);
  convertToDecimal(ones, data.size());

  int o2  = computeOxygen(data, 0);
  int co2 = computeCO2(data, 0);
  cout << " O2 = " << o2 << endl;
  cout << "CO2 = " << co2 << endl;
  cout << "O2 * CO2 = " << o2 * co2 << endl;

  return 0;
}
