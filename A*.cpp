/*
    AI Assignment-1.
    Aman Jham - 2019A7PS0071H
    R Vedang - 2019A7PS0150
    Shubh - 2019A7PS0100
*/

/*
    Problem statement :
    In 2021, a Mars rover, Perseverance, landed on the moon carrying along with it the first of its kind
    helicopter named Ingenuity. The goal of the rover was to travel to the center of a crater named Jezero
    with the help of Ingenuity. Since no help from Earth is available, Perseverance is solely dependent on
    Ingenuity’s inputs. Ingenuity flies across a couple of meters and gives an aerial topography as an input to
    Perseverance (FIG A) and based on these inputs the rover takes its next step. Design a communication
    channel between Ingenuity and Perseverance where the copter sends the expanded states from the
    initial position of the rover, the rover sends back the decision it takes on the expanded states and so on.
    Ensure that an optimal heuristic approach search (A*) is used by the rover to decide upon which state
    to choose. The edges in the topography represent the distances between each check point.
*/

/*
    Assumptions or considering foloowing facts for input and output.
    Number of nodes will be given - nodes
    Number of edges are - m which are form u, v, w -> meaning undirdceted edge from u to v with wei w
    start - start state
    goal - goal state
    Heursitics value - straight line distance which will be given as an input.
*/

#include <bits/stdc++.h>

using namespace std;
#define MAX_DIST 1000000000
#define all(x) x.begin(), x.end()
#define sz(x) static_cast<int32_t>(x.size())

vector <int> heuristics_sld;
vector <int> g;

struct cmp {
    bool operator() (int a, int b) const {
        return g[a] + heuristics_sld[a] < g[b] + heuristics_sld[b];
    }
};

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); 
  int nodes, m;
  int start, goal;
  cin >> nodes >> m;
  cin >> start >> goal;
  vector <vector<pair<int, int> > > graph(nodes);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back(make_pair(v, w));
    graph[v].push_back(make_pair(u, w));
  }
  heuristics_sld.resize(nodes);
  for (int i = 0; i < nodes; ++i) {
    cin >> heuristics_sld[i];
  }

  set <int> closed_list;
  
  vector <int> parents(nodes);
  
  // auto cmp = [](int a, int b) {
  //   return g[a] + heuristics_sld[a] < g[b] + heuristics_sld[b];
  // };
  
  //set <int, decltype(cmp)> open_list;
  set <int, cmp> open_list;
  parents[start] = start;
  g.assign(nodes, 1e9);
  g[start] = 0;
  open_list.insert(start);

  // while (!open_list.empty()) {
  //   int n = -1;
  //   for (auto v : open_list) {
  //       if (n == -1 or g[v] + heuristics_sld[v] < g[n] + heuristics_sld[n]) {
  //           n = v;
  //       }
  //   }
  //   if (n == -1) {
  //       cout << "NO PATH EXISTS\n";
  //       return 0;
  //   }
  //   if (n == goal) {
  //       cout << "SOLUTION FOUND : \n";
  //       cout << "TOTAL DISTANCE : " << g[n] << '\n';
  //       cout << "PATH : ";
  //       vector <int> path;
  //       while (parents[n] != n) {
  //           path.push_back(n);
  //           n = parents[n];
  //       }
  //       path.push_back(start);
           // reverse(all(path));
           // int cnt = 0;
           // for (auto &x : path) {
           //      cout << x << " ";
           //      if (cnt++ < path.size() - 1) cout << "-> ";
           // } 
           // cout << '\n';
           // return 0;
  //   }
  //   for (auto &[v, w] : graph[n]) {
  //       if (!open_list.count(v) and !closed_list.count(v)) {
  //           g[v] = g[n] + w;
  //           parents[v] = n;
  //           open_list.insert(v);
  //       } else {
  //           if (g[v] > g[n] + w) {
  //               g[v] = g[n] + w;
  //               parents[v] = n;
  //               if (closed_list.count(v)) {
  //                   closed_list.erase(v);
  //                   open_list.insert(v);
  //               }
  //           }
  //       }
  //   }
  //   open_list.erase(n);
  //   closed_list.insert(n);
  // }


  /*
    Optimised Version, using compartors for open_list
    We dont have to iterate in open_list to get current best value.
    so we can get best in O(logn).
  */

 while (!open_list.empty()) {
    int n = *open_list.begin();
    if (n == goal) {
        cout << "SOLUTION FOUND : \n";
        cout << "TOTAL DISTANCE : " << g[n] << '\n';
        cout << "PATH : ";
        vector <int> path;
        while (parents[n] != n) {
            path.push_back(n);
            n = parents[n];
        }
        path.push_back(start);
        reverse(all(path));
        int cnt = 0;
        for (auto &x : path) {
            cout << x << " ";
            if (cnt++ < path.size() - 1) cout << "-> ";
        } 
        cout << '\n';
        return 0;
    }
    for (auto &[v, w] : graph[n]) {
        if (!open_list.count(v) and !closed_list.count(v)) {
            g[v] = g[n] + w;
            parents[v] = n;
            open_list.insert(v);
        } else {
            if (g[v] > g[n] + w) {
                if (open_list.count(v)) open_list.erase(v);
                g[v] = g[n] + w;
                parents[v] = n;
                open_list.insert(v);
                if (closed_list.count(v)) {
                    closed_list.erase(v);
                    open_list.insert(v);
                }
            }
        }
    }
    open_list.erase(n);
    closed_list.insert(n);
  }

  /*
    NO PATH FOUND, if found alerady returned.
  */

  cout << "NO PATH FOUND\n";

  return 0;
}

