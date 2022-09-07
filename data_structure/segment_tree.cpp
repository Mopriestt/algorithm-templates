#include <iostream>
#include <vector>

using namespace std;

const int MAX_NODES = 100000;

class SegmentTree {
public:
    struct Node {
        int l, r, max;
        Node *cl, *cr;
        long long sum;
    } T[MAX_NODES * 2 + 10], root = T;
    int ns = 0;
    
    SegmentTree(vector<int> &maxArray, vector<int> &sumArray) {
        buildTree(root, 0, maxArray.size() - 1, maxArray, sumArray);
    }
    
    pair<int, long long> query(int l, int r) {
        return _query(root, l, r);
    }
private:
    pair<int, long long> _query(Node *p, int l, int r) {
        if (l > p -> r || r < p -> l) return {0, 0};
        if (l <= p -> l && r >= p -> r) return {p -> max, p -> sum};
        auto v1 = _query(p -> cl, l, r), v2 = _query(p -> cr, l, r);
        return {max(v1.first, v2.first), v1.second + v2.second};
    }

    inline void update(Node *p) {
        p -> max = max(p -> cl -> max, p -> cr -> max);
        p -> sum = p -> cl -> sum + p -> cr -> sum;
    }

    void buildTree(Node *p, int l, int r, vector<int> &maxArray, vector<int> &sumArray) {
        p -> l = l, p -> r = r;
        if (l == r) {
            p -> max = maxArray[l], p -> sum = sumArray[l];
            return;
        }
        int mid = (l + r) >> 1;
        p -> cl = T + ++ns, p -> cr = T + ++ns;
        buildTree(p -> cl, l, mid, maxArray, sumArray);
        buildTree(p -> cr, mid + 1, r, maxArray, sumArray);
        update(p);
    }
};

void test_segment_tree() {
    int n = 100000;
    srand(time(NULL));
    vector<int> maxArray, sumArray;
    for (int i = 0; i < n; i ++)
        maxArray.push_back(rand()), sumArray.push_back(rand());
    SegmentTree tree(maxArray, sumArray);

    for (int query = 0; query < 10000; query ++) {
        int l = rand() % n, r = rand() % n;
        if (l > r) swap(l, r);
        auto result = tree.query(l, r);

        int max_value = 0;
        long long sum = 0;
        for (int i = l; i <= r; i ++) {
            max_value = max(max_value, maxArray[i]);
            sum += sumArray[i];
        }
        if (max_value != result.first || sum != result.second) {
            cout<<"Test failed!"<<endl;
            return;
        }
    }
    cout<<"Test passed!"<<endl;
}

// Used for Leetcode 2398.
int main() {
    test_segment_tree();
    return 0;
}