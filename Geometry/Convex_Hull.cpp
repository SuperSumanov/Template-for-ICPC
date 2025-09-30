#include <bits/stdc++.h>

using namespace std;

namespace VectorSpace{
    struct Point{
        double x, y, ang;
        friend Point operator-(const Point &s, const Point &p) {return {s.x - p.x, s.y - p.y, 0};}
        friend double operator^(const Point &s, const Point &p) { return s.x * p.y - s.y * p.x;}
        friend bool operator!=(const Point &s, const Point &p) {return (s.x != p.x) || (s.y != p.y);}
    };

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


