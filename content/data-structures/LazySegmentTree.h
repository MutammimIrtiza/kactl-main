/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: can use set and add together. ranges are all [), EVEN IN CONSTRUCTOR TOO
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Lseg seg(a, 1, n+1);  /  seg(1, n+1)  / seg(0, n)
 * Status: stress-tested a bit
 */
#pragma once
#include "../various/BumpAllocator.h"

using T = ll;
struct Node { 
    T mn, mx, sm; // ignore variables you dont need
    Node() : mn(inf), mx(-inf), sm(0) {}
    Node(T v) : mn(v), mx(v), sm(v) {}
    Node(T _mn, T _mx, T _sm) : mn(_mn), mx(_mx), sm(_sm) {}
};
struct Lseg {
    // s:set tag (inf=none), a:add tag, v:stored node values
    Lseg *lc=0, *rc=0; int l, r; T s=inf, a=0; Node v;
    // Associative merge function
    Node f(Node i, Node j) {
        return {min(i.mn, j.mn), max(i.mx, j.mx), i.sm + j.sm};
    }
    // Huge interval of neutrals
    Lseg(int _l, int _r): l(_l), r(_r) {}
    Lseg(vll& vc, int _l, int _r): l(_l), r(_r) {
        if (l+1 < r) {
            int m = l+(r-l)/2;
            lc = new Lseg(vc, l, m); rc = new Lseg(vc, m, r);
            v = f(lc->v, rc->v);
        } else if(l < (int)vc.size()) v = Node(vc[l]);
    }
    // apply set
    void ps(T x) { s=v.mn=v.mx=x, a=0, v.sm=x*(r-l); }
    // apply add
    void pa(T x) {
		(s!=inf ? s : a)+=x, v.mn+=x, v.mx+=x, v.sm+=x*(r-l);
	}
    // push
    void ph() {
        int m = l+(r-l)/2;
        if(!lc) lc=new Lseg(l, m), rc=new Lseg(m, r);
        if(s!=inf) lc->ps(s), rc->ps(s), s=inf;
        if(a) lc->pa(a), rc->pa(a), a=0;
    }
    // Range Set: Update all elements in [x, y) to val
    void set(int x, int y, T val) {
        if(y<=l || r<=x) return;
        if(x<=l && r<=y) ps(val);
        else ph(), lc->set(x, y, val), rc->set(x, y, val), \
		    v=f(lc->v, rc->v);
    }
    // Range Add: Add val to all elements in [x, y)
    void add(int x, int y, T val) {
        if(y<=l || r<=x) return;
        if(x<=l && r<=y) pa(val);
        else ph(), lc->add(x, y, val), rc->add(x, y, val), \
		    v=f(lc->v, rc->v);
    }
    // Returns Node containing mn, mx, sm of [x, y)
    Node qry(int x, int y) {
        if(y<=l || r<=x) return Node();
        if(x<=l && r<=y) return v;
        ph(); return f(lc->qry(x, y), rc->qry(x, y));
    }
    // First index in [x, y) with value >= val
    int fst(T val, int x, int y) {
        if(y<=l || r<=x || v.mx<val) return -1;
        if(l+1 == r) return l;
        ph(); int res = lc->fst(val, x, y);
        return (res != -1) ? res : rc->fst(val, x, y);
    }
    ~Lseg() { delete lc; delete rc; }
};