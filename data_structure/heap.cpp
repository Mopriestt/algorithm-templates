#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>

class Heap {
public:
    inline int Size() {
        return arr.size();
    }

    T Top() {
        if (arr.size() == 0) throw overflow_error("Topping on empty heap.");
        return arr[0];
    }

    T Pop() {
        if (arr.size() == 0) throw overflow_error("Popping on empty heap.");
        T ret = arr[0];
        arr[0] = *--arr.end();
        arr.pop_back();
        Sink(0);
        return ret;
    }

    void Add(T x) {
        arr.push_back(x);
        Float(arr.size() - 1);
    }
private:
    vector<T> arr;

    inline bool Greater(int a, int b) {
        if (b >= arr.size()) return false;
        return arr[a] > arr[b];
    }

    void Sink(int pos) {
        while (Greater(pos, pos * 2 + 1) || Greater(pos, pos * 2 + 2)) {
            if (Greater(pos * 2 + 1, pos * 2 + 2)) {
                swap(arr[pos], arr[pos * 2 + 2]);
                pos = pos * 2 + 2;
            } else {
                swap(arr[pos], arr[pos * 2 + 1]);
                pos = pos * 2 + 1;
            }
        }
    }

    void Float(int pos) {
        while (pos > 0 && arr[pos] < arr[pos - 1 >> 1]) {
            swap(arr[pos], arr[pos - 1 >> 1]);
            pos = pos - 1 >> 1;
        }
    }
};

void TestHeap(int n) {
    srand(time(NULL));
    vector<int> a(n);
    Heap<int> heap;

    for (int i = 0; i < n; i ++) {
        int x = rand();
        a[i] = x;
        heap.Add(x);
    }
    sort(a.begin(), a.end());

    for (int i = 0; i < n; i ++) {
        if (a[i] != heap.Pop()) {
            cout<<"Test Failed"<<endl;
            return;
        }
    }
    cout<<"Test Passed"<<endl;
}

int main() {
    TestHeap(100000);
    return 0;
}