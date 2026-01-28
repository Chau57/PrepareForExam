// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
#include <sstream>
using namespace std;

vector<int> a(1,0);
long long f[21];
bool used[21];
int ans[21];



int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string l;
    long long y = 0;
    getline(cin, l);
    int x;
    cin >> y;
    stringstream s(l);
    while(s >> x)
    {
        a.push_back(x);
    } 
    int n = a.size() - 1;
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        f[i] = f[i - 1] * i;

    long long rankX = 1;
    for (int i = 1; i <= n; i++) {
        int pi = a[i];
        long long cntLess = 0;
        for (int v = 1; v < pi; v++)
            if (!used[v])
                ++cntLess;

        rankX += cntLess * f[n - i];
        used[pi] = true;
    }

    cout << rankX << '\n';
    vector<int> S;
    for(int i = 1; i <= n; i++) S.push_back(i);
    y--; // 0-based
    for (int i = 1; i <= n; i++) {
        long long block = f[n - i];
        long long idx = (block == 0) ? 0 : (y / block);
        ans[i] = S[(size_t)idx];
        S.erase(S.begin() + (ptrdiff_t)idx);
        if (block != 0) y %= block;
    }

    for(int i = 1; i <= n; i++)
    {
        cout << ans[i] << " ";
    }
}


