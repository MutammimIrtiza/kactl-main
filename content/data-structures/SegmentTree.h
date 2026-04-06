/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once
struct Seg { // left child even, right odd
    ll unit = -inf;     // identity element
    int n,  m=1;   vector<ll> t;
    
    Seg(int _n) : n(_n) {while(m<n)m<<=1;  t.resize(4*m,unit);}
    ll f(ll a, ll b) { return max(a, b); } // change operation

    void update(int p,  ll value) {
        for (t[p += m] = value;  p > 1;  p >>= 1) {
            t[p>>1] = f(t[p],  t[p^1]); // p>>1 is parent
        } 
    }
    ll query(int l, int r) { // [l, r)
        ll resL = unit, resR = unit;
        for (l += m, r += m;  l < r;  l >>= 1, r >>= 1) {
            if (l & 1) resL = f(resL,  t[l++]);
            if (r & 1) resR = f(t[--r],  resR);
        }
        return f(resL,  resR);
    }
    // find first position having element >= val in a range
    ll myQ(int val) {return myQ(val,1,0, m, 0,n);} //whole range
    ll myQ(int val, int pos, int l, int r, int ql, int qr) {
        if (r <= ql || qr <= l) return -1;   // no overlap
        if (t[pos] < val) return -1;       // all values < val
        if (l + 1 == r) return l;          // leaf node
        int mid = (l + r) / 2;
        int left = myQ(val,   2*pos, l, mid,   ql, qr);
        if (left != -1) return left;
        return myQ(val,   2*pos+1, mid, r,  ql, qr);  
    }  
};