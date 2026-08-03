/**
 * Author:
 * Date: 
 * Description:
 */
vector<ar<ll, 2>> gr[N];
vector<bool> vis_edge(N);
vll ans;
void dfs(ll node) {
    while(!gr[node].empty()) {
        auto [ch, ed] = gr[node].back(); gr[node].pop_back();
        if(vis_edge[ed]) continue;
        vis_edge[ed] = 1;
        dfs(ch);
    }
    ans.push_back(node);
}
main:
L(i, 1, m) {
    cin >> u >> v;
    gr[u].push_back({v, i}); gr[v].push_back({u, i});
    deg[u]++, deg[v]++;       
}
L(i, 1, n) if(deg[i]&1) {cout << "IMPOSSIBLE" << nl; return;}
dfs(1);
if(sz(ans)!=m+1) {cout << "IMPOSSIBLE" << nl; return;}
for(ll x : ans) cout << x << gp;