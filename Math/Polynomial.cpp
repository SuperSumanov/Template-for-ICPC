#include <bits/stdc++.h>

using namespace std;

namespace Convolution{
    const double PI = acos(-1.0);

    struct Complex {
        double x, y;

        Complex(double _x = 0.0, double _y = 0.0) {
            x = _x;
            y = _y;
        }

        Complex operator-(const Complex &b) const {
            return Complex(x - b.x, y - b.y);
        }

        Complex operator+(const Complex &b) const {
            return Complex(x + b.x, y + b.y);
        }

        Complex operator*(const Complex &b) const {
            return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
        }
    };
    int get_full_length(int len)
    {
        int ret = 1;
        while (ret < len * 2) ret <<= 1;
        return ret;
    }
    void change(std::vector <Complex> &y, int len)
    {
        int i, j, k;

        for (int i = 1, j = len / 2; i < len - 1; i++) {
            if (i < j) std::swap(y[i], y[j]);

            // 交换互为小标反转的元素，i<j 保证交换一次
            // i 做正常的 + 1，j 做反转类型的 + 1，始终保持 i 和 j 是反转的
            k = len / 2;

            while (j >= k) {
            j = j - k;
            k = k / 2;
            }

            if (j < k) j += k;
        }
           
    }
    void fft(std::vector<Complex> &y, int len, int on)
    {
        change(y, len);

        for (int h = 2; h <= len; h <<= 1) {
            Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));

            for (int j = 0; j < len; j += h) {
            Complex w(1, 0);

            for (int k = j; k < j + h / 2; k++) {
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
            }
        }

        if (on == -1) {
            for (int i = 0; i < len; i++) {
            y[i].x /= len;
            }
        }
    }

    // Mind that the start point of the array is 0 NOT 1;
    template <typename T>
    void FFT(T *a, T *b, int lena, int lenb, T *result)
    {
        std::vector <Complex> X, Y;
        X.clear(); Y.clear();
        int len = max(get_full_length(lena), get_full_length(lenb));
        for (int i = 0; i < lena; i++) X.push_back(Complex(a[i], 0));
        for (int i = lena; i < len; i++) X.push_back(Complex(0, 0));
        for (int i = 0; i < lenb; i++) Y.push_back(Complex(b[i], 0));
        for (int i = lenb; i < len; i++) Y.push_back(Complex(0, 0));
        fft(X, len, 1);
        fft(Y, len, 1);
        for (int i = 0; i < len; i++) X[i] = X[i] * Y[i];
        fft(X, len, -1);
        if constexpr(std::is_same_v<T, int> || std::is_same_v<T, long long>)
                for (int i = 0; i < len; i++) result[i] = T(X[i].x + 0.5);
        else for (int i = 0; i < len; i++) result[i] = X[i].x;
    }   
};








// For Testing;

const int MAXN = 1e6 + 7;
int a[MAXN], b[MAXN], c[MAXN * 2];
int main()
{
    int n, m;
    cin >> n >> m; n++; m++;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    Convolution::FFT(a, b, n, m, c);
    for (int i = 0; i < n + m - 1; i++) cout << c[i] << ' ';
    cout << '\n';
}