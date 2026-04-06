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

struct Node { 
  ll mn, mx, sum; // ignore variables you dont need
  Node() : mn(inf), mx(-inf), sum(0) {}
  Node(ll x) : mn(x), mx(x), sum(x) {}
  Node(ll x, ll y, ll z) : mn(x), mx(y), sum(z) {}
};

struct Lseg {
  Lseg *l = 0, *r = 0;   int lo, hi;   ll mset = inf, madd = 0;
  Node val;

  Node unite(Node a, Node b) {
	return Node(min(a.mn, b.mn), max(a.mx, b.mx), a.sum + b.sum);
  }

Lseg(int lo,int hi):lo(lo),hi(hi){}//Huge interval of neutrals

  Lseg(vll& v, int _lo, int _hi) : lo(_lo), hi(_hi) {
	if (lo + 1 < hi) {
	  int mid = lo + (hi - lo)/2;
	  l = new Lseg(v, lo, mid); r = new Lseg(v, mid, hi);
	  val = unite(l->val, r->val);
	} else val = Node(v[lo]);
  }

  Node query(int L, int R) {
	if (R <= lo || hi <= L) return Node();
	if (L <= lo && hi <= R) return val;
	push();
	return unite(l->query(L, R), r->query(L, R));
  }

  void set(int L, int R, ll x) {  // skip if not needed
	if (R <= lo || hi <= L) return;
	if (L <= lo && hi <= R) {
	  mset = val.mn = val.mx = x, madd = 0;
	  val.sum = x * (hi - lo);
	} else {
	  push(), l->set(L, R, x), r->set(L, R, x);
	  val = unite(l->val, r->val);
	}
  }

  void add(int L, int R, ll x) {  // skip if not needed
	if (R <= lo || hi <= L) return;
	if (L <= lo && hi <= R) {
	  if (mset != inf) mset += x;
	  else madd += x;
	  val.mn += x, val.mx += x, val.sum += x * (hi - lo);
	} else {
	  push(), l->add(L, R, x), r->add(L, R, x);
	  val = unite(l->val, r->val);
	} 
  }

  void push() {
	if (!l) {
	  int mid = lo + (hi - lo)/2;
	  l = new Lseg(lo, mid); r = new Lseg(mid, hi);
	}
	if (mset != inf)
	  l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
	else if (madd)
	  l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
  }

  int myQ(ll val, int L, int R) { // first idx >= val
	  if (R <= lo || hi <= L) return -1;
	  if (val > this->val.mx) return -1;
	  if (lo + 1 == hi) return lo;
	  push();
	  int res = l->myQ(val, L, R);  if(res != -1) return res;
	  return r->myQ(val, L, R);  
	}  
	~Lseg() { delete l; delete r; }; // must if you want to debug
}