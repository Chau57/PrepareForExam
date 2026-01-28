// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>

using namespace std;
#define M 100
#define N 100

int m = 0, n = 0;
int a[M+1][N+1], f[M+1][N+1], g[M+1][N+1];
int ans;
int main() {
	cin >> m >> n;
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++)
			cin >> a[i][j];
	for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(a[i][j] == 1)
                f[i][j] = min({f[i-1][j-1], f[i-1][j], f[i][j-1]}) + 1;
            else
                g[i][j] = min({g[i-1][j-1],g[i-1][j],g[i][j-1]}) + 1;

            ans = max(ans,max(f[i][j], g[i][j]));
        }
    }
    cout << ans << '\n';
	return 0;
}