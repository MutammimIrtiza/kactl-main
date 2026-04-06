/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: ...
 * Time: ...
 * Usage: vector<Node *> pref(n+1);
 * pref[0] = build(0, unqvals); // [0, unqvals) 
 * trees[k] = change(trees[k-1], 0, unqvals, pos, x);
 * cout << query(trees[k], 0, unqvals, l, r+1) << nl;
 * Status: ...
 */
struct Node {
    Node *left = nullptr, *right = nullptr;  ll sum = 0;
};
// Builds a segment tree on [l,r). use same [l,r) in qry, upd
// Returns a pointer to the constructed tree.
Node *build(int l, int r) {
    Node *p = new Node();
    if (r - l == 1) return p;
    int m = (l + r) / 2;
    p->left = build(l, m);
    p->right = build(m, r);
    return p;
}
// Changes value in position k to x in tree p.
// Returns a pointer to the new tree.
Node *change(Node *p, int l, int r, int k, int x) {
    Node *n = new Node(*p);
    if (r - l == 1) { n->sum = x; }
    else {
        int m = (l + r) / 2;
        if (k < m) { n->left = change(p->left, l, m, k, x); }
        else { n->right = change(p->right, m, r, k, x); }
        n->sum = n->left->sum + n->right->sum;
    } 
    return n;
}
// Returns the sum of values in range [ql, qr).
ll query(Node *p, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return p->sum;
    int m = (l + r) / 2;
    return query(p->left, l, m, ql, qr) + 
            query(p->right, m, r, ql, qr);
}