#include <bits/stdc++.h>

using namespace std;

namespace SAM{
    constexpr int N = 1e6 + 7, M = 1e6 + 7, RNG = 26, inf = INT_MAX;
    struct SuffixAutomaton{
        int tot, lst;
            int siz[N << 1];
            int buc[N], id[N << 1];

            struct Node {
                int len, link;
                int ch[26];
            } st[N << 1];

            SuffixAutomaton() : tot(1), lst(1) {}

            void extend(int ch) {
                int cur = ++tot, p = lst;
                lst = cur;
                siz[cur] = 1, st[cur].len = st[p].len + 1;
                for (; p && !st[p].ch[ch]; p = st[p].link) st[p].ch[ch] = cur;
                if (!p)
                st[cur].link = 1;
                else {
                int q = st[p].ch[ch];
                if (st[q].len == st[p].len + 1)
                    st[cur].link = q;
                else {
                    int pp = ++tot;
                    st[pp] = st[q];
                    st[pp].len = st[p].len + 1;
                    st[cur].link = st[q].link = pp;
                    for (; p && st[p].ch[ch] == q; p = st[p].link) st[p].ch[ch] = pp;
                }
                }
            }
    };
    // Support inserting character to the end of the string.
    struct SuffixTree {
        int ch[M + 5][RNG + 1], st[M + 5], len[M + 5], link[M + 5];
        int s[N + 5];
        int now{1}, rem{0}, n{0}, tot{1};

        SuffixTree() { len[0] = inf; }

        int new_node(int s, int le) {
            ++tot;
            st[tot] = s;
            len[tot] = le;
            return tot;
        }

        void extend(int x) {
            s[++n] = x;
            ++rem;
            for (int lst{1}; rem;) {
            while (rem > len[ch[now][s[n - rem + 1]]])
                rem -= len[now = ch[now][s[n - rem + 1]]];
            int &v{ch[now][s[n - rem + 1]]}, c{s[st[v] + rem - 1]};
            if (!v || x == c) {
                lst = link[lst] = now;
                if (!v)
                v = new_node(n, inf);
                else
                break;
            } else {
                int u{new_node(st[v], rem - 1)};
                ch[u][c] = v;
                ch[u][x] = new_node(n, inf);
                st[v] += rem - 1;
                len[v] -= rem - 1;
                lst = link[lst] = v = u;
            }
            if (now == 1)
                --rem;
            else
                now = link[now];
            }
        }
        } Tree;

};

int main()
{

    return 0;
}