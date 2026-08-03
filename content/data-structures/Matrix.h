/**
 * Author:
 * Date: 
 * Description:
 */
#pragma once
template<class T> struct Matrix {
    typedef Matrix M;
    int n;
    vector<vector<T>> d;
    Matrix(int _n = 0) : n(_n), d(_n, vector<T>(_n, 0)) {}
    static M identity(int n) {
        M I(n);
        rep(i,0,n) I.d[i][i] = 1;
        return I;
    }
    M operator*(const M& m) const {
        M a(n);
        rep(i,0,n) rep(j,0,n)
            rep(k,0,n) {
                a.d[i][k] = (a.d[i][k] + d[i][j] * m.d[j][k]) % mod;
            }
        return a;
    }
    vector<T> operator*(const vector<T>& vec) const {
        vector<T> ret(n, 0);
        rep(i,0,n) rep(j,0,n) {
            ret[i] = (ret[i] + d[i][j] * vec[j]) % mod;
        }
        return ret;
    }
    M operator^(ll p) const {
        assert(p >= 0);
        M a = identity(n), b(*this);
        while (p) {
            if (p & 1) a = a * b;
            b = b * b;
            p >>= 1;
        }
        return a;
    }
};