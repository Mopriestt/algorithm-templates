#include <iostream>
#include <vector>
#include <queue>

using namespace std;


template <typename T>

/**
 * Bellman-Ford's algorithm with queue optimised.
 * AKA Shortest-Path-Fast-Algorithm.
*/
class Spfa {
    public:
        int n;
        bool undirected;
        
        vector<T> distance;
        vector<bool> visited;
        
        Spfa(int n, bool undirected = false) {
            this -> n = n;
            this -> undirected = undirected;
            distance.resize(n);
            visited.resize(n);
            edges.resize(n);
        }
        
        void add_edge(int start, int end, T length) {
            index_sanity_check(start, "add_edge");
            index_sanity_check(end, "add_edge");
            
            edges[start].push_back(make_pair(end, length));
            if (undirected) edges[end].push_back(make_pair(start, length));
        }
        
        void calculate(int start) {
            index_sanity_check(start, "calculate");
            
            while (!q.empty()) q.pop();
            for (int i = 0 ; i < n; i ++) visited[i] = false;
            distance[start] = 0;
            visited[start] = true;
            q.push(start);
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                for (auto next : edges[u]) {
                    relax(u, next.first, next.second);
                }
            }
        }
    private:
        queue<int> q;
        vector<vector<pair<int, T>>> edges;
        
        void relax(int u, int v, T l) {
            if (!visited[v] || distance[v] > distance[u] + l) {
                visited[v] = true;
                distance[v] = distance[u] + l;
                q.push(v);
            }
        }
        
        void index_sanity_check(int index, string where) {
            if (index >= n) throw std::overflow_error(where + ": index >= n");
            if (index < 0) throw std::overflow_error(where + ": index < 0");
        }
};

int main() {
    return 0;
}
