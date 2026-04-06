/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * Initialize with AhoCorasick ac(patterns); the automaton start node will be at index 0.
 * find(word) returns for each position the index of the longest word that ends there, or -1 if none.
 * findAll($-$, word) finds all words (up to $N \sqrt N$ many if no duplicate patterns)
 * that start at each position (shortest first).
 * Duplicate patterns are allowed; empty patterns are not.
 * To find the longest words that start at each position, reverse all input.
 * For large alphabets, split each symbol into chunks, with sentinel bits for symbol boundaries.
 * Time: construction takes $O(26N)$, where $N =$ sum of length of patterns.
 * find(x) is $O(N)$, where N = length of x. findAll is $O(NM)$.
 * Status: stress-tested
 */
#pragma once

struct Aho{
 static const int K=26; // alphabet size
 struct Vertex{
    int next[K],link,term_link; // suffix link, terminal link
    bool output; // true if this node is end of some pattern
    vector<int> ids; // pattern ids ending here
    int len;
    Vertex(){
      fill(begin(next), end(next), -1);
      link=-1;  term_link=-1;  output=false;  len=0; 
    } 
  };
 vector<Vertex> t = {Vertex()}; // root = state 0

 void add_string(const string& s,int id){
  int v=0;
  for(char ch:s){
   int c=ch-'a';
   if(t[v].next[c] == -1){
     t[v].next[c] = t.size();  t.emplace_back(); 
   }
   v=t[v].next[c]; 
  }
  t[v].output=true; t[v].ids.push_back(id); 
 }

 void build_automaton(){ // build the automaton T.T
  queue<int> q;
  t[0].link=0;  t[0].term_link=0;
  for(int c=0;  c<K;  c++){
   int u=t[0].next[c];
   if(u!=-1){ t[u].link=0; q.push(u); t[u].len=1; }
   else t[0].next[c]=0;// missing edge from root loops to root
  } 
  while(!q.empty()){
   int v=q.front(); q.pop();
   for(int c=0;  c<K;  c++){
    int u=t[v].next[c];
    if(u!=-1){ // compute suffix link
     t[u].link = t[t[v].link].next[c];
     t[u].len = t[v].len+1; 
     q.push(u); 
    }
    else t[v].next[c] = t[t[v].link].next[c]; 
  }
   // compute terminal link
   if(t[t[v].link].output) t[v].term_link = t[v].link;
   else t[v].term_link = t[t[v].link].term_link; 
  } 
 }

 void form_tree(){
    gr.resize(t.size());
    L(state,1,t.size()-1){
     gr[t[state].term_link].push_back(state); 
    } 
  }
};