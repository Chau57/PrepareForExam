#include <bits/stdc++.h>
using namespace std;
int m, n;
vector<pair<long long, int>> a, b;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> m >> n;
    for(int i = 0; i < m; i++)
    {
        long long x;
        cin >> x;
        a.push_back({x,i+1});
    }
    for(int i = 0; i < n; i++)
    {
        long long x;
        cin >> x;
        b.push_back({x,i+1});
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    int i = 0, j = n - 1;
    long long bestAbs = LLONG_MAX;
    int bestI = a[0].second, bestJ = b[0].second;

    while (i < m && j >= 0) {
        long long sum = a[i].first + b[j].first;
        long long curAbs = llabs(sum);
        if (curAbs < bestAbs) {
            bestAbs = curAbs;
            bestI = a[i].second;
            bestJ = b[j].second;
            if (bestAbs == 0) break;
        }

        if (sum > 0) {
            --j;
        } else {
            ++i;
        }
    }
    
    cout << bestI << " " << bestJ;
}