/*
    prove: https://www.youtube.com/watch?v=M64HUIJFTZM

*/
#include <bits/stdc++.h>

#define pii std::pair<int, int>

const int N = (int)1e5 + 3;

pii p[N];
int id[N];
int pivot;

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

int main(void) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n; std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> p[i].first >> p[i].second;

    
    pivot = 1;
    for (int i = 2; i <= n; ++i) {
        if (p[pivot].first > p[i].first || (p[pivot].first == p[i].first && p[pivot].second > p[i].second)) {
            pivot = i;
        }
    }
    for (int i = 1; i <= n; ++i) id[i] = i;
    std::swap(id[1], id[pivot]);
    std::sort(id + 2, id + 1 + n, [](int &x, int &y) {
        return CCW(p[pivot], p[x], p[y]) > 0;
    });

    std::cout << pivot << ' ' << id[n / 2 + 1] << '\n';
    return 0;
}