/**
 * Author:
 * Date: 
 * Description:
 */
struct XorBasis {
    static const int B = 60;     // for 64-bit numbers
    long long b[B];  int sz;
    XorBasis() {
        memset(b, 0, sizeof b);  sz = 0;
    }
    // Insert number into basis
    void insert(long long x) {
        for (int i = B-1; i >= 0; i--) {
            if (!(x >> i & 1)) continue;
            if (b[i]) x ^= b[i];        // eliminate bit
            else {                      // new basis vector
                b[i] = x;  sz++;  return;
            }}}
    // Check if some subset has xor = x
    bool can(long long x) {
        for(int i = B-1; i>=0; i--) x = min(x, x ^ b[i]);
        return x == 0;
    }
    // Maximum possible xor with optional start value
    long long max_xor(long long x = 0) {
        for(int i = B-1; i>=0; i--) x = max(x, x ^ b[i]);
        return x;
    }
    // k-th smallest subset xor (1-indexed, 1st = 0)
    long long kth(long long k) {
        if (k < 1 || k > (1LL << sz)) return -1;
        long long x = 0, cnt = 1LL << sz;
        for (int i = B-1; i >= 0; i--) if (b[i]) {
            if (k > cnt/2) {
                if (!(x >> i & 1)) x ^= b[i];  k -= cnt/2;
            } else {
                if (x >> i & 1) x ^= b[i];
            }
            cnt /= 2;
        }
        return x;
    }
    // Count how many subset xors are < x
    long long count_lt(long long x) {
        if (x < 0) return 0;
        long long ans = 0, cnt = 1LL << sz;
        long long mask = 0;
        for (int i = B-1; i >= 0; i--) {
            if (b[i]) {
                if (x >> i & 1) {
                    ans += cnt/2;
                    if (!(mask >> i & 1)) mask ^= b[i];
                } else if (mask >> i & 1) {
                    mask ^= b[i];
                }
                cnt /= 2;
            }
            else if ((x >> i & 1) != (mask >> i & 1)) {
                return (x >> i & 1) ? ans + cnt : ans;
            }
        }
        return ans;
    }};