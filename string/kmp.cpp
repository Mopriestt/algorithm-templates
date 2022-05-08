#include <stdio.h>

using namespace std;

class kmp {
public:
    vector<int> jump;
    kmp(int s) {
        jump.resize(s.length);
        calc_jump(s);
    }
    
private:
    void calc_jump(string s) {
        jump[0] = 0;
        int match = 0;
        for (int i = 1; i < s.length; i ++) {
            while (match > 0 && s[i] != s[match + 1]) match = jump[match];
            if (s[i] == s[match + 1]) ++ match;
            jump[i] = match;
        }
    }
};

int main() {
    

    return 0;
}
