#include<bits/stdc++.h>
using namespace std;

    // m lớn => ko thể xử lý như số thông thường
    // xây dựng m từ trái -> phải, chỉ dùng 0 và 1
    // dùng bfs trên phần dư của m khi chia cho n 
    
    // Cách duyệt:
    // - Xem quá trình xây dựng m như một cây nhị phân:
    //     + Mỗi nút là một số (hoặc tương đương là một phần dư mod n).
    //     + Mỗi nút có 2 nhánh con: nối thêm '0' hoặc nối thêm '1'.
    // - Duyệt cây theo BFS để đảm bảo số có ít chữ số hơn được xét trước,
    //   do đó khi gặp phần dư = 0 lần đầu tiên thì m tương ứng là nhỏ nhất.

    // Tối ưu: duyệt bfs với cây nhị phân: O(2*L) với L = len({0,1})
    // mở rộng: On: cũng bfs như trên, nhưng visited chứa phần dư
    // - Nếu một phần dư đã được thăm, nghĩa là đã tồn tại một số ngắn hơn
    //   cho ra cùng phần dư, nên không cần mở rộng nhánh đó nữa.
    
    // Kết luận:
    // - BFS trên các trạng thái phần dư (tối đa n trạng thái).
    // - Độ phức tạp thời gian O(n), bộ nhớ O(n).

int main(){
    int n; cin>>n;
    queue<int> q; 

    q.push(1 % n);             //số đầu tiên là 1
    vector<int> visited(n,0);
    vector<int> parent(n,-1); //lưu số cha
    vector<int> how(n,-1);   //lưu cách tạo số từ cha (thêm 0 hay 1)
    visited[1 % n] = 1;
    how[1 % n] = 1;

    while (!q.empty())
    {
        int rem = q.front(); q.pop();
        if (rem == 0) { //tìm được số chia hết
            //xây dựng số từ parent và how
            string res = "";
            while (parent[rem] != -1) {
                res += (how[rem] + '0');
                rem = parent[rem];
            }
            res += "1";
            reverse(res.begin(), res.end());
            cout << res << endl;
            break;
        }
        //thêm 0
        int rem0 = (rem * 10) % n;
        if (!visited[rem0]) {
            visited[rem0] = 1;
            parent[rem0] = rem;
            how[rem0] = 0;
            q.push(rem0);
        }
        //thêm 1
        int rem1 = (rem * 10 + 1) % n;
        if (!visited[rem1]) {
            visited[rem1] = 1;
            parent[rem1] = rem;
            how[rem1] = 1;
            q.push(rem1);
        }
    }
    return 0;
}