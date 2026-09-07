template<class t>
auto pr(t x) -> decltype(cerr<<x, void()) {cerr<<x;}
void pr(string s) {cerr<<s;}
template<class t>
auto pr(t v) -> decltype(v.begin(), void());
template<class a, class b>
void pr(pair<a,b> p){
  cerr << "{";  pr(p.F);  cerr << ", ";  pr(p.S);  cerr << "}";
}
template<class...  a>
void pr(tuple<a...>  t){
    cerr << "(";
    apply( [&] (auto...  x) {
        ( ( pr(x), cerr << ", " ),  ...);
    },  t);
    cerr << ")";
}
template<class t>
auto pr(t v) -> decltype(v.begin(), void()){
    cerr << "[";   
    for(auto x : v){
        pr(x);  cerr << ", ";
    }
    cerr << "]";
}
template<class...  t>
void _deb(const  t&...  x){
    ( ( pr(x), cerr << ", " ),  ...);
    cerr << '\n';
}
#define deb(...) cerr << __LINE__ << "| [" << #__VA_ARGS__ << \
 "] = " ,  _deb(__VA_ARGS__)