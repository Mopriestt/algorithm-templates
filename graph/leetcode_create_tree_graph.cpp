const int MAXN = 100005; //1e5

struct Edge {
    int t;
    Edge *p;
} *v[MAXN], e[MAXN * 2];

int es = -1;

void add_edge(int i, int j) {
    e[++es].t = j; e[es].p = v[i]; v[i] = e + es;
}

// Tree calc father.
int father[MAXN];
void getFather(int u, int fa) {
    father[u] = fa;
    for (auto x = v[u]; x; x = x -> p) if (x -> t != fa) {
        getFather(x -> t, u);
    }
}

int main() {
    return 0;
}