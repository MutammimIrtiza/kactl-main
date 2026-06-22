/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: gemini
 * Description: ...
 */
const ll INF = 2e18; 

// Solve ax + by = c
bool diophantine(ll a, ll b, ll c, ll &x, ll &y, ll &g) {
    if (a == 0 && b == 0) {
        if (c == 0) { x = 0; y = 0; g = 0; return true; }
        return false;
    }
    g = euclid(abs(a), abs(b), x, y);
    if (c % g != 0) return false;

    if (a < 0) x = -x;
    if (b < 0) y = -y;

    x *= (c / g);
    y *= (c / g);

    return true;
}