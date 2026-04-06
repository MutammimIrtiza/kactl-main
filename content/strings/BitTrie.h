/**
 * Author: idk
 * Description: idk
 * Time: idk
 * Status: idk
 */

struct BitTrie{
 struct Node{
    int child[2],cnt;//trie[0]=total numbers inserted in trie
    Node(){ child[0] = child[1] = -1;  cnt=0; } 
  };
 vector<Node> trie;
 int BITS;

 BitTrie(int maxBits = 30){ // 30 for numbers up to 1e9
  BITS = maxBits;  trie.push_back(Node()); // root
} 

 void insert(int x){
  int node=0;
  trie[node].cnt++;
  for(int b=BITS;  b>=0;  b--){
   int bit = (x>>b)&1;
   if(trie[node].child[bit] == -1){
    trie[node].child[bit] = trie.size(); 
    trie.push_back(Node()); 
   }
   node = trie[node].child[bit];  trie[node].cnt++; 
   } 
 }

 void erase(int x){
  int node=0;
  trie[node].cnt--;
  for(int b=BITS;  b>=0;  b--){
   int bit = (x>>b)&1;
   int nxt=trie[node].child[bit];
   node=nxt; trie[node].cnt--; 
  } 
 }

 ll max_xor(ll x){ // find y from this trie that maximizes x^y
  if(trie[0].cnt == 0) return 0; // empty trie
  ll cur=0, y=0;
  R(bit, BITS, 0){
   int nextbit = getBit(x,bit); // at root, nextbit=30
   if(trie[cur].child[!nextbit] != -1
    and trie[trie[cur].child[!nextbit]].cnt){
    cur = trie[cur].child[!nextbit];
    if(!nextbit) y = setbit(y,bit); 
  }
   else{ // has to exist, since tire is not empty
    cur = trie[cur].child[nextbit];
    if(nextbit) y = setbit(y,bit); 
   } 
  }
  return x^y; 
 }
};