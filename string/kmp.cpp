#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Kmp {
public:
    string t;
    vector<int> jump;
    Kmp(string t) {
        this -> t = t;
        jump.resize(t.size());
        calc_jump(t);
    }
    
    // Returns first matching start index of t in s.
    // If no match returns -1.
    int index_in(string s) {
        int j = -1; // Matching position in t.
        for (int i = 0; i < s.size(); i ++) {
            while (j >= 0 && s[i] != t[j + 1]) j = jump[j];
            if (s[i] == t[j + 1]) j ++;
            if (j == t.size() - 1) return i - t.size() + 1;
        }
        return -1;
    }
    
private:
    void calc_jump(string s) {
        jump[0] = -1;
        int match = -1;
        for (int i = 1; i < t.length(); i ++) {
            while (match >= 0 && t[i] != t[match + 1]) match = jump[match];
            if (t[i] == t[match + 1]) ++ match;
            jump[i] = match;
        }
    }
};

void test_kmp(string s, string t) {
    Kmp kmp(t);
    cout<<kmp.index_in(s)<<endl;
}

int main() {
    string s, t;
    for (int i = 0 ; i < 1000000; i ++) s += 'a';
    s += 'b';
    for (int i = 0; i < 10000; i ++) t += 'a';
    t += 'b';
    test_kmp(s, t);
    
    test_kmp("mississippi", "issip");

    return 0;
}
