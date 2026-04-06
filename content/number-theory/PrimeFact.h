/**
 * Author: idk
 * Date: 2015-06-23
 * License: CC0
 * Source: idk
 * Description: idk
 *
 * Time: idk
 * Status: idk
 */
#pragma once
const int N = 1e7;
vector<int> spf(N);
void prep(){ // modified sieve
    L(i, 2, N-1) {
        if(spf[i] == 0) {
            spf[i] = i;
            for(ll j = i * i; j <= N-1; j += i) {
                if(spf[j] == 0) spf[j] = i;    }}}}
// prime factorize [if you need 1e9, use loop upto sqrt]
vector<pll> prime_factorize(ll x) {
    vector<pll> ans;
    while(x!=1) {
        ll cur = spf[x];  ll cnt = 0;
        while(x%cur==0) cnt++, x/=cur;
        ans.push_back({cur, cnt});   }
    return ans;   }