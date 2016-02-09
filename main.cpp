#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

using namespace std;

class TicTacToe {
  int **grid;
  int player, cpu, winner;
  int playerRow, playerCol, cpuRow, cpuCol;
  int freeCells;
  vector<vector<int>> cells;
  public:
    TicTacToe();
    ~TicTacToe();
    void showGrid();
    void runGame();
  private:
    bool pickSymbol();
    bool place(int, int, int);
    bool testWinner();
    void playerTurn();
    void cpuTurn();
    void setPlayerCoords();
    void setCpuCoords();
};

int main()
{
  TicTacToe game;
  game.runGame();
  return 0;
}

TicTacToe::TicTacToe() : winner(0), freeCells(9) {
  grid = new int*[3];
  for (unsigned int i=0; i<3; i++) {
    grid[i] = new int[3];
  }

  for (unsigned int i=0; i<3; i++) {
    for (unsigned int j=0; j<3; j++) {
      grid[i][j] = 0;
    }
  }

  for (int i=0; i<9; i++) {
    cells.push_back({i/3, i%3});
  }

  this->pickSymbol();
  this->showGrid();
}

TicTacToe::~TicTacToe() {
  for (unsigned int i=0; i<3; i++) {
    delete[] grid[i];
  }
  delete[] grid;
}

void TicTacToe::showGrid() {
  char c = ' ';
  cout << "    0" << "     1" << "     2" << endl;
  cout << "   ___" << "   ___" << "   ___" << endl;
  for (unsigned int i=0; i<3; i++) {
    cout << i;
    for (unsigned int j=0; j<3; j++) {
      if      (grid[i][j] == 0) { c = ' '; }
      else if (grid[i][j] == 1) { c = 'X'; }
      else                      { c = 'O'; }
      cout << " | " << c << " |";
    }
    cout << endl;
    cout << "   ---   ---   ---" << endl;
  }
}

bool TicTacToe::pickSymbol() {
  int a = 0;
  cout << "TicTacToe"<< endl << "Press '1' for 'X' or '2 for 'O': ";
  if (cin >> a) {
    if (a == 1 || a == 2) {
      player = a;
      cpu = (a == 1) ? 2 : 1;
      return true;
    }
  }
  cout << "Wrong input." << endl;
  return false;
}

bool TicTacToe::place(int row, int col, int who) {
  if ((row <= 2 && row >= 0) && (col <= 2 && col >= 0)) {
    if (grid[row][col] == 0) {
      grid[row][col] = who;
      freeCells--;
      return true;
    }
  }
  return false;
}

void TicTacToe::setPlayerCoords() {
  int row, col;
  cout << "Select position: ";
  if (cin >> row >> col) {
    playerRow = row;
    playerCol = col;
  } else {
    this->setPlayerCoords();
  }
}

void TicTacToe::setCpuCoords() {
  srand(time(0));
  int n = floor((float) rand() / (float) RAND_MAX * cells.size());
  vector<vector<int>>::iterator it = cells.begin();
  cpuRow = cells.at(n)[0];
  cpuCol = cells.at(n)[1];
  cells.erase(it + n);
}

void TicTacToe::cpuTurn() {
  this->setCpuCoords();
  while (!this->place(cpuRow, cpuCol, cpu)) {
    this->setCpuCoords();
  }
  this->showGrid();
}

void TicTacToe::playerTurn() {
  this->setPlayerCoords();
  this->place(playerRow, playerCol, player);
}

bool TicTacToe::testWinner() {
  if ((grid[0][0] == grid[1][1]) && (grid[1][1] == grid[2][2]) && (grid[0][0] != 0)) {
      winner = grid[0][0];
      return true;
  }
  if ((grid[2][0] == grid[1][1]) && (grid[1][1] == grid[0][2]) && (grid[2][0] != 0)) {
      winner = grid[2][0];
      return true;
  }
  for (unsigned int i=0; i<3; i++) {
    if ((grid[i][0] == grid[i][1]) && (grid[i][1] == grid[i][2]) && (grid[i][0] != 0)) {
      winner = grid[i][0];
      return true;
    }
    if ((grid[0][i] == grid[1][i]) && (grid[1][i] == grid[2][i]) && (grid[0][i] != 0)) {
      winner = grid[0][i];
      return true;
    }
  }
  return false;
}

void TicTacToe::runGame() {
  while (freeCells > 0) {
    this->playerTurn();
    if (this->testWinner()) {
      break;
    }
    if (freeCells > 0) {
      this->cpuTurn();
      if (this->testWinner()) {
        break;
      }
    }
  }
  this->showGrid();
  if (winner == 0) {
    cout << "Draw!";
  } else if (winner == player) {
    cout << "You win!";
  } else {
    cout << "You lose!";
  }
  cout << endl;
}



