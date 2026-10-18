#include "euclid.h"
struct mint{
 ll x; mint() { x=0; }
 mint(ll xx) {x = xx%mod; if(x<0)x+=mod; }
 mint& operator+=(mint b){ x=(x + b.x)%mod; return *this; }
 mint& operator*=(mint b){ x=(x * b.x)%mod; return *this; }
 mint& operator-=(mint b){ x=(x - b.x +mod)%mod; return *this;}
 mint& operator/=(mint b){ return *this *= b.inv(); }
 friend mint operator+(mint a,mint b){ return a+=b; }
 friend mint operator-(mint a,mint b){ return a-=b; }
 friend mint operator*(mint a,mint b){ return a*=b; }
 friend mint operator/(mint a,mint b){ return a/=b; }
 mint operator-() { return mint()-*this; }
 mint inv() { return power(mod-2); } // prime mod
//  mint inv() { // any mod
// 		ll x, y, g = euclid(a.x, mod, x, y);
// 		assert(g == 1); return mint((x + mod) % mod);
//  }
 mint power(ll n) {
	mint a=*this,  res=1;
	while(n) { if(n&1)res*=a;  a*=a;  n>>=1;}
	return res; 
 }
  friend ostream& operator<<(ostream& os, const mint& m) \
   { return os << m.x; }
};

const int N=2000005; mint fact[N],inv_fact[N];
mint power(mint a,ll n){ return a.power(n); }
void prep_factorials(){
 fact[0] = 1;
 for(int i=1; i<N; ++i) fact[i] = fact[i-1] * i;
 inv_fact[N-1] = fact[N-1].inv();
 for(int i=N-2; i>=0; --i) inv_fact[i] = inv_fact[i+1]*(i+1);
}
// for big n and small r, use loop instead
mint ncr(int n,int r){ // limitation : small n
 if(r<0 || r>n) return mint();
 return fact[n] * inv_fact[r] * inv_fact[n-r]; 
}
mint ncr_lucas(int n, int r) { // limitation : small mod
    if (r < 0 || r > n) return 0;
    mint res(1);
    while (n > 0 || r > 0) {
        int ni = n % mod, ri = r % mod;
        if (ri > ni) return 0;
        res *= ncr(ni, ri);
        n /= mod; r /= mod;
    }
    return res;
}