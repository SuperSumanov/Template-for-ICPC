#include <bits/stdc++.h>

using namespace std;

namespace SA{
    constexpr int MAXN = 1e6 + 7;
    int n, m, p;
    int tmprk[MAXN], cnt[MAXN], id[MAXN], rk[MAXN], sa[MAXN];
    // Remember the length of the array rk and sa.
    void solve(string &s, int ans[]) // Return the final rank for suffix array in "ans[]"
    {
        n = s.size();
        // cout << s << '\n';
        m = 128;
        for (int i = 1; i <= n; i++) cnt[rk[i]=s[i - 1]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;
        
        for (int w = 1;; w <<= 1, m = p)
        {
            int cur = 0;
            for (int i = n - w + 1; i <= n; i++) id[++cur] = i;
            for (int i = 1; i <= n; i++) if (sa[i] > w) id[++cur] = sa[i] - w;
            memset(cnt, 0, sizeof(cnt));
            for (int i = 1; i <= n; i++) cnt[rk[i]]++;
            for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i];
            p = 0;
            memcpy(tmprk, rk, sizeof(rk));
            
            p = 0;
            for (int i = 1; i <= n; i++)
            {
                if (tmprk[sa[i]] == tmprk[sa[i - 1]] && tmprk[sa[i] + w] == tmprk[sa[i - 1] + w]) rk[sa[i]] = p;
                else rk[sa[i]] = ++p;
            }
            if (p == n) break; 
        }
        for (int i = 1; i <= n; i++) ans[i] = sa[i];
    }

};
const int MAXN = 1e6 + 7;
int rk[MAXN], sa[MAXN];
// For testing the sort of suffix array.
int main()
{
    string s;
    cin >> s;
    SA::solve(s, sa);
    for (int i = 1; i <= s.size(); i++) cout << sa[i]<< ' ';


    return 0;
}