/**
 * Author: idk
 * Description: idk
 * Time: idk
 * Status: idk
 */

struct Trie{
 static const int ALPHABET=26;
 static const char BASE='a';
 struct Node{
  int next[ALPHABET];
  int ends_here_cnt,count; // passes this node
  Node(){
   fill(next,next+ALPHABET,-1);
   ends_here_cnt=0; count=0; 
  } 
 };
 vector<Node> nodes;
 Trie(){ nodes.emplace_back(); } // root node

 void insert(const string& s){
  int cur=0;
  for(char ch:s){
   int c = ch-BASE;
   if(nodes[cur].next[c] == -1){
    nodes[cur].next[c]=nodes.size(); nodes.emplace_back();
   }
   cur = nodes[cur].next[c];  nodes[cur].count++; 
  }
  nodes[cur].ends_here_cnt++; 
 }

 bool erase(const string& s){
  if(!search(s)) return false;
  int cur=0;
  for(char ch:s){
   int c=ch-BASE;
   cur=nodes[cur].next[c];  nodes[cur].count--; 
  }
  nodes[cur].ends_here_cnt--; 
  return true; 
 }

 bool search(const string& s)const{
  int cur=0;
  for(char ch:s){
   int c=ch-BASE;
   if(nodes[cur].next[c]==-1
      || nodes[nodes[cur].next[c]].count==0) return false;
   cur=nodes[cur].next[c]; 
  }
  return nodes[cur].ends_here_cnt>0; 
}

 bool starts_with(const string& prefix)const{
  int cur=0;
  for(char ch:prefix){
   int c=ch-BASE;
   if(nodes[cur].next[c]==-1
     ||nodes[nodes[cur].next[c]].count==0) return false;
   cur=nodes[cur].next[c]; 
  }
  return true; 
 }

 int count_prefix(const string& prefix)const{
  int cur=0;
  for(char ch:prefix){
   int c=ch-BASE;
   if(nodes[cur].next[c]==-1
     ||nodes[nodes[cur].next[c]].count==0) return 0;
   cur=nodes[cur].next[c]; 
  }
  return nodes[cur].count; 
 }
};