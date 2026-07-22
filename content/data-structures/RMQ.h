/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
#pragma once
template<class T>
struct RMQ {
    const vector<T>& V;
    vector<vector<int>> jmp;
    RMQ(const vector<T>& V) : V(V), jmp(1, vector<int>(sz(V))) {
        rep(i,0,sz(V)) jmp[0][i] = i;
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j,0,sz(jmp[k])) {
                int a = jmp[k - 1][j];
                int b = jmp[k - 1][j + pw];
                jmp[k][j] = (V[a] <= V[b] ? a : b);
            }
        }
    }
    int queryIdx(int a, int b) { // leftmost for tie breaking
        assert(a < b);
        int dep = 31 - __builtin_clz(b - a);
        int i = jmp[dep][a];
        int j = jmp[dep][b - (1 << dep)];
        return (V[i] <= V[j] ? i : j); // use < for rightmost
    }
    T query(int a, int b) {
        return V[queryIdx(a, b)];
    }
};