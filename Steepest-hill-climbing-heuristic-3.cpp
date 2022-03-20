/*
    AI Assignment-1.
    Aman Jham - 2019A7PS0071H
    R Vedang - 2019A7PS0150H
    Shubh - 2019A7PS0100H
*/

/*
    2 7 9 3 6 1 4 10 12 5 11 8
    2 3 4 1 6 7 8 5 10 11 12 9
*/

/*
    Problem: A dart board is filled with 12 sectors. Each sector can perform 4 operations, rotate clockwise, rotate
    anticlockwise, shift down (till center). Given an initial state (Fig. A), design and implement an efficient
    heuristic approach to reach the goal state (Fig B). Use Steepest Ascent Hill-Climbing Search with an
    appropriate heuristic evaluation function. During the execution, you may check if your heuristic
    evaluation function is prone to issues like local maxima, plateau or ridges as discussed in the class. You
    need not provide any solution to these problems at this stage.
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
        this->board.resize(12);
    }
    // Board(const Board &other) {
    //     this->board.resize(12);
    //     this->board = other.get_board();
    // }
    void set_board(vector <int> board) {
        this->board = board;
    }
    vector <int> get_board() {
        return this->board;
    }
    vector <int> operate(int sector_no, int type) {
        vector <int> new_board(12);
        new_board = board;
        /*
            OPeration accordingly.
        */
        //this->board = new_board;
        return board;
    }
    Board clockwise(vector <int> a, int x) {
        Board new_board;
        int val = a[x * 4 + 3];
        a[4 * x + 3] = a[x * 4 + 2];
        a[4 * x + 2] = a[x * 4 + 1];
        a[4 * x + 1] = a[x * 4 + 0];
        a[x * 4 + 0] = val;
        new_board.set_board(a);
        return new_board;
    }   
    Board anti_clockwise(vector <int> a, int x) {
        Board new_board;
        int val = a[x * 4 + 0];
        a[4 * x + 0] = a[x * 4 + 1];
        a[4 * x + 1] = a[x * 4 + 2];
        a[4 * x + 2] = a[x * 4 + 3];
        a[x * 4 + 3] = val;
        new_board.set_board(a);
        return new_board;
    }
    Board shift_down(vector<int> a, int x) {
        Board new_board;
        swap(a[x], a[4 + x]);
        new_board.set_board(a);
        return new_board;
    }
    vector <Board> get_all_states() {
        vector <Board> nextstates;
        nextstates.push_back(clockwise(this->board, 0));
        nextstates.push_back(clockwise(this->board, 1));
        nextstates.push_back(clockwise(this->board, 2));

        nextstates.push_back(anti_clockwise(this->board, 0));
        nextstates.push_back(anti_clockwise(this->board, 1));
        nextstates.push_back(anti_clockwise(this->board, 2));

        nextstates.push_back(shift_down(this->board, 0));
        nextstates.push_back(shift_down(this->board, 4));
        nextstates.push_back(shift_down(this->board, 1));
        nextstates.push_back(shift_down(this->board, 5));
        nextstates.push_back(shift_down(this->board, 2));
        nextstates.push_back(shift_down(this->board, 6));
        nextstates.push_back(shift_down(this->board, 3));
        nextstates.push_back(shift_down(this->board, 7));

        return nextstates;
    }
    int heuristic_val(Board goalstate) {
        int heuristic = 0;
        vector <int> goalboard = goalstate.get_board();
        for (int i = 0; i < 12; ++i) {
            int x1 = i / 4;
            int y1 = i % 4;
            int x2 = -1, y2 = -1;
            for (int j = 0; j < 12; ++j) {
                if (goalboard[j] == this->board[i]) {
                    x2 = j / 4;
                    y2 = j % 4;
                    break;
                }
            }
            assert(x2 != -1);
            heuristic += abs(x1 - x2) + abs(y1 - y2);
        }
        return heuristic;
    }
    void print() {
        for (auto x : this->board) {
            cout << x << " ";
        }
        cout << '\n';
    }
    bool is_better(Board other, Board goal) {
        return this->heuristic_val(goal) < other.heuristic_val(goal); 
    }
    bool operator == (Board other) {
        return this->board == other.get_board();
    }
    bool eaquals(Board other, Board goal) {
        return this->heuristic_val(goal) == other.heuristic_val(goal);
    }
    void operator = (Board other) {
        this->board = other.get_board();
    }
    bool operator != (Board other) {
        return this->board != other.get_board();
    }
};

void print(vector <Board> path) {
    for (int i = 0; i < path.size(); ++i) {
        cout << "State " << i << " : ";
        //cout << "this state heuristic value : " << path[i].heuristic_val(goalstate) << '\n';
        path[i].print();
    }
    return;
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); 
  Board startstate;
  vector <int> vals(12);
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
  Board currentstate = startstate;
  path.push_back(startstate);
  Board SUCC = currentstate;
  //cout << "Start state heuristic value : " << startstate.heuristic_val(goalstate) << '\n';
  //cout << goalstate.heuristic_val(goalstate) << '\n';
  while (true) {
    Board prevstate = currentstate;
    vector <Board> nextstates = currentstate.get_all_states();
    //cout << sz(nextstates) << '\n';
    for (auto &state : nextstates) {
        if (state == goalstate) {
            path.push_back(state);
            cout << "SOLUTION FOUND\n";
            print(path);
            return 0;
        }
        //SUCC = state;
        if (state.is_better(SUCC, goalstate)) {
            SUCC = state;
        }
    }
    if (SUCC.is_better(currentstate, goalstate)) {
        currentstate = SUCC;
    }
    if (currentstate.eaquals(prevstate, goalstate)) {
        cout << "NO SOLUTION FOUND\n";
        //cout << "Final state heuristic value : " << currentstate.heuristic_val(goalstate) << '\n';
        //cout << "MAi yaha pe hu!!!\n";
        print(path);
        return 0;
    }
    path.push_back(currentstate);
  }
  cout << "SOLUTION FOUND\n";
  print(path);
  return 0;
}
