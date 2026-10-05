/**
 * Author:
 * Date: 
 * Description:
 */
struct MergeSortTree {
    int n;
    vector<vector<int>> tree;
    MergeSortTree(const vector<int>& a) : n(a.size()), tree(4 * a.size()) {
        build(a, 1, 0, n - 1);
    }
    void build(const vector<int>& a, int node, int l, int r) {
        if (l == r) {
            tree[node] = {a[l]};
            return;
        }
        int mid = l + (r - l) / 2;
        build(a, 2 * node, l, mid);
        build(a, 2 * node + 1, mid + 1, r);
        merge(tree[2 * node].begin(), tree[2 * node].end(),
                   tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
                   back_inserter(tree[node]));
    }
    // Example Method: Count elements strictly greater than k in range [ql, qr]
    int query_gt(int node, int l, int r, int ql, int qr, int k) {
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) {
            auto it = upper_bound(tree[node].begin(), tree[node].end(), k);
            return tree[node].end() - it;
        }
        int mid = l + (r - l) / 2;
        return query_gt(2 * node, l, mid, ql, qr, k) + 
               query_gt(2 * node + 1, mid + 1, r, ql, qr, k);
    }
    int query_gt(int ql, int qr, int k) {
        return query_gt(1, 0, n - 1, ql, qr, k);
    }
};