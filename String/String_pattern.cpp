#include <bits/stdc++.h>

using namespace std;
namespace Str{
    vector <int> pre(string s)
    {
        int n = (int) s.length();
        vector <int> pi(n);
        for (int i = 1; i < n; i++)
        {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
        return pi;
    }
    vector <int> KMP(string a, string b)
    {
        string cur = b + '#' + a; // the "#" represents the unrelated character
        int sz1 = a.size(), sz2 = b.size();
        vector <int> v;
        vector <int> lps = pre(cur);
        for (int i = sz2 + 1; i <= sz1 + sz2; i++)
        {
            if (lps[i] == sz2) v.push_back(i - 2 * sz2);
        }
        return v;
    }
    // KMP extention, z[i] : common prefix for s and s[i..n]
    vector <int> z(string s)
    {
        int n = (int)s.length();
        vector<int> z(n);
        for (int i = 1, l = 0, r = 0; i < n; ++i) {
            if (i <= r && z[i - l] < r - i + 1) {
            z[i] = z[i - l];
            } else {
            z[i] = max(0, r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
            }
            if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        }
        return z;
    }


    
};

// for testing
int main(){
    string a, b;
    cin >> a >> b;
    vector <int> tmp = Str::KMP(a, b);
    for (auto x : tmp) cout << x << ' ';

    return 0;
}