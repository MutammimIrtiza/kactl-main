/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If
 * you just need gcd, use the built in \texttt{\_\_gcd} instead.
 * If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 */
#pragma once
// Extended Euclid
ll euclid(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1, g = euclid(b, a % b, x1, y1);
    x = y1; y = x1 - (a / b) * y1;
    return g;
}