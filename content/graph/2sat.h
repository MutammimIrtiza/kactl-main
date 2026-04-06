/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem,
 * so that an expression of the type $(a||b)\&\&(!a||c)\&\&(d||!b)\&\&...$
 * becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.either(0, \tilde3); // Var 0 is true or var 3 is false
 *  ts.setValue(2); // Var 2 is true
 *  ts.atMostOne({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
 *  ts.solve(); // Returns true iff it is solvable
 *  ts.values[0..N-1] holds the assigned values to the vars
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 * Status: stress-tested
 */
#pragma once
// variables are zero indexed
struct twosat{
 int n;
 vector<vector<int>> g,gt;
 vector<bool> vis,res;
 vector<int> comp;
 stack<int> ts;
 twosat(int vars=0){
  n=vars<<1; g.resize(n); gt.resize(n); }

 //if you want to force variable a to be true : addOR (a,1,a,1);
 //if you want to force variable a to be false : addOR (a,0,a,0);

 // adds an implication
 void _add(int a,bool sign_a,int b,bool sign_b){
  a+=a+(sign_a^1);
  b+=b+(sign_b^1);
  g[a].push_back(b); gt[b].push_back(a); }

 //(x_a or (not x_b))-> sign_a=1,sign_b=0
 void addOR(int a,bool sign_a,int b,bool sign_b){
  a+=a+(sign_a^1);
  b+=b+(sign_b^1);
  g[a^1].push_back(b); // !a => b
  g[b^1].push_back(a); // !b => a
  gt[b].push_back(a^1);
  gt[a].push_back(b^1); }

 //(!x_a xor !x_b)-> sign_a=0, sign_b=0
 void addXOR(int a,bool sign_a,int b,bool sign_b){
  addOR(a,sign_a,b,sign_b);
  addOR(a,!sign_a,b,!sign_b); }

 void dfs1(int u){
  vis[u]=true;
  for(int v:g[u]) if(!vis[v]) dfs1(v);
  ts.push(u); }

 void dfs2(int u,int c){
  comp[u]=c;
  for(int v:gt[u]) if(comp[v]==-1) dfs2(v,c); }

 bool run(){ // returns true if possible, else false
  vis.resize(n,false);
  for(int i=0;i<n;++i) if(!vis[i]) dfs1(i);
  int scc=0;
  comp.resize(n,-1);
  while(!ts.empty()){
   int u=ts.top(); ts.pop();
   if(comp[u]==-1) dfs2(u,scc++); }
  res.resize(n/2);
  for(int i=0;i<n;i+=2){
   if(comp[i]==comp[i+1]) return false;
   res[i/2]=(comp[i]>comp[i+1]); }
  return true; }
};