/**
 * Author: 
 * Description: 
 * Time: 
 */
#pragma once

struct DSU {
    vector<int> p, _sz;
    DSU(int n) {
        p.resize(n); _sz.assign(n, 1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int i) {
        if (p[i] == i) return i;
        return p[i] = find(p[i]); // Path compress
    }
    bool join(int i, int j) {
        int pi = find(i); int pj = find(j);
        if (pi == pj) return false;
        if (_sz[pi] < _sz[pj]) swap(pi, pj);
        p[pj] = pi;  _sz[pi] += _sz[pj];
        return true;
    }
};