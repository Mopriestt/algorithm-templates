#include <iostream>

using namespace std;

void loopSubSet(int n) {
    for (int s = n; s; s = (s - 1) & n) {
        cout<<s<<endl;
    }
}

void loopKSubSet(int n, int k) {
    int comb = (1 << k) - 1;
    while (comb < 1 << n) {
        cout<<comb<<endl;
        int x = comb & -comb, y = comb + x;
        comb = ((comb & ~y) / x >> 1) | y;
    }
}

int main() {
    loopSubSet(100);
    cout<<"============="<<endl;
    loopKSubSet(5, 3);
}
