/**
 * Author: idk
 * Description: idk
 * Time: idk
 * Status: idk
 */

struct SAM{
 struct State{
  int link, maxlen;
  map<char,int> next;
  State(){ link=-1; maxlen=0; } 
 };

 vector<State> st;
 vector<vector<int>> gr;
 vector<ll> koybar;
 vector<bool> was_terminal;
 int last,sz;
 ll total; // number of unique substrings

 SAM(int n){
  st.resize(2*n);  gr.resize(2*n);  koybar.resize(2*n); was_terminal.resize(2*n);
  st[0]=State();  sz=1;  last=0;  total=0; 
 }

 void extend(char c){
  int cur = sz++;
  st[cur].maxlen = st[last].maxlen+1;
  int p=last;
  while(p!=-1 && !st[p].next.count(c)){
   st[p].next[c]=cur;  p=st[p].link; 
  }
  if(p == -1){ st[cur].link=0; }
  else{
   int q = st[p].next[c];
   if(st[p].maxlen+1 == st[q].maxlen){ st[cur].link=q; }
   else{
      int clone=sz++;
      st[clone] = st[q];
      st[clone].maxlen = st[p].maxlen + 1;
      while(p!=-1 && st[p].next[c] == q){
        st[p].next[c]=clone;  p=st[p].link; 
      }
      st[q].link = st[cur].link = clone; 
    } 
  }
    last=cur; was_terminal[last]=true;
    total+=st[cur].maxlen-st[st[cur].link].maxlen; 
 }

 void build_tree(){ // USE (sam.sz-1) when you need to visit all states
  L(i,1,sz-1) gr[st[i].link].push_back(i); 
 }

 void guno(){ // count repetitions in the string for each node
  int cur=last;
  L(i,1,sz-1) koybar[i] = was_terminal[i];
  function<void(int)> dfs=[&](int node){
   for(int ch:gr[node])
      { dfs(ch); koybar[node] += koybar[ch]; } 
  };
  dfs(0); 
 }

 ll koyta(int i){ return st[i].maxlen-st[st[i].link].maxlen; }

 // after adding the entire string, if you need terminal states:
 // start from last, go back by suffix links. all visited states are terminal states
};