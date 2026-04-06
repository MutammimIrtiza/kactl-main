mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
inline ll rnd(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}