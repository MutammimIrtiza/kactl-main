/**
 * Author:
 * Date: 
 * Description:
 */
#pragma once

vvll gr(N), revgr(N);
vector<bool> vis(N);
stack<ll> st;
void dfs1(ll node) {
    vis[node] = 1;
    for(ll ch : gr[node]) { if(!vis[ch]) dfs1(ch); }
    st.push(node);
}
void dfs2(ll node, vll &comp) {
    vis[node] = 1; comp.push_back(node);
    for(ll ch : revgr[node]) { if(!vis[ch]) dfs2(ch, comp); }
}
vvll kosaraju() {  // returns comps in topological order
    vvll comps;
    L(i, 1, n) if(!vis[i]) dfs1(i);
    L(i, 1, n) vis[i] = 0;
    while(st.size()) {
        ll now = st.top(); st.pop();
        if(!vis[now]) { 
            vll comp; dfs2(now, comp); comps.push_back(comp);
        }
    } return comps;
}