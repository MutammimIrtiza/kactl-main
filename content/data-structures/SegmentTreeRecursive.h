/**
 * Author:
 * Date: 
 * Description:
 */
struct SegTree { // 0 based
    int n;           
    vector<int> t;   
    SegTree(int n) : n(n), t(4 * n, 0) {}
    void u(int node, int l, int r, int i, int v) {
        if (l == r) { t[node] = v; return; }
        int m = (l + r) / 2;
        if (i <= m) u(2 * node, l, m, i, v);
        else u(2 * node + 1, m + 1, r, i, v);
        t[node] = max(t[2 * node], t[2 * node + 1]);
    }
    int q(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return t[node]; // Fully in
        if (r < ql || l > qr) return -inf;     // Outside
        int m = (l + r) / 2;
        return max(q(2 * node, l, m, ql, qr), q(2 * node + 1, m + 1, r, ql, qr));
    }
    int f(int node, int l, int r, int ql, int qr, int x) {
        if (l > qr || r < ql || t[node] < x) return -1; 
        if (l == r) return l;      // Target leaf index found
        int m = (l + r) / 2;
        int res = f(2 * node, l, m, ql, qr, x); // left first
        if (res != -1) return res;
        return f(2 * node + 1, m + 1, r, ql, qr, x); // right
    }
    // Update array[i] = v
    void u(int i, int v) { u(1, 0, n - 1, i, v); }
    // Query max value in range [ql, qr]
    int q(int ql, int qr) { return q(1, 0, n - 1, ql, qr); }
    // Find first index in range [ql, qr] where value >= x (-1 if none)
    int f(int ql, int qr, int x) { return f(1, 0, n - 1, ql, qr, x); }
};
int main() {
    vector<int> a = {1, 3, 2, 5, 4, 7};
    SegTree st(a.size());
    for(int i = 0; i < a.size(); i++) st.u(i, a[i]);
    cout << st.q(1, 4) << "\n"; // Max in [1, 4] -> 5
    cout << st.f(0, 5, 4) << "\n";// 1st >= 4 in [0, 5] : idx 3
    return 0;
}