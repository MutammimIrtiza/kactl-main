/**
 * Author: ...
 * License: ...
 * Source: ...
 * Description: the dnc sol for cses subarray squares
 * Time: k*n*log(n) here
 * Status: ...
 */
#pragma once
/*
	dnc dp can be applid for 
		dp[i] = min( dp[j] + cost(j+1..i) ) for all j<i
	if opt(i) <= opt(i-1) is satisfied
		where opt(i) = smallest j among all the best j for i
	this may or may not be obvious
    [if you cant prove, try bruteforcing too see if it holds]
	one (not only) case when this is true is: 
		cost function satisfies quadrangle inequality:
		cost(a..c) + cost(b..d) <= cost(a..d) + cost(b..c)
		where a <= b <= c <= d
	the cost function (pref[i]-pref[j])^2 satisfies this
	this runs in nlogn for each k. so k*nlogn total
*/
const int MXN = 3005, inf = 2e18;
ll pref[MXN], dp[MXN][MXN];//dp[i][k]=divide upto i int k segs
ll cost(int l, int r) { // change
    int sum = pref[r] - pref[l-1]; return sum*sum;
}
void dnc(int k, int l, int r, int optl, int optr) {
    if (l > r) return;
    int mid = (l + r) / 2;
    pair<int, int> best = {inf, l};
    for (int j = optl; j <= min(mid - 1, optr); j++) {
        best = min(best, make_pair(dp[j][k-1] + cost(j+1, mid), j));
    }
    dp[mid][k] = best.first;
    int opt = best.second;
    dnc(k, l, mid - 1, optl, opt);
    dnc(k, mid + 1, r, opt, optr);
}
usage:
dp[0][0] = 0;
for (int i = 1; i <= n; i++) dp[i][0] = inf;
for (int k = 1; k <= _K; k++) dnc(k, 1, n, 0, n - 1);
// [optl, optr] = possible values of j. starts with [0,n-1]