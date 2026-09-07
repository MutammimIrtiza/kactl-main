/**
 * Author: Gemini
 * Date: 
 * Description:
 */
using T = ll; 
struct Lseg {
    struct node { T mn=0, mx=0, sm=0; }; // remove/add 
    
    int n; 
    vector<node> tr; 
    vector<T> s, a; // s:set tag, a:add tag

    Lseg(int _n) : n(_n), tr(4*n), s(4*n, inf), a(4*n, 0) {}

    inline node f(const node& i, const node& j) { // merge 
        return {min(i.mn, j.mn), max(i.mx, j.mx), i.sm + j.sm};
    }

    inline void ps(int u, int l, int r, T x) { // apply set.
        s[u]=tr[u].mn=tr[u].mx=x, a[u]=0, tr[u].sm=x*(r-l);
    } 

    inline void pa(int u, int l, int r, T x) { // apply add. 
        (s[u]!=inf ? s[u] : a[u])+=x;
        tr[u].mn+=x, tr[u].mx+=x, tr[u].sm+=x*(r-l);
    }

    inline void ph(int u, int l, int r) { // push
        int m = l+(r-l)/2, lc = u<<1, rc = lc|1;
        if(s[u]!=inf) 
            ps(lc, l, m, s[u]), ps(rc, m, r, s[u]), s[u]=inf;
        if(a[u]) 
            pa(lc, l, m, a[u]), pa(rc, m, r, a[u]), a[u]=0;
    }
    // set [x, y) to val
    void set(int x, int y, T val, int u, int l, int r) { 
        if(x<=l && r<=y) return ps(u, l, r, val);
        ph(u, l, r); int m = l+(r-l)/2;
        if(x < m) set(x, y, val, u<<1, l, m);
        if(y > m) set(x, y, val, u<<1|1, m, r);
        tr[u] = f(tr[u<<1], tr[u<<1|1]);
    }
    // Add val to [x, y)
    void add(int x, int y, T val, int u, int l, int r) { 
        if(x<=l && r<=y) return pa(u, l, r, val);
        ph(u, l, r); int m = l+(r-l)/2;
        if(x < m) add(x, y, val, u<<1, l, m);
        if(y > m) add(x, y, val, u<<1|1, m, r);
        tr[u] = f(tr[u<<1], tr[u<<1|1]);
    }

    node qry(int x, int y, int u, int l, int r) {
        if(x<=l && r<=y) return tr[u];
        ph(u, l, r); int m = l+(r-l)/2;
        // fully in left child, fully in right child, overlap
        if(y <= m) return qry(x, y, u<<1, l, m);      
        if(x >= m) return qry(x, y, u<<1|1, m, r);    
        return 
            f(qry(x, y, u<<1, l, m), qry(x, y, u<<1|1, m, r)); 
    }
    // First index in [x, y) >= val
    int fst(T val, int x, int y, int u, int l, int r) { 
        if(tr[u].mx < val) return -1; // pruned early
        if(l+1 == r) return l;
        ph(u, l, r); int m = l+(r-l)/2;
        if(x < m) {
            int res = fst(val, x, y, u<<1, l, m);
            if(res != -1) return res;
        }
        if(y > m) return fst(val, x, y, u<<1|1, m, r);
        return -1;
    }

    // --- PUBLIC WRAPPERS ---
    void set(int x, int y, T val){if(x<y) set(x,y,val,1,0,n); }
    void add(int x, int y, T val){if(x<y) add(x,y,val,1,0,n); }
    node qry(int x, int y)
        {return (x<y) ? qry(x,y,1,0,n) : node{inf,-inf,0}; }
    int fst(T val, int x, int y)
        {return (x<y) ? fst(val,x,y,1,0,n) : -1; }
};