#include<bits/stdc++.h>
using namespace std;
// *st.find_by_order(index) = value at index
// st.order_of_key(x) = no. of elements strictly less than x
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, \
 rb_tree_tag,tree_order_statistics_node_update>
#define all(v) v.begin(),v.end()
#define range(v, i, j) v.begin()+i, v.begin()+j+1
#define rep(i, a, b) for(ll i = (a); i < (b); ++(i))
#define sz(x) (ll)(x.size())
#define gp " "
#define nl "\n"
#define isSet(x, i) ((x>>i)&1)
#define setbit(x, i) (x | (1LL<<i))
#define resetbit(x, i) (x & (~(1LL << i)))
#define toggleBit(x, i) ((x) ^ (1LL << (i)))
#define clz(x) __builtin_clzll(x)
#define ctz(x) __builtin_ctzll(x)
#define csb(x) __builtin_popcountll(x)
#define msb(x) ((x) ? (63 - __builtin_clzll((ll)(x))) : -1)
#define lsb(x) ((x) ? (__builtin_ctzll((ll)(x))) : -1)

#ifdef LOCAL
#include "debug.h"
#else
#define deb(...)
#endif
void solve(int tcase){}
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1;
    // cin >> t;
    L(i,1,t) solve(i);
}