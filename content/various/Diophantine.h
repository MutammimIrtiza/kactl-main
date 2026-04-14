/**
 * Author: ...
 * Description: ...
 * Time: ...
 * Status: ...
 */
// Extended Euclidean Algorithm
ll ext_gcd(ll a,ll b,ll& x,ll& y){
 if(b==0){ x=1,y=0; return a; }
 ll x1,y1,g=ext_gcd(b,a%b,x1,y1);
 x=y1; y=x1-(a/b)*y1; return g; }
 // Solve ax + by = c
// general solution : x + k*b/g, y - k*a/g
bool solve_diophantine(ll a,ll b,ll c,ll& x,ll& y,ll& g){
 g=ext_gcd(abs(a),abs(b),x,y);
 if(c%g!=0) return false;
 x*=c/g; y*=c/g;
 if(a<0)x=-x; if(b<0)y=-y; return true; }
 
bool solve_dioph_non_neg(ll a,ll b,ll c,ll& x,ll& y,ll& g){
 if(!solve_diophantine(a,b,c,x,y,g)) return false;
 ll dx=(b/g),dy=(a/g);
 if(x<0){
  ll k=(-x+abs(dx)-1)/abs(dx); // ceil
  if(dx<0)k=-k; x+=k*dx; y-=k*dy; }
 if(y<0){
  ll k=(-y+abs(dy)-1)/abs(dy);
  if(dy<0)k=-k; y+=k*dy; x-=k*dx; }
 return x>=0 and y>=0; }