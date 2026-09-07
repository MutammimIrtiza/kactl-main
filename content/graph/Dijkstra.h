/**
 * Author:
 * Date: 
 * Description:
 */
vector<ll> dijkstra(ll start, vector<vector<array<ll, 2>>> &gr, int n) {
    vector<ll> d(n + 1, inf); 
    d[start] = 0; 

    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<array<ll, 2>>> pq; 
    pq.push({0LL, start});

    while (!pq.empty()) {
        auto [dist, node] = pq.top(); 
        pq.pop();

        if (dist > d[node]) continue;

        for (auto [nextNode, weight] : gr[node]) {
            if (weight + dist < d[nextNode]) {
                d[nextNode] = weight + dist;
                pq.push({d[nextNode], nextNode});
            }
        }
    }
    return d;
}