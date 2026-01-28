#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string a,b;
    cin >> a >> b;
    string s = b + "#" + a;
    vector<int> pi = prefix_function(s);
    int m = a.length(), n = b.length();

    for (int i = n + 1; i < m + n + 1; i++) {
        if(pi[i] == n)
            cout << i - 2*n + 1 << " ";
    }
}
