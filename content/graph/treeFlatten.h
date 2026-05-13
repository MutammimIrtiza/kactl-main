/**
 * Author: ...
 * Description: Subtree of a node is [ in[node]...out[node] ]
 * The node itself is [ in[node]...in[node] ]
 * Time: ...
 * Status: ...
 */
vll in(N), out(N);   ll timer = -1;
void euler_tour(ll node, ll par) {
    in[node] = ++timer;
    for(ll ch : gr[node]) {
        if(ch == par) continue;
        euler_tour(ch, node);
    }
    out[node] = timer;
}   
//  usage :
    euler_tour(1, 0);
    vll flat_tree(n);
    L(i, 1, n) flat_tree[in[i]] = a[i];
    sumSeg seg(flat_tree);