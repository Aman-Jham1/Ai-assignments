/*
    AI Assignment-1.
    Aman Jham - 2019A7PS0071H
    R Vedang - 
    Shubh - 
*/

#include <bits/stdc++.h>

using namespace std;
#define all(x) x.begin(), x.end()
#define sz(x) static_cast<int32_t>(x.size())

class Board {
private:
    vector <int> board;
public:
    Board() {
        board.resize(12);
    }
    vector <int> get_board() {
        return this->board;
    }
    void set_board(vector <int> board) {
        this->board = board;
    }
    vector <int> operate(int sector_no, int type) {
        vector <int> new_board(12);
        new_board = board;
        /*
            OPeration accordingly.
        */
        this->board = new_board;
        return board;
    }
    vector <Board> get_all_states() {
        vector <Board> nextstates;
        return nextstates;
    }
    int heuristic_val(Board &goalstate) {
        int heuristic = 0;
        vector <int> goalboard = goalstate.get_board();
        for (int i = 0; i < 12; ++i) {
            heuristic += this->board[i] == goalboard[i];
        }
        return heuristic;
    }
    bool is_better(Board &other, Board &goal) {
        return this->heuristic_val(goal) < other.heuristic_val(goal); 
    }
    bool operator == (Board &other) {
        return this->board == other.get_board();
    }
    void operator = (Board &other) {
        this->board = other.get_board();
    }
    bool operator != (Board &other) {
        return this->board != other.get_board();
    }
};

// int heuristic_val(Board &b1, Board &b2) {
//     int val = 0;
//     vector <int> board1 = b1.get_board();
//     vector <int> board2 = b2.get_board();
//     for (int i = 0; i < 12; ++i) {
//         if (board1[i] == board2[i]) {
//             val++;
//         }
//     }
//     return val;
// }

void print(vector <Board> &path) {
    for (int i = 0; i < path.size(); ++i) {
        cout << "State " << i << " : ";
        for (auto x : path[i].get_board()) {
            cout << x << " ";
        }
        cout << '\n';
    }
    return;
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); 
  Board startstate;
  vector <int> vals;
  for (int i = 0; i < 12; ++i) {
    cin >> vals[i];
  }
  startstate.set_board(vals);
  Board goalstate;
  for (int i = 0; i < 12; ++i) {
    cin >> vals[i];
  }
  goalstate.set_board(vals);
  vector <Board> path;
  if (startstate == goalstate) {
    cout << "Start state is goalstate state, 0 steps nedded.\n";
    return 0;
  }
  // def steepest_ascent_hill_climbing(maze):
  //   currentstate = maze.startstate
  //   goalstate = maze.goalstate
  //   path = [currentstate]
  //   SUCC = currentstate
  //   while currentstate != goalstate:
  //       prevstate = currentstate
  //       for state in maze.nextstate(currentstate):
  //           if state == goalstate:
  //               path.append(state)
  //               return path, SOLUTION_FOUND
  //           SUCC = state
  //           if maze.is_better(SUCC, currentstate):
  //               currentstate = SUCC
  //       if currentstate == prevstate:
  //           return path, SOLUTION_NOT_FOUND
  //       path.append(currentstate)
  //   return path, SOLUTION_FOUND
  path.push_back(startstate);
  Board currentstate = startstate;
  Board SUCC = currentstate;
  while (currentstate != startstate) {
    Board prevstate = currentstate;
    vector <Board> nextstates = currentstate.get_all_states();
    for (auto state : nextstates) {
        if (state == goalstate) {
            path.push_back(state);
            cout << "SOLUTION FOUND\n";
            print(path);
            return 0;
        }
        SUCC = state;
        if (SUCC.is_better(currentstate, goalstate)) {
            currentstate = SUCC;
        }
    }
    if (currentstate == prevstate) {
        cout << "NO SOLUTION FOUND\n";
        print(path);
        return 0;
    }
    path.push_back(currentstate);
  }
  cout << "SOLUTION FOUND\n";
  print(path);
  return 0;
}

