/**
 * Author: Simon Lindholm + Gemini
 * Date: 2026-08-10
 * Description: Solves $Ax = b$ over $\mathbb F_2$. If there are multiple solutions, one is returned arbitrarily. If $b=0$, returns non-zero solution if it exists (rank < m).
 *  Returns rank, or -1 if no solutions. Destroys $A$ and $b$.
 * Time: O(n^2 m)
 * Status: bruteforce-tested for n, m <= 4
 */
#pragma once

typedef bitset<1500> bs; // max. no. of variables
int solveLinear(vector<bs>& A, vi& b, bs& x, int m) {
	int n = sz(A), rank = 0, br;
	assert(m <= sz(x));
	vi col(m); iota(all(col), 0);
	rep(i,0,n) {
		for (br=i; br<n; ++br) if (A[br].any()) break;
		if (br == n) {
			rep(j,i,n) if(b[j]) return -1;
			break;
		}
		int bc = (int)A[br]._Find_next(i-1);
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) if (A[j][i] != A[j][bc]) {
			A[j].flip(i); A[j].flip(bc);
		}
		rep(j,i+1,n) if (A[j][i]) {
			b[j] ^= b[i];
			A[j] ^= A[i];
		}
		rank++;
	}
	x = bs();
    if (rank < m) x[col[rank]] = 1; 
    for (int i = rank - 1; i >= 0; --i) {
        int v = b[i]; 
        for(int j = i+1; j<m; ++j) v ^= (A[i][j] & x[col[j]]);
        x[col[i]] = v;
    }
    return rank;
}
