#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// ========================================================== //
class BingoBoard {
public:
  array<int, 25>  board;
  array<bool, 25> marked;

  // ---------------------------------------------------------- //
  BingoBoard(string numbers) {
    string        number_string;
    istringstream number_stream(numbers);
    // cout << numbers << endl;
    int i = 0;
    while (getline(number_stream, number_string, ' ')) {
      if (number_string.length() == 0 || number_string.at(0) == ' ')
        continue;
      int n      = atoi(number_string.c_str());
      board[i++] = n;
    }

    for (bool& flag : marked)
      flag = false;
  }

  // ---------------------------------------------------------- //
  int operator()(int x, int y) { return board[x + y * 5]; }

  // ---------------------------------------------------------- //
  bool mark(int value) {
    for (int i = 0; i < board.size(); ++i) {
      if (board[i] == value) {
        marked[i] = true;
        return true;
      }
    }
    return false;
  }

  // ---------------------------------------------------------- //
  bool isMarked(int x, int y) { return marked[x + y * 5]; }

  // ---------------------------------------------------------- //
  bool hasBingo() {
    // check rows
    for (int row = 0; row < 5; ++row) {
      if (isMarked(0, row) && isMarked(1, row) && isMarked(2, row) &&
          isMarked(3, row) && isMarked(4, row))
        return true;
    }
    // check columns
    for (int col = 0; col < 5; ++col) {
      if (isMarked(col, 0) && isMarked(col, 1) && isMarked(col, 2) &&
          isMarked(col, 3) && isMarked(col, 4))
        return true;
    }
    // ---
    return false;
  }

  // ---------------------------------------------------------- //
  int unmarkedSum() {
    int sum = 0;
    for (int i = 0; i < board.size(); ++i)
      sum += marked[i] ? 0 : board[i];
    return sum;
  }

  // ---------------------------------------------------------- //
  string toString() {
    string content;
    for (int j = 0; j < 5; ++j) {
      for (int i = 0; i < 5; ++i) {
        int number = (*this)(i, j);
        number     = board[i + j * 5];
        if (number < 10)
          content.append(" ");
        content.append(to_string(number));
        content.append(" ");
      }
      content.append("\n");
    }
    return content;
  }
};

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
loadDrawnNumbers(string filename) {
  vector<int> result;
  ifstream    data;
  // --- open the file
  if (!loadFile(filename, data))
    return result;
  // --- load the draw numbers from the first line
  string line = "";
  while (getline(data, line, ','))
    result.push_back(atoi(line.c_str()));
  // ---
  cout << "loaded numbers" << endl;
  for (int i : result)
    cout << i << " ";
  cout << endl;
  // ---
  return result;
}

// ---------------------------------------------------------- //
vector<BingoBoard>
loadBoards(string filename) {
  vector<BingoBoard> result;
  ifstream           data;
  // --- open the file
  if (!loadFile(filename, data))
    return result;
  // --- load the draw numbers from the first line
  string line    = "";
  string numbers = "";
  while (getline(data, line)) {
    numbers.append(line);
    for (int i = 0; i < 4; ++i) {
      numbers.append(" ");
      getline(data, line);
      numbers.append(line);
    }
    // ---
    BingoBoard board{ numbers };
    result.push_back(board);
    // consume empty line
    getline(data, line);
    numbers.clear();
  }
  // ---
  cout << "loaded boards" << endl;
  for (BingoBoard board : result)
    cout << board.toString() << endl;

  return result;
}

// ---------------------------------------------------------- //
void
computeBestBoard() {
  cout << "load data" << endl;
  auto data   = loadDrawnNumbers("input_draw.dat");
  auto boards = loadBoards("input_boards.dat");

  bool        stop       = false;
  int         hit        = -1;
  int         last_num   = -1;
  BingoBoard* best_board = nullptr;
  for (int number : data) {
    last_num = number;
    hit      = -1;
    for (auto& board : boards) {
      ++hit;
      board.mark(number);
      if (board.hasBingo()) {
        stop       = true;
        best_board = &board;
        break;
      }
    }
    if (stop)
      break;
  }
  cout << "best board is:   " << hit << endl;
  cout << "sum of unmarked: " << best_board->unmarkedSum() << endl;
  cout << "last number:     " << last_num << endl;
  cout << "result:          " << last_num * best_board->unmarkedSum() << endl;
}

// ---------------------------------------------------------- //
void
computeWorstBoard() {
  cout << "load data" << endl;
  auto data   = loadDrawnNumbers("input_draw.dat");
  auto boards = loadBoards("input_boards.dat");

  bool        stop             = false;
  int         hit              = -1;
  int         last_num         = -1;
  BingoBoard* worst_board      = nullptr;
  int         remaining_boards = boards.size();
  for (int number : data) {
    last_num = number;
    hit      = -1;
    for (auto& board : boards) {
      ++hit;
      if (!board.hasBingo()) {
        board.mark(number);
        if (board.hasBingo())
          remaining_boards--;
      }
      if (remaining_boards == 0) {
        worst_board = &board;
        stop        = true;
      }
      if (stop)
        break;
    }
    if (stop)
      break;
  }
  cout << "worst board is:  " << hit << endl;
  cout << "sum of unmarked: " << worst_board->unmarkedSum() << endl;
  cout << "last number:     " << last_num << endl;
  cout << "result:          " << last_num * worst_board->unmarkedSum() << endl;
}

// ========================================================== //
int
main(int argc, char const* argv[]) {
  // computeBestBoard();
  computeWorstBoard();
  return 0;
}
