/**
 * Author: ...
 * Description: ...
 * Time: ...
 * Status: ...
 */
vector<ll> dijkstra(ll start, vector<vector<array<ll, 2>>> &gr, int n){
    vector<ll> d(n); For(i, 1, n) d[i] = inf; d[start] = 0;   
    bool vis[n+1] = {0};
    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<array<ll, 2>>> pq; 
    pq.push({0LL, start});
    while(!pq.empty()){
        auto [dist, node] = pq.top(); pq.pop();
        if(vis[node]) continue; 
        vis[node] = 1;
        for(auto [nextNode, weight] : gr[node]){
            if(weight + dist < d[nextNode]){
                d[nextNode] = weight + dist;
                pq.push({d[nextNode], nextNode}); }}}
    return d;
}