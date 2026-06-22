/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

using lt = __int128;
struct Line { ll k, m; };
struct CHT {
    vector<Line> h; int p = 0;
    // Returns true if l2 becomes redundant between l1 and l3
    bool bad(Line l1, Line l2, Line l3) {
        return (lt)(l2.m - l1.m) * (l1.k - l3.k) \
		 >= (lt)(l3.m - l1.m) * (l1.k - l2.k);
    }
    // Slopes (k) must be added in non-decreasing order
    void add(ll k, ll m) {
        if (!h.empty() && h.back().k == k) {
            if (h.back().m >= m) return;
            h.pop_back();
        }
        while(h.size()>=2 && bad(h[h.size()-2],h.back(),{k,m}))
            h.pop_back();
        h.push_back({k, m});
    }
    // O(1) query: requires x to be non-decreasing
    ll query(ll x) {
        p = min(p, (int)h.size() - 1);
        while (p < h.size() - 1 && \
		 h[p].k * x + h[p].m <= h[p+1].k * x + h[p+1].m) 
            p++;
        return h[p].k * x + h[p].m;
    }
    // O(log N) query: if x is random/not monotonic
    ll query_bs(ll x) {
        int l = 0, r = h.size() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (h[mid].k * x + h[mid].m < \
				 h[mid+1].k * x + h[mid+1].m) l = mid + 1;
            else r = mid;
        }
        return h[l].k * x + h[l].m;
    }
};