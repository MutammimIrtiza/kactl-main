/**
 * Author:
 * Date: 
 * Description:
 */
// cost[u][v] = edge weight, INF if no edge
// O(n^2 * 2^n)
ll tsp(vector<vector<ll>>& cost) {
    int n = cost.size();
    vector dp(1 << n, vector<ll>(n, inf));
    dp[1][0] = 0; // start at 0

    for (int mask = 0; mask < (1 << n); mask++) {
        if (!(mask & 1)) continue;

        for (int u = 0; u < n; u++) {
            if (dp[mask][u] == inf) continue;

            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                if (cost[u][v] == inf) continue;
                dp[mask | (1 << v)][v] =
                    min(dp[mask | (1 << v)][v],
                        dp[mask][u] + cost[u][v]);
            }
        }
    }
    ll ans = inf;
    int full = (1 << n) - 1;
    for (int u = 0; u < n; u++) {
        if (cost[u][0] == inf) continue;
        ans = min(ans, dp[full][u] + cost[u][0]);
    }
    return ans;
}