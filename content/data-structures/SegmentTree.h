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
using T = ll;
struct Seg {
    int n, m=1;
    vector<T> t;
    const T unit = -inf;   // identity element

    Seg(int _n): n(_n) {
        while(m<n) m<<=1;
        t.assign(2*m, unit);
    }
    T f(T a, T b) { return max(a, b); } // operation

    void upd(int p, T v) {
        for(t[p+=m]=v;  p>1;  p>>=1)
            t[p>>1] = f(t[p&~1], t[p|1]);// parent, lef, right
    }
    T qry(int l, int r) {   // [l, r)
        T L=unit, R=unit;
        for(l+=m, r+=m;  l<r;  l>>=1, r>>=1) {
            if(l&1) L = f(L, t[l++]);
            if(r&1) R = f(t[--r], R);
        }
        return f(L,R);
    }
    // first position with value >= v
    int first(T v) {
        if(t[1] < v) return -1; 
        int p = 1;
        while(p < m) {
            if(t[2*p] >= v) p = 2*p;
            else p = 2*p+1;
        }
        int res = p - m;
        return (res < n) ? res : -1;
    }
};