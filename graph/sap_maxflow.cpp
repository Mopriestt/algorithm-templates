#include <iostream>
#include <vector>

using namespace std;

class Sap {
public:
    const int oo = 1 << 30;

    struct Edge {
        int t, f;
        Edge *op;

        Edge(int t, int f) : t(t), f(f) {}
    };

    int n, S, T;
    vector<int> vd;
    vector<int> d;
    vector<vector<Edge>> G;
    
    Sap(int n, int S, int T) : n(n), S(S), T(T) {
        G.resize(n);
    }

    void addedge(int i, int j, int f) {
        G[i].push_back(Edge(j, f));
        G[j].push_back(Edge(i, 0));
        G[i].back().op = &G[j].back();
        G[j].back().op = &G[i].back();
    }

    int dfs(int u, int flow) {
        int tmp, ret = 0;
        if (u == T) return flow;
        for (auto &e : G[u]) {
            if (e.f > 0 && d[u] == d[e.t] + 1) {
                tmp = dfs(e.t, min(flow - ret, e.f));
                e.f -= tmp;
                e.op->f += tmp;
                ret += tmp;
                if (flow == ret) return ret;
            }
        }
        if (!--vd[d[u]]) d[S]=n;
        vd[++d[u]]++;
        return ret;
    }

    int calculate() {
        d.resize(n);
        vd.resize(n);
        vd[S] = n;
        int ans = 0;

        while (d[S] < n) ans += dfs(S, oo);

        return ans;
    }
};

int main() {
    Sap sap(2, 0, 1);
    sap.addedge(0, 1, 1);
    cout<< sap.calculate() << endl;
    return 0;
}