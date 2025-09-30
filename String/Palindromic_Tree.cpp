#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 3e5 + 7;
namespace pam{
    int sz, tot, last;
    int ch[MAXN][26], cnt[MAXN], len[MAXN], fail[MAXN];
    char s[MAXN];

    int node(int l)
    {
        sz++;
        len[sz] = l;
        fail[sz] = cnt[sz] = 0;
        return sz;
    }

    void clear()
    {
        sz = -1;
        last = 0;
        s[tot = 0] = '$';
        node(0);
        node(-1);
        fail[0] = 1;
    }

    int getfail(int x)
    {
        while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
        return x;
    }

    void insert(char c)
    {
        s[++tot] = c;
        int now = getfail(last);
        if (!ch[now][c - 'a'])
        {
            int x = node(len[now] + 2);
            fail[x] = ch[getfail(fail[now])][c - 'a'];
            ch[now][c - 'a'] = x;
        }
        last = ch[now][c - 'a'];
        cnt[last]++;
        
    }
};
int main()
{

    return 0;
}