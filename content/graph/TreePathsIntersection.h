/**
 * Author: 
 * Date: 
 * Source: 
 * Description: Find intersecting path between two paths a..b and c..d
 */
// returns {-1,-1} if empty
pair<int,int> intersect(int a, int b, int c, int d) {   
    int cand[4] = { lca(a,c), lca(a,d), lca(b,c), lca(b,d) };
    sort(cand, cand+4, [&](int x, int y) {
        return dep[x]>dep[y];
    } );
    int u = cand[0], v = cand[1];
    if (dep[u] < max(dep[lca(a,b)], dep[lca(c,d)])) 
        return {-1, -1};
    return {u, v};
}