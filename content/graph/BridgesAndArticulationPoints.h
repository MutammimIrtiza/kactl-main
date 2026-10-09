/**
 * Author:
 * Date: 
 * Description:
 */
struct BridgesAndArtPoint{
 int n,timer=0;
 vector<vector<int>> g;
 vector<int> tin,low;
 vector<char> vis,isArtPoint;
 vector<pair<int,int>> bridges;
 BridgesAndArtPoint(int n=0) : n(n), g(n), tin(n,-1),
  low(n,-1), vis(n,0), isArtPoint(n,0){}

void addEdge(int u,int v){g[u].push_back(v);g[v].push_back(u);}
 void run(){
  timer=0;
  fill(tin.begin(),tin.end(),-1);
  fill(low.begin(),low.end(),-1);
  fill(vis.begin(),vis.end(),0);
  fill(isArtPoint.begin(),isArtPoint.end(),0);
  bridges.clear();
  for(int v=0;v<n;++v) if(!vis[v]) dfs(v,-1); 
}
private:
 void dfs(int v,int p){
  vis[v]=1;
  tin[v]=low[v]=timer++;
  int children=0;
  for(int to:g[v]){
   if(to==p) continue;
   if(vis[to]){ low[v]=min(low[v],tin[to]); }
   else{
    ++children; dfs(to,v);
    low[v]=min(low[v],low[to]);
    if(low[to]>tin[v]) bridges.emplace_back(min(v,to),max(v,to));
    if(p!=-1&&low[to]>=tin[v]) isArtPoint[v]=1; 
    } 
  }
  if(p==-1&&children>1) isArtPoint[v]=1; 
}
};