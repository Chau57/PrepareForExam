#include <iostream>
#include <cmath>
using namespace std;

int main() {
    long long S;
    cin >> S;

    for (long long a = 0; a * a <= S; a++) {
        long long b2 = S - a * a;
        long long b = sqrt(b2);

        if (b * b == b2) {
            cout << 0 << " " << 0 << "\n";
            cout << a << " " << b << "\n";
            cout << a - b << " " << b + a << "\n";
            cout << -b << " " << a << "\n";
            return 0;
        }
    }

    cout << "Impossible\n";
    return 0;
}
