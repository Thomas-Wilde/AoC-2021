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

// ========================================================== //
struct Point {
  int x = 0;
  int y = 0;
};

class Line {
public:
  Point p0;
  Point p1;

  // ---------------------------------------------------------- //
  Line(string input) {
    istringstream coords_stream(input);
    string        coords_string;
    int           x = 0;
    int           y = 0;
    // ---
    getline(coords_stream, coords_string, ',');
    x = atoi(coords_string.c_str());
    getline(coords_stream, coords_string, ' ');
    y  = atoi(coords_string.c_str());
    p0 = { x, y };
    getline(coords_stream, coords_string, '>');
    getline(coords_stream, coords_string, ' ');
    getline(coords_stream, coords_string, ',');
    x = atoi(coords_string.c_str());
    getline(coords_stream, coords_string);
    y  = atoi(coords_string.c_str());
    p1 = { x, y };
  }

  string toString() {
    string result = to_string(p0.x);
    result.append(",");
    result.append(to_string(p0.y));
    result.append(" -> ");
    result.append(to_string(p1.x));
    result.append(",");
    result.append(to_string(p1.y));
    result.append("\n");
    return result;
  }
};

// ========================================================== //
class VentureGrid {
public:
  int          max_x = -1;
  int          max_y = -1;
  vector<Line> lines;
  vector<int>  floor;

  // ---------------------------------------------------------- //
  void loadLines(string filename) {
    ifstream data;
    // --- open the file
    if (!loadFile(filename, data))
      return;
    // --- load the draw numbers from the first line
    string content = "";
    while (getline(data, content)) {
      Line line(content);
      max_x = max(max(line.p0.x, max_x), line.p1.x);
      max_y = max(max(line.p0.y, max_y), line.p1.y);
      lines.push_back(line);
      cout << line.toString();
    }
    cout << "loaded " << lines.size() << " lines" << endl;
  }

  // ---------------------------------------------------------- //
  int& operator()(int x, int y) { return floor[x + (max_x + 1) * y]; }
  int& operator()(Point pt) { return floor[pt.x + (max_x + 1) * pt.y]; }

  // ---------------------------------------------------------- //
  int countOverlaps(int min) {
    int count = 0;
    for (int& entry : floor)
      count += entry >= min ? 1 : 0;
    return count;
  }

  // ---------------------------------------------------------- //
  void computeFloor() {
    floor.resize((max_x + 1) * (max_y + 1));
    for (int& entry : floor)
      entry = 0;
    for (Line line : lines) {
      int dx = line.p0.x < line.p1.x ? 1 : -1;
      int dy = line.p0.y < line.p1.y ? 1 : -1;
      if (line.p0.x == line.p1.x)
        dx = 0;
      if (line.p0.y == line.p1.y)
        dy = 0;
      // if (dx != 0 && dy != 0)
      //   continue;
      int x = line.p0.x;
      int y = line.p0.y;
      (*this)(x, y) += 1;
      do {
        x += dx;
        y += dy;
        (*this)(x, y) += 1;
      } while (x != line.p1.x || y != line.p1.y);
    }
  }

  // ---------------------------------------------------------- //
  string toString() {
    string result = "";
    for (int y = 0; y < max_y + 1; ++y) {
      for (int x = 0; x < max_x + 1; ++x) {
        int&   value = (*this)(x, y);
        string item  = (value == 0) ? "." : to_string(value);
        result.append(item);
      }
      result.append("\n");
    }
    return result;
  }
};

// ========================================================== //
int
main(int argc, char const* argv[]) {
  // computeBestBoard();
  VentureGrid grid;
  grid.loadLines("input_lines.dat");
  cout << "xₘₐₓ: " << grid.max_x << endl;
  cout << "yₘₐₓ: " << grid.max_y << endl;
  grid.computeFloor();
  cout << endl;
  cout << grid.toString();
  cout << endl;
  cout << "overlaps of 2: " << grid.countOverlaps(2) << endl;
  return 0;
}
