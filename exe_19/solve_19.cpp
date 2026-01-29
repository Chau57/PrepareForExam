#include <bits/stdc++.h>

#define ll long long
#define int long long

const int N = (int)1e5 + 3;
const ll INF = (ll)1e18;
const ll BASE = (ll)1e17;

int n;
ll k;
int a[N];

ll f[N];
int b[N];
int L[N], R[N];

bool check(ll h) {
    for (int i = 1; i <= n; ++i) {
        if (h >= a[i]) return true;
    }

    std::fill(b + 1, b + 1 + n, 0);
    // j < i
    // need: a[j] <= h + i - j
    // add: a[j] > h + i - j
    // -> i > a[j] + j - h
    // stop: i = a[j] + j - h
    for (int j = 1; j <= n; ++j) {
        int i = std::max(1LL, a[j] + j - h);
        if (i <= n) b[i] = j;
    }
    // i -> b[i] cost 0
    // i + 1 -> b[i] still cost 0, b[i + 1] cost 0 too
    int maxL = 0;
    for (int i = 1; i <= n; ++i) {
        maxL = std::max(maxL, b[i]);
        L[i] = maxL + 1;
    }

    std::fill(b + 1, b + 1 + n, n + 1);
    for (int j = n; j >= 1; --j) {
        int i = std::min(1LL * n, h + j - a[j]);
        if (1 <= i) b[i] = j;
    }
    int minR = n + 1;
    for (int i = n; i >= 1; --i) {
        minR = std::min(minR, b[i]);
        R[i] = minR - 1;
    }

    for (int i = 1; i <= n; ++i) {
        int lb = L[i], rb = R[i];
        ll cur = f[rb] - f[lb - 1];
        cur -= (i - lb) * (i - lb + 1) / 2; // lb <- i, 0+1+2+3+...(i-lb)
        cur -= (rb - i) * (rb - i + 1) / 2; // i -> rb, 0+1+2+3+...+(rb-i)
        if (-h >= (INF + BASE) / (rb - lb + 1)) continue;
        cur -= h * (rb - lb + 1); // Plus base h for [lb; rb]
        if (cur <= k) return true;
    }
    return false;
}

signed main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(NULL);
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];

    f[0] = 0;
    for (int i = 1; i <= n; ++i) f[i] = f[i - 1] + a[i];

    ll ret = *std::min_element(a + 1, a + 1 + n);
    ll lb = -INF;
    ll rb = ret - 1;
    while (lb <= rb) {
        int mb = (lb + rb) >> 1;
        if (check(mb)) {
            rb = mb - 1;
            ret = mb;
        } else {
            lb = mb + 1;
        }
    }
    std::cout << ret << std::endl;
}