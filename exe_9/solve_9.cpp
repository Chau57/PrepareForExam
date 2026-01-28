#include <bits/stdc++.h>

bool isMatch(std::string s, std::string p) {
    const int n = s.length();
    const int m = p.length();
    s = '\0' + s;
    p = '\0' + p;
    std::vector<bool> f(m + 1, false);
    f[0] = true;
    for (int j = 2; j <= m && p[j] == '*'; j += 2) {
        f[j] = true;
    }
    for (int i = 1; i <= n; ++i) {
        std::vector<bool> g = f;
        f[0] = false;
        for (int j = 1; j <= m; ++j) {
            switch(p[j]) {
                case '.':
                    f[j] = g[j - 1];
                    if (p[j - 1] == '*') {
                        f[j] = f[j] | g[j - 3];
                    }
                    break;
                case '*':
                    f[j] = f[j - 2] | f[j - 1] |
                        (g[j] & ((p[j - 1] == '.') | (p[j - 1] == s[i])));
                    break;
                default:
                    f[j] = (s[i] == p[j]) & g[j - 1];
            }
        }
    }
    return f[m];
}

int main(void) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::string s, t; std::cin >> s >> t;
    std::cout << (isMatch(s, t) ? "true\n" : "false\n");
}