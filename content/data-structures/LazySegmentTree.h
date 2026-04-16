/**
 * Author: Gemini
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: can use set and add together. ranges are all [), EVEN IN CONSTRUCTOR ***
 * Time: O(\log N).
 * Usage: Lseg seg(0, n); Lseg seg(-50000, 50001)
 * Status: stress-tested a bit
 */
#pragma once

using T = ll;
struct Node {
    T mn=inf, mx=-inf, sm=0; // remove/add variables as needed
};
struct Lseg {
    Lseg *lc=0, *rc=0; Node v; int l, r;

    // s:set tag (inf=none), a:add tag, v:stored node values
    T s=inf, a=0; //custom

    Node f(Node i, Node j) { // merge function  // custom
        return {min(i.mn, j.mn), max(i.mx, j.mx), i.sm + j.sm};
    }

    // Huge interval of neutrals
    Lseg(int _l, int _r): l(_l), r(_r) {}
    
    void ps(T x) { // apply set  // custom
        s=v.mn=v.mx=x, a=0, v.sm=x*(r-l);
    } 

    void pa(T x) { // apply add  //custom
		(s!=inf ? s : a)+=x, v.mn+=x, v.mx+=x, v.sm+=x*(r-l);
	}

    void ph() { // push
        int m = l+(r-l)/2;
        if(!lc) lc=new Lseg(l, m), rc=new Lseg(m, r);
        if(s!=inf) lc->ps(s), rc->ps(s), s=inf;  //custom
        if(a) lc->pa(a), rc->pa(a), a=0; //custom
    }
    
    void set(int x, int y, T val) { // set [x, y) to val
        if(y<=l || r<=x) return;
        if(x<=l && r<=y) ps(val); //custom
        else ph(), lc->set(x, y, val), rc->set(x, y, val), \
		    v=f(lc->v, rc->v);
    }

    void add(int x, int y, T val) { // Add val to [x, y)
        if(y<=l || r<=x) return;
        if(x<=l && r<=y) pa(val); //custom
        else ph(), lc->add(x, y, val), rc->add(x, y, val), \
		    v=f(lc->v, rc->v);
    }

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