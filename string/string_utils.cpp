#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> split(string &s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

int main() {
    string s = "abc.def.egh..   .kkk";
    cout<<segs.size()<<endl;
    auto segs = split(s, ".");
    for (auto _ : segs) cout<<_<<endl;
    return 0;
}