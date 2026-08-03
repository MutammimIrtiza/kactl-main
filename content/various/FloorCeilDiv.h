/**
 * Author:
 * Date: 
 * Description:
 */
ll floor_div(ll a, ll b) {
    if (b < 0) a = -a, b = -b;
    if (a >= 0) return a / b;
    return (a - b + 1) / b;
}
ll ceil_div(ll a, ll b) {
    if (b < 0) a = -a, b = -b;
    if (a >= 0) return (a + b - 1) / b;
    return a / b;
}