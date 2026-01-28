/*
    1. Goldbach theorem
    -> Sieve and compute
    2. Not multiplicative function
    -> FFT
*/
#include <bits/stdc++.h>

const int N  = (int)2e4 + 3;
const int N2 = (int)5e4 + 3;

int n;
long long f[N];

std::vector<int> prime;
bool isComposite[N2];
void linearSieve(void) {
    std::fill(isComposite, isComposite + 1 + N2, false);
    isComposite[0] = isComposite[1] = true;
    prime.clear();
    for (int x = 2; x <= N2 - 3; ++x) {
        if (!isComposite[x]) prime.push_back(x);
        for (int j = 0; j < prime.size() && x * prime[j] <= N2 - 3; ++j) {
            isComposite[x * prime[j]] = true;
            if (x % prime[j] == 0) break;
        }
    }
}

int main(void) {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cin >> n;
    linearSieve();
    for (int i = 0; i < prime.size(); ++i) {
        for (int j = i; j < prime.size(); ++j) {
            int sum = prime[i] + prime[j];
            if (sum <= n + n && sum % 2 == 0) {
                ++f[sum / 2];
            }
        }
    }
    for (int x = 1; x <= n; ++x) f[x] += f[x - 1];
    std::cout << f[n] << std::endl;
    return 0;
}