/*
    AI Assignment-1.
    Aman Jham - 2019A7PS0071H
    R Vedang - 
    Shubh - 
*/

#include <bits/stdc++.h>

using namespace std;
#define MAX_DIST 1000000000
#define all(x) x.begin(), x.end()
#define sz(x) static_cast<int32_t>(x.size())

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); 
  int n, m;
  int start, goal;
  cin >> n >> m;
  cin >> start >> goal;
  vector <vector<pair<int, int> > > graph(n);
  vector <int> heuristics_sld(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back(make_pair(v, w));
    graph[v].push_back(make_pair(u, w));
  }
  for (int i = 0; i < n; ++i) {
    cin >> heuristics_sld[i];
  }
  set <int> open_list, closed_list;
  vector <int> parents(n);
  parents[start] = start;
  vector <int> g(n); 
  g[start] = 0;
  open_list.insert(start);
  while (!open_list.empty()) {
    int n = -1;
    for (auto v : open_list) {
        if (n == -1 or g[v] + heuristics_sld[v] < g[n] + heuristics_sld[n]) {
            n = v;
        }
    }
    if (n == -1) {
        cout << "NO PATH EXISTS\n";
        return 0;
    }
    if (n == goal) {
        cout << "SOLUTION FOUND : \n";
        vector <int> path;
        while (parents[n] != n) {
            path.push_back(n);
            n = parents[n];
        }
        path.push_back(start);
        reverse(all(path));
        for (auto &x : path) {
            cout << x << " ";
        } 
        cout << '\n';
        return 0;
    }
    for (auto &[v, w] : graph[n]) {
        if (!open_list.count(v) and !closed_list.count(v)) {
            open_list.insert(v);
            g[v] = g[n] + w;
            parents[v] = n;
        } else {
            if (g[v] > g[n] + w) {
                g[v] = g[n] + w;
                parents[v] = n;
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

