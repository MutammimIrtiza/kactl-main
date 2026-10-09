/**
 * Author:
 * Date: 
 * Description:
 */
struct PersistentSegTree {
    struct Node {
        int l = 0, r = 0; ll mx = -inf; // add/change as needed
    };
    vector<Node> st;
    PersistentSegTree() {st.push_back(Node());} // 0 = null
    int update(int prev, int tl, int tr, int pos, ll val) {
        st.push_back(st[prev]); // new copy of prev's root
        int cur = (int)st.size() - 1;
        if (tl == tr) {
            st[cur].mx = val;
            return cur;
        }
        int tm = (tl + tr) >> 1; // either l/r of root changes
        if (pos <= tm)
          st[cur].l = update(st[prev].l, tl, tm, pos, val);
        else 
          st[cur].r = update(st[prev].r, tm + 1, tr, pos, val);

        st[cur].mx = max(st[st[cur].l].mx, st[st[cur].r].mx);
        return cur;
    }
    // query(root[i], 0, n-1, l, r) means
    // maximum on range [l,r] in version i
    ll query(int node, int tl, int tr, int l, int r) {
        if (!node || r < tl || tr < l) return -INF;
        if (l <= tl && tr <= r) return st[node].mx;
        int tm = (tl + tr) >> 1;
        return max( 
            query(st[node].l, tl, tm, l, r),
            query(st[node].r, tm + 1, tr, l, r)
        );
    }
// CUSTOM:
// Collect all ids in this version whose stored v >= need.
// Problem statement bounds total leaves accessed, not costly
    void collect(int node, int tl, int tr, ll v_need, vector<int>& out) const {
        if (node == 0 || st[node].mx < v_need) return;
        if (tl == tr) { out.push_back(tl); return; }
        int tm = (tl + tr) >> 1;
        collect(st[node].l, tl, tm, v_need, out);
        collect(st[node].r, tm + 1, tr, v_need, out);
    }
};
/* USAGE */
PersistentSegTree pst;
vector<int> root(N + 1, 0);
for (int i = N - 1; i >= 0; i--) {//or forward, whatever works
    root[i] = pst.update(root[i + 1], 0, N - 1, pos, val);
}
/*
  k-th on tree path : versions for each tree node. 
  Each node extends from it's parent's version.
  seg tree is ON the node values (compressed). 
  each segtree index HOLDS total count over all it's ancestors
  inner nodes hold total of left child + right child.
  walk down 3 versions simultaneously. 
  at current segtree node, for both children :
  use LCA formula to calculate count of elements in that range
  go left or right acccording to current k
*/
