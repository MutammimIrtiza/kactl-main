mt19937_64 \
 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(l, r) uniform_int_distribution<ll>(l, r)(rng)
// [l,r]