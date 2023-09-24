#include <vector>

using namespace std;

void dijkstra(vector<vector<pair<int, int>>> &G, vector<int> &ret, int s, int n) {
    vector<char> vis(n, 0);
    ret.resize(n, -1);
    ret[s] = 0;
    for (int i = 0; i < n - 1; i ++) {
        int k = -1;
        for (int j = 0; j < n; j ++)
            if (vis[j] == 0 && ret[j] != -1 && (k == -1 || ret[k] > ret[j])) k = j;
        vis[k] = 1;
        
        for (auto &e : G[k]) {
            if (ret[e.first] == -1 || ret[e.first] > ret[k] + e.second) {
                ret[e.first] = ret[k] + e.second;
            }
        }
    }
}

inline void dijkstra(vector<vector<pair<int, int>>> &G, vector<int> &ret, int s) {
    dijkstra(G, ret, s, G.size());
}

inline void dijkstra(vector<vector<pair<int, int>>> &G, vector<int> &ret) {
    dijkstra(G, ret, 0, G.size());
}

int main() {
    return 0;
}