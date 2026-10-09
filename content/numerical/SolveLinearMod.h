/**
 * Author: Claude
 * Date:
 * Description: Solves A*x = b mod p (p prime). Input a is the augmented
 *  matrix [A | b] with entries in [0, mod). Returns rank, or -1 if no
 *  solution. If multiple solutions, one arbitrary solution is returned.
 * If $b=0$, returns non-zero solution if it exists (rank < m).
 * Time: O(n^2 m)
 */
#pragma once
// requires: const int mod (prime); int power(int, int)
int Gauss(vector<vector<int>> a, vector<int>& ans) {
  int n = a.size();
  if (n == 0) { ans.clear(); return 0; }
  int m = (int)a[0].size() - 1;
  const ll MODSQ = (ll)mod * mod;
  vector<int> pos(m, -1);
  int rank = 0;

  for (int col = 0, row = 0; col < m && row < n; col++) {
    int mx = -1;
    rep(k,row,n) if(a[k][col]) {mx = k; break;}
    if (mx == -1) continue;
    swap(a[mx], a[row]);
    pos[col] = row;
    int inv = power(a[row][col], mod - 2);
    rep(i,0,n) {
      if (i != row && a[i][col]) {
        ll x = (ll)a[i][col] * inv % mod;
        for (int j = col; j <= m; j++)
          a[i][j] = (MODSQ + a[i][j] - a[row][j] * x) % mod;
      }
    }
    row++; rank++;
  }

  rep(i,rank,n) if (a[i][m]) return -1;      // inconsistent

  ans.assign(m, 0);
  int f = -1;
  rep(i,0,m) if(pos[i] == -1) {f=i; break;}
  if (f != -1) ans[f] = 1;            // first free var = 1 (nonzero if rank < m)

  rep(i,0,m) {
    if (pos[i] == -1) continue;
    long long v = a[pos[i]][m];
    if (f != -1) v = (v - 1LL * a[pos[i]][f] * ans[f]) % mod;
    v = (v + mod) % mod;
    ans[i] = v * power(a[pos[i]][i], mod - 2) % mod;
  }
  return rank;
}