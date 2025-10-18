#include <bits/stdc++.h>

using namespace std;

namespace VectorSpace{
    struct Point{
        double x, y, ang = 0;
        friend Point operator+(const Point &s, const Point &p){ return {s.x + p.x, s.y + p.y};}
        friend Point operator-(const Point &s, const Point &p) {return {s.x - p.x, s.y - p.y, 0};}
        friend double operator^(const Point &s, const Point &p) { return s.x * p.y - s.y * p.x;}
        friend double operator*(const Point &s, const Point &p){return s.x * p.x + s.y + p.y;}
        friend bool operator!=(const Point &s, const Point &p) {return (s.x != p.x) || (s.y != p.y);}
    };

    double form(Point p)
    {
        return sqrt(p.x * p.x + p.y * p.y);
    }
    double dis(Point p1, Point p2)
    {
        return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }
    // Note that the length will change if there are identical points in the array.

    //
    void ConvexHull(Point *p, int *sta, int &n, int &len)
    {
        for (int i = 2; i <= n; i++)
            if (p[i].y < p[1].y || (p[i].y == p[1].y && p[i].x < p[1].x)){
                std::swap(p[i], p[1]);
            }
        for (int i = 2; i <= n; i++)
            p[i].ang = atan2(p[i].y - p[1].y, p[i].x - p[1].x);
        Point tmp = p[1];
        std::sort(p + 2, p + n + 1, [tmp](const Point &x, const Point &y){
            if (x.ang == y.ang) return dis(x, tmp) < dis(y, tmp);
            return x.ang < y.ang;
        });
        // Judge if has identical points
        int sn = 1;
        for (int i = 2; i <= n; i++)
        {
            if (p[i] != p[i - 1] && p[i] != p[1]){
                p[++sn] = p[i];
            }
        }
        n = sn;
        len = 0;
        sta[++len] = 1;
        for (int i = 2; i <= n; i++)
        {
            while (len >= 2 && ((p[sta[len]] - p[sta[len - 1]]) ^ (p[i] - p[sta[len]])) < 0) len--;
            sta[++len] = i;
        }
    }
    // Use vector form and remember to ensure that a and b is convex.
    void MinkovskiSum(vector <Point> &a, vector <Point> &b, vector <Point> &ret)
    {
        ret.push_back(a[0] + b[0]);
        for (int i = 0; i + 1 < a.size(); i++) a[i] = a[i + 1] - a[i];
        for (int i = 0; i + 1 < b.size(); i++) b[i] = b[i + 1] - b[i]; 
        a.pop_back(); b.pop_back();
        ret.resize(a.size() + b.size() + 1);
        merge(a.begin(), a.end(), b.begin(), b.end(), ret.begin() + 1, [](const Point &x, const Point &y){
            return (x ^ y) < 0;
        });
        for (int i = 1; i < ret.size(); i++) ret[i] = ret[i] + ret[i - 1];
    }
    // Judge if a point is inside a Convex Hull A
    bool JudgeIn(vector <Point> &a, Point s)
    {
        int len = a.size();
        if ((s ^ a[0]) > 0 || (a[len - 1] ^ s) > 0) return 0;
        int pos = lower_bound(a.begin(), a.end(), s ,[](const Point &x, const Point &y){
            return ((x ^ y) > 0 || ((x ^ y) == 0 && form(x) < form(y)));
        }) - a.begin();
       // cout  << pos << ' ' << a[pos].x << ' ' << a[pos].y << ' ' << s.x << ' ' << s.y << '\n';
        return ((s - a[pos]) ^ (a[(pos + 1) % len] - a[pos])) <= 0;
    }


};


// for testing Convex Hull


// const int MAXN = 1e5 + 7;
// int main()
// {
//     VectorSpace::Point p[MAXN];
//     int sta[MAXN];
//     int n, len;
//     cin >> n;
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> p[i].x >> p[i].y;
//         p[i].ang = 0;
//     }
//     VectorSpace::ConvexHull(p, sta, n, len);
//     // cout << "knccs\n";
//     double ans = 0;
//     for (int i = 1; i <= len; i++)
//     {
//         int nxt = (i == len) ? 1 : (i + 1);
//         // cout << p[sta[i]].x << ' ' << p[sta[i]].y << '\n';
//         ans += VectorSpace::dis(p[sta[i]], p[sta[nxt]]);
//     }
//     cout << fixed << setprecision(2) << ans << '\n';
//     return 0;   
// }


// for testing MinkovskiSum and Judgein (JSOI2018)


const int MAXN = 1e5 + 7;
int main()
{
    VectorSpace::Point a[MAXN], b[MAXN], tmp;
    int sta[MAXN], stb[MAXN];
    int n, m, q, lena, lenb;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
    VectorSpace::ConvexHull(a, sta, n, lena);
    vector <VectorSpace::Point> ca, cb, c;
    for (int i = 1; i <= lena; i++) ca.push_back(a[sta[i]]);
    for (int i = 1; i <= m; i++) cin >> b[i].x >> b[i].y, b[i].x = -b[i].x, b[i].y = -b[i].y;
    VectorSpace::ConvexHull(b, stb, m, lenb);
    for (int i = 1; i <= lenb; i++) cb.push_back(b[stb[i]]);
    
    // cout << '\n';
    // for (int i = 0; i < ca.size(); i++)
    //     cout << ca[i].x <<' ' << ca[i].y << '\n';

    // cout << '\n';
    // for (int i = 0; i < cb.size(); i++)
    //     cout << cb[i].x <<' ' << cb[i].y << '\n';


    VectorSpace::MinkovskiSum(ca, cb, c);  
    
    
    c.pop_back();
    for (int i = 1; i < c.size(); ++i) c[i] = c[i] - c[0];
    // cout << '\n';
    // for (int i = 0; i < c.size(); i++)
    //     cout << c[i].x <<' ' << c[i].y << '\n';
    for (int i = 1; i <= q; i++)
    {
        cin >> tmp.x >> tmp.y;
        cout << VectorSpace::JudgeIn(c, tmp) << '\n';
    }

}


// Another Solution for this:(JSOI2018)

// #include <algorithm>
// #include <cassert>
// #include <cstdint>
// #include <iostream>
// #include <vector>
// using namespace std;
// using i64 = int64_t;
// using isz = ptrdiff_t;
// using usz = size_t;

// template <class T>
// struct Point {
//   T x, y;

//   Point(T x = 0, T y = 0) : x(x), y(y) {}

//   friend Point operator+(const Point &a, const Point &b) {
//     return {a.x + b.x, a.y + b.y};
//   }

//   friend Point operator-(const Point &a, const Point &b) {
//     return {a.x - b.x, a.y - b.y};
//   }

//   // 点乘
//   friend T operator*(const Point &a, const Point &b) {
//     return a.x * b.x + a.y * b.y;
//   }

//   // 叉乘
//   friend T operator^(const Point &a, const Point &b) {
//     return a.x * b.y - a.y * b.x;
//   }

//   friend istream &operator>>(istream &is, Point &p) { return is >> p.x >> p.y; }
// };

// template <class T>
// vector<Point<T>> convex_hull(vector<Point<T>> p) {
//   assert(!p.empty());
//   sort(p.begin(), p.end(),
//        [](const Point<i64> &a, const Point<i64> &b) { return a.x < b.x; });
//   vector<Point<T>> u{p[0]}, d{p.back()};
//   for (usz i = 1; i < p.size(); ++i) {
//     while (u.size() >= 2 &&
//            ((u.back() - u[u.size() - 2]) ^ (p[i] - u.back())) > 0)
//       u.pop_back();
//     u.push_back(p[i]);
//   }
//   for (usz i = p.size() - 2; (isz)i >= 0; --i) {
//     while (d.size() >= 2 &&
//            ((d.back() - d[d.size() - 2]) ^ (p[i] - d.back())) > 0)
//       d.pop_back();
//     d.push_back(p[i]);
//   }
//   u.insert(u.end(), d.begin() + 1, d.end());
//   return u;
// }

// template <class T>
// vector<Point<T>> minkowski_sum(vector<Point<T>> a, vector<Point<T>> b) {
//   vector<Point<T>> c{a[0] + b[0]};
//   for (usz i = 0; i + 1 < a.size(); ++i) a[i] = a[i + 1] - a[i];
//   for (usz i = 0; i + 1 < b.size(); ++i) b[i] = b[i + 1] - b[i];
//   a.pop_back(), b.pop_back();
//   c.resize(a.size() + b.size() + 1);
//   merge(a.begin(), a.end(), b.begin(), b.end(), c.begin() + 1,
//         [](const Point<i64> &a, const Point<i64> &b) { return (a ^ b) < 0; });
//   for (usz i = 1; i < c.size(); ++i) c[i] = c[i] + c[i - 1];
//   return c;
// }

// int main() {
//   cin.tie(nullptr)->sync_with_stdio(false);
//   uint32_t n, m, q;
//   vector<Point<i64>> a, b;
//   cin >> n >> m >> q;
//   a.resize(n), b.resize(m);
//   for (auto &p : a) cin >> p;
//   for (auto &p : b) cin >> p, p = 0 - p;
//   a = convex_hull(a), b = convex_hull(b);
//   a = minkowski_sum(a, b);
//   a.pop_back();
//   for (usz i = 1; i < a.size(); ++i) a[i] = a[i] - a[0];
//   while (q--) {
//     Point<i64> v;
//     cin >> v;
//     v = v - a[0];
//     if (v.x < 0) {
//       cout << "0\n";
//       continue;
//     }
//     auto it = upper_bound(
//         a.begin() + 1, a.end(), v,
//         [](const Point<i64> &a, const Point<i64> &b) { return (a ^ b) < 0; });
//     if (it == a.begin() + 1 || it == a.end()) {
//       cout << "0\n";
//       continue;
//     }
//     i64 s0 = *it ^ *prev(it), s1 = v ^ *prev(it), s2 = *it ^ v;
//     cout << (s1 >= 0 && s2 >= 0 && s1 + s2 <= s0) << '\n';
//   }
//   return 0;
// }