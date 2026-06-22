/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: gemini
 * Description: ...
 */
ll floor_div(ll a, ll b) {
    ll res = a / b;
    ll rem = a % b;
    if (rem != 0 && ((a < 0) ^ (b < 0))) res--;
    return res;
}
ll ceil_div(ll a, ll b) {
    ll res = a / b;
    ll rem = a % b;
    if (rem != 0 && !((a < 0) ^ (b < 0))) res++;
    return res;
}
// Non-negative solution (x >= 0, y >= 0)
bool dioph_nonneg(ll a, ll b, ll c, ll &x, ll &y, ll &g) {
    if (!diophantine(a, b, c, x, y, g)) return false;

    if (a == 0) {
        if (b == 0) return c == 0;
        if (y >= 0) { x = 0; return true; }
        return false;
    }
    if (b == 0) {
        if (x >= 0) { y = 0; return true; }
        return false;
    }

    ll dx = b / g;
    ll dy = a / g;

    ll k_min = -INF;
    ll k_max = INF;

    // x + k*dx >= 0  =>  k*dx >= -x
    if (dx > 0) {
        k_min = max(k_min, ceil_div(-x, dx));
    } else if (dx < 0) {
        k_max = min(k_max, floor_div(-x, dx));
    } else if (-x > 0) { 
        return false;
    }

    // y - k*dy >= 0  =>  k*dy <= y
    if (dy > 0) {
        k_max = min(k_max, floor_div(y, dy));
    } else if (dy < 0) {
        k_min = max(k_min, ceil_div(y, dy));
    } else if (y < 0) { 
        return false;
    }

    if (k_min > k_max) return false;

    // Any k in [k_min, k_max] gives a non-negative solution.
    // k_min minimizes x (if dx > 0) or maximizes x (if dx < 0)
    ll k = k_min;
    x += k * dx;
    y -= k * dy;

    return true;
}