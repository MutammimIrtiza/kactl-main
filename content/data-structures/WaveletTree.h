/**
 * Author:
 * Date: 
 * Description:
 */
const int MAXV = (int)1e9 + 9;//max val of any element in array
//array values can be negative too, so \
 use appropriate minimum and maximum value
struct wavelet_tree {
    int lo, hi;
    wavelet_tree *l, *r;
    int *b;       // prefix sum of cnt <= mid
    long long *c; // prefix sum of elements
    int bsz, csz;

    wavelet_tree() : lo(1), hi(0), l(nullptr), r(nullptr),\
        b(nullptr), c(nullptr), bsz(0), csz(0) {}

    void init(int *from, int *to, int x, int y) {
        lo = x; hi = y;
        if (from >= to) return;
        int mid = (lo + hi) >> 1;
        auto f = [mid](int x){ return x <= mid; };
        int n = to - from;
        b = (int*)malloc((n + 2) * sizeof(int));
        c = (long long*)malloc((n + 2) * sizeof(long long));
        b[0] = 0;
        c[0] = 0;
        for (int i = 0; i < n; i++) {
            b[i + 1] = b[i] + f(from[i]);
            c[i + 1] = c[i] + from[i]; // use long long
        }
        bsz = n + 1;
        csz = n + 1;
        if (lo == hi) return;
        auto pivot = stable_partition(from, to, f);
        l = new wavelet_tree();
        l->init(from, pivot, lo, mid);
        r = new wavelet_tree();
        r->init(pivot, to, mid + 1, hi);
    }
    //kth smallest element in [l, r]
    int kth(int lpos, int rpos, int k) {
        if (lpos > rpos) return 0;
        if (lo == hi) return lo;
        int inLeft = b[rpos] - b[lpos - 1];
        int lb = b[lpos - 1], rb = b[rpos];
        if (k <= inLeft) return l->kth(lb + 1, rb, k);
        return r->kth(lpos - lb, rpos - rb, k - inLeft);
    }
    //count of numbers in [l, r] Less than or equal to k
    int LTE(int lpos, int rpos, int k) {
        if (lpos > rpos || k < lo) return 0;
        if (hi <= k) return rpos - lpos + 1;
        int lb = b[lpos - 1], rb = b[rpos];
        return l->LTE(lb + 1, rb, k) + \
         r->LTE(lpos - lb, rpos - rb, k);
    }
    //count of numbers in [l, r] equal to k
    int count(int lpos, int rpos, int k) {
        if (lpos > rpos || k < lo || k > hi) return 0;
        if (lo == hi) return rpos - lpos + 1;
        int lb = b[lpos - 1], rb = b[rpos];
        int mid = (lo + hi) >> 1;
        if (k <= mid) return l->count(lb + 1, rb, k);
        return r->count(lpos - lb, rpos - rb, k);
    }
    //sum of numbers in [l ,r] less than or equal to k
    long long sum(int lpos, int rpos, int k) {
        if (lpos > rpos || k < lo) return 0;
        if (hi <= k) return c[rpos] - c[lpos - 1];
        int lb = b[lpos - 1], rb = b[rpos];
        return l->sum(lb + 1, rb, k) + \
         r->sum(lpos - lb, rpos - rb, k);
    }

    ~wavelet_tree() {
        if (l) delete l;
        if (r) delete r;
        if (b) free(b);
        if (c) free(c);
    }
};
// Usage:
int a[n+1] = {0};
L(i, 1, n) cin >> a[i];
wavelet_tree wt;
wt.init(a+1, a+n+1, 1, MAXV); //beware! after the init() operation array a[] will not be same