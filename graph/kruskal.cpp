#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>

class Kruskal {
public:
	int n;
	vector<int> father; // Disjoint-set
	Kruskal(int n) {
	    this->n = n;
		father.resize(n);
		for (int i = 0; i < n; i++) father[i] = i;
	}
	void AddEdge(int u, int v, T value) {
		IndexSanityCheck(u, "AddEdge");
		IndexSanityCheck(v, "AddEdge");
		edges.push_back(make_pair(value, make_pair(u, v)));
	}

	T Calculate() {
		// Change ans type if the result will overflow.
		T ans = 0;
		// Change comparator to Calculate maximum spanning forest.
		sort(edges.begin(), edges.end());

		for (auto e : edges) {
			if (Find(e.second.first) != Find(e.second.second)) {
				ans += e.first;
				Merge(e.second.first, e.second.second);
			}
		}

		return ans;
	}
private:
	vector<pair<T, pair<int, int>>> edges;

	inline void Merge(int u, int v) {
		father[Find(u)] = father[v];
	}

	int Find(int u) {
		if (father[u] != u) father[u] = Find(father[u]);
		return father[u];
	}

	inline void IndexSanityCheck(int index, string where) {
		if (index >= n) throw overflow_error(where + ": index >= n");
		if (index < 0) throw overflow_error(where + ": index < 0");
	}
};

void SimpleTestKruskal() {
	Kruskal<int> kruskal(5);
	kruskal.AddEdge(0, 1, 1);
	kruskal.AddEdge(1, 2, 2);
	kruskal.AddEdge(2, 3, 3);
	kruskal.AddEdge(3, 4, 5);
	kruskal.AddEdge(0, 4, 6);
	kruskal.AddEdge(0, 3, 3);
	kruskal.AddEdge(3, 1, 4);
	cout << kruskal.Calculate() << endl;
}

int main() {
	SimpleTestKruskal();
	return 0;
}
