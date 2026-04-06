/**
 * Author: idk
 * Description: idk
 * Time: idk
 * Status: idk
 */

ll n,m,k,q;
ll a[N];
ll dp[][11][2][2]; // put max len of string + 1

bool is_valid(){ return 1; } // for even sum, return sum % 2 == 0;

ll cnt(string s,ll pos,ll prev,bool started,bool tight){
 if(pos==Size(s)) return is_valid(); // number of such numbers = 1
 if(dp[pos][prev][started][tight]!=-1) return dp[pos][prev][started][tight];
 ll ans=0;
 ll digMax=tight?s[pos]-'0':9;
 for(ll dig=0;dig<=digMax;dig++){
  // ***
  if(started and dig==prev) continue; // no repitition
  bool startedNext=started?1:dig!=0; // started || (dig != 0)
  bool tightNext=tight?(dig==digMax):0; // tight && (dig == digMax)
  ans+=cnt(s,pos+1,dig,startedNext,tightNext); }
 return dp[pos][prev][started][tight]=ans; }

// usage:
string s1 = to_string(n1 - 1); 
    memset(dp, -1, sizeof(dp));
    ll ans1; if(n1-1 < 0) ans1 = 0;
    // 10 is a dummy value for prev.
    else ans1 = cnt(s1, 0, 10, 0, 1);
    // similarly, find ans2, and output : ans2-ans1