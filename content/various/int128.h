/**
 * Author: idk
 * Description: idk
 * Time: idk
 * Status: idk
 */
using i128=__int128_t;
i128 read(){
 string s; cin>>s; bool neg=false; size_t i=0;
 if(s[0]=='-'){ neg=true; i=1; } i128 mag=0;
 for(;i<s.size();++i){ mag=mag*10+(unsigned)(s[i]-'0'); }
 return neg?-mag:mag; }
void print(i128 x){
 if(x==0){cout<<0<<nl;return;}
 bool neg=x<0; if(neg)x=-x;
 string s;while(x){ int d=(int)(x%10);
    s.push_back(char('0'+d)); x/=10; }
 if(neg)s.push_back('-'); reverse(s.begin(),s.end());
 cout<<s<<nl; }
bool cmp(i128 x,i128 y){ return x>y; } // for sorting