/**
 * Author:
 * Date: 
 * Description:
 */
struct ImplicitSegTree {
    struct Node {
        int val = 0;
        int left = -1, right = -1; // Indices of children in 'nodes' vector
    };
    int L, R;              // Global range [L, R], e.g., [0, 1e9]
    std::vector<Node> nodes;
    ImplicitSegTree(int L, int R) : L(L), R(R) {
        nodes.push_back(Node()); // Root node created at index 0
    }
    void u(int node, int l, int r, int i, int v) {
        if (l == r) { nodes[node].val = v; return; }
        int m = l + (r - l) / 2;
        if (i <= m) {
            if (nodes[node].left == -1) {
                nodes[node].left = nodes.size();
                nodes.push_back(Node());
            }
            u(nodes[node].left, l, m, i, v);
        } else {
            if (nodes[node].right == -1) {
                nodes[node].right = nodes.size();
                nodes.push_back(Node());
            }
            u(nodes[node].right, m + 1, r, i, v);
        }
        int left_val = (nodes[node].left != -1) ? nodes[nodes[node].left].val : 0;
        int right_val = (nodes[node].right != -1) ? nodes[nodes[node].right].val : 0;
        nodes[node].val = std::max(left_val, right_val);
    }
    int q(int node, int l, int r, int ql, int qr) {
        if (node == -1 || r < ql || l > qr) return -1e9; // Missing node or out of bounds
        if (ql <= l && r <= qr) return nodes[node].val;  // Fully inside
        int m = l + (r - l) / 2;
        return std::max(q(nodes[node].left, l, m, ql, qr),
                        q(nodes[node].right, m + 1, r, ql, qr));
    }
    int f(int node, int l, int r, int ql, int qr, int x) {
        if (node == -1 || l > qr || r < ql || nodes[node].val < x) return -1;
        if (l == r) return l;
        int m = l + (r - l) / 2;
        int res = f(nodes[node].left, l, m, ql, qr, x);
        if (res != -1) return res;
        return f(nodes[node].right, m + 1, r, ql, qr, x);
    }
    // --- PUBLIC INTERFACE ---
    void u(int i, int v) { u(0, L, R, i, v); }
    int q(int ql, int qr) { return q(0, L, R, ql, qr); }
    int f(int ql, int qr, int x) { return f(0, L, R, ql, qr, x); }
};