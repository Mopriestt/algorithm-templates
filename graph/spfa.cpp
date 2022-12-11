#include <iostream>
#include <vector>
#include <deque>

using namespace std;

template <typename T>

/**
 * Bellman-Ford's algorithm with queue optimised.
 * AKA Shortest-Path-Fast-Algorithm.
 * To use:
 * Spfa<Type> spfa(node_count);
 * spfa.add_edge(a1, b1, c1);
 * spfa.add_edge(a2, b2, c2);
 * ...
 * spfa.calculate(start_node_index);
 * result = spfa.distance
 */
class Spfa {
public:
    int n;
    bool undirected;
    bool slf;

    vector<T> distance;
    vector<bool> visited;

    Spfa(int n, bool undirected = false, bool slf = false) {
        this->n = n;
        this->undirected = undirected;
        this->slf = slf;
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
        index_sanity_check(start, "Calculate");

        while (!dq.empty()) dq.pop_back();
        for (int i = 0; i < n; i++) visited[i] = false;
        distance[start] = 0;
        visited[start] = true;
        dq.push_back(start);

        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();
            for (auto next : edges[u]) relax(u, next.first, next.second);
        }
    }
private:
    deque<int> dq;
    vector<vector<pair<int, T> > > edges;

    void relax(int u, int v, T l) {
        if (!visited[v] || distance[v] > distance[u] + l) {
            visited[v] = true;
            distance[v] = distance[u] + l;
            if (slf && !dq.empty() && distance[v] < distance[dq.front()]) dq.push_front(v);
            else dq.push_back(v);
        }
    }

    inline void index_sanity_check(int index, string where) {
        if (index >= n) throw overflow_error(where + ": index >= n");
        if (index < 0) throw overflow_error(where + ": index < 0");
    }
};

void TestSpfaWithFloyd(int N) {
    srand(time(NULL));

    vector<vector<long long> > d(N);
    Spfa<long long> spfa(N, false, true);

    for (int i = 0; i < N; i++) {
        d[i].resize(N);
        for (int j = 0; j < N; j++) {
            d[i][j] = rand() % 10000;
            spfa.add_edge(i, j, d[i][j]);
        }
        d[i][i] = 0;
    }

    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (d[i][j] > d[i][k] + d[k][j]) d[i][j] = d[i][k] + d[k][j];

    for (int start = 0; start < N; start++) {
        spfa.calculate(start);
        for (int end = 0; end < N; end++)
            if (spfa.distance[end] != d[start][end]) {
                throw runtime_error("Test failed!");
            }
    }
}

int main() {
    TestSpfaWithFloyd(300);
    cout << "Test Passed!" << endl;
    return 0;
}
