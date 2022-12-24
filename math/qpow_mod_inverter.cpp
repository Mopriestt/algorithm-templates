#include <iostream>

using namespace std;

const int M = 1000000007;

// Fermat's little theorem
// a ^ (p - 1) % p = 1 if a % p != 0
//
// Mod inverter
// a ^ (p - 2) % p => 1 / a
// b / a => b * a ^ (p - 2) % p

long long qpow(long long a, long long b) {
    long long ret = 1;
    while (b > 0) {
        a %= M;
        if (b & 1) ret = ret * a % M;
        b >>= 1;
        a = a * a % M;
    }
    return ret;
}

int main() {
    return 0;
}