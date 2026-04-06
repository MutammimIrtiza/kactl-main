/**
 * Author: idk
 * Description: idk
 * Time: idk
 * Status: idk
 */
ll n,m,x,y,z,q,k,u,v,w;
vector<int> gr[N];
int sz[N];
int tot,done[N],cenpar[N];

void calc_sz(int node,int p){
 tot++; sz[node]=1;
 for(auto ch:gr[node]){
  if(ch==p||done[ch]) continue;
  calc_sz(ch,node); sz[node]+=sz[ch]; } }

int find_cen(int node,int p){ // find centroid
 for(auto ch:gr[node]){
  if(ch==p||done[ch]) continue;
  else if(sz[ch]>tot/2) return find_cen(ch,node); }
 return node; }

void decompose(int node,int p){ // find centroid of subtree
 tot=0; calc_sz(node,p);
 int cen=find_cen(node,p);
 cenpar[cen]=p; done[cen]=1;
 for(auto ch:gr[cen]){
  if(ch==p||done[ch]) continue;
  decompose(ch,cen); } }

vll cen_tree[N]; // centroid tree

int form_cen_tree(){ // form graph, return root(centroid)
 decompose(1,0); int root;
 L(i,1,n){
  if(cenpar[i]==0) root=i;
  if(cenpar[i]!=0){
   cen_tree[i].push_back(cenpar[i]);
   cen_tree[cenpar[i]].push_back(i); } }
 return root; }