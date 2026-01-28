#include <bits/stdc++.h>

#define pii std::pair<int, int>

const int N = (int)1e5 + 3;

pii p[N];
long long f[N];

pii operator-(const pii &a, const pii &b)
{
   return std::make_pair(a.first - b.first, a.second - b.second);
}
 
long long operator*(const pii &a, const pii &b)
{
   return 1LL * a.first * b.second - 1LL * a.second * b.first;
}
 
long long CCW(const pii &a, const pii &b, const pii &c)
{
   return (b - a) * (c - b);
}

long long calc(int i, int r) {
    return f[r] - f[i] - CCW(p[1], p[i], p[r]);
}

int main(void) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n; std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> p[i].first >> p[i].second;

    f[1] = f[2] = 0;
    for (int i = 3; i <= n; ++i) {
        f[i] = f[i - 1] + CCW(p[1], p[i - 1], p[i]);
    }
    f[n + 1] = f[n];

    int s = 1, t = n;
    long long ret = f[n];
    for (int i = 1; i <= n - 2; ++i) {
        int l = i + 2;
        int r = n;
        while (l <= r) {
            int m = (l + r) >> 1;
            long long f1 = abs(f[n] - 2 * calc(i, m - 1));
            long long f2 = abs(f[n] - 2 * calc(i, m));
            long long f3 = abs(f[n] - 2 * calc(i, m + 1));
            if (f1 >= f2 && f2 <= f3) {
                if (ret > f2) {
                    ret = f2;
                    s = i;
                    t = m;
                }
                break;
            }
            if (f1 >= f2 && f2 >= f3) {
                l = m + 1;
                if (ret > f3) {
                    ret = f3;
                    s = i;
                    t = m + 1;
                }
            }
            if (f1 <= f2 && f2 <= f3) {
                r = m - 1;
                if (ret > f1) {
                    ret = f1;
                    s = i;
                    t = m - 1;
                }
            }
        }
    }
    std::cout << s << ' ' << t << std::endl;
    return 0;
}