#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll n, T;
vector<ll> a;

bool check(ll X) {
    // Bước 1: Xây dựng khung M[i] dựa trên mảng a ban đầu và độ cao đích X
    // M[i] là độ cao tối đa tại i sao cho M[i] <= a[i] 
    // VÀ tồn tại ít nhất một điểm j đạt độ cao X (M[j] = X)
    // VÀ |M[i] - M[i+1]| <= 1
    
    // Thực tế, ta chỉ cần tìm xem có tồn tại j nào mà:
    // Tổng chi phí để hạ a về phễu đỉnh X tại j <= T
    
    // Tiền xử lý mảng cộng dồn cho mảng a
    static vector<ll> pref(100005, 0);
    for(int i = 0; i < n; i++) pref[i+1] = pref[i] + a[i];

    for (int j = 0; j < n; j++) {
        // Giả sử j là "đáy phễu" đạt độ cao X
        // Chi phí = Tổng (a[i] - target_h[i])
        // target_h[i] = X + |i - j|
        
        // Tổng target_h từ 0 đến n-1:
        // = (X+j) + (X+j-1) + ... + X + ... + (X + (n-1-j))
        ll sum_target = n * X + (ll)j*(j+1)/2 + (ll)(n-1-j)*(n-j)/2;
        
        ll current_cost = pref[n] - sum_target;
        
        if (current_cost <= T) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    if (!(cin >> n >> T)) return 0;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // Bước 1: Chuẩn hóa mảng a để thỏa mãn |a[i] - a[i+1]| <= 1
    // Đây chính là khung M mà mình đã nói ở các lượt trước
    vector<ll> L(n), R(n);
    L[0] = a[0];
    for (int i = 1; i < n; i++) L[i] = min(a[i], L[i-1] + 1);
    R[n-1] = a[n-1];
    for (int i = n-2; i >= 0; i--) R[i] = min(a[i], R[i+1] + 1);
    
    ll T_prep = 0;
    for (int i = 0; i < n; i++) {
        ll Mi = min(L[i], R[i]);
        T_prep += (a[i] - Mi);
        a[i] = Mi; // Cập nhật mảng a thành khung M
    }
    T -= T_prep; // Số tiền còn lại sau khi xây khung

    // Bước 2: Chặt nhị phân tìm X trên mảng đã chuẩn hóa
    ll low = -1e18, high = 1e9, ans = 1e9;
    for(int i=0; i<n; i++) ans = min(ans, a[i]);

    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    cout << ans << endl;
    return 0;
}