/*
  2011/1/21
  极大权闭合图 
*/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<iterator>

using namespace std;

const double oo=1e+10;
const int Max_M=1005;
const int Max_N=105;

struct node{
  int to,pair;
  double cap;
  node(int _to,double _cap,int _pair):to(_to),cap(_cap),pair(_pair){};
};

bool found,chk[Max_N];
vector<node> g[Max_N];
int d[Max_N],v[Max_N],dv[Max_N],x[Max_M],y[Max_M],ans[Max_N];
double flow,aug;
int N,M,S,T,tot,sum;

void mke(int a,int b,double c,double d,int pos_a,int pos_b){
  g[a].push_back(node(b,c,pos_b));g[b].push_back(node(a,d,pos_a));
}

void augment(int now){
  double tmp=aug; int min_d=tot-1;
  vector<node>::iterator iter;
  if(now==T){
    found=true;     
    flow+=aug;
    return;
  }
  for(iter=g[now].begin();iter!=g[now].end();++iter){
    if(iter->cap>0){
      if(d[now]==d[iter->to]+1){  
        if(iter->cap<aug) aug=iter->cap;  
        augment(iter->to);                       
        if(d[S]>=tot) return;
        if(found) break;
        aug=tmp;
      }
      if(d[iter->to]<min_d) min_d=d[iter->to]; 
    }
  }
  if(found){
    iter->cap-=aug;
    g[iter->to][iter->pair].cap+=aug;
  }
  else{
    if(--v[d[now]]==0) d[S]=tot;
    d[now]=min_d+1;
    v[d[now]]++;
  }
}

double sap(double r){
  
  S=0;T=N+1;tot=N+2;
  memset(d,0,sizeof(d));
  memset(v,0,sizeof(v));
  v[0]=tot;
  flow=0;
  
  for(int i=S;i<=T;++i)
    g[i].clear();
  for(int i=1;i<=M;++i)
    mke(x[i],y[i],1,1,g[x[i]].size(),g[y[i]].size());
  for(int i=1;i<=N;++i){
    mke(S,i,M,0,g[S].size(),g[i].size());
    mke(i,T,M+2*r-dv[i],0,g[i].size(),g[T].size());
  }

  while(d[S]<tot){
    aug=oo;    
    found=false;
    augment(S);            
  }
  
  return flow;
  
}

void dfs(int now){
  chk[now]=true;
  if(now!=S) ans[sum++]=now;
  for(int i=0;i<g[now].size();++i)
    if(chk[g[now][i].to]==false&&g[now][i].cap>0) dfs(g[now][i].to);
}

void solve(){
  
  double lef,rig,mid,tmp,eps=1.0/N/N;
  if(M==0){
    printf("1\n1\n");
    return;
  }
  lef=0;
  rig=M;
  
  while(rig-lef>=eps){
    mid=(lef+rig)/2;
    tmp=M*N-sap(mid);
    if(tmp>1e-8)
      lef=mid;
        else rig=mid;
  }
  
  sap(lef);
  sum=0;
  memset(chk,false,sizeof(chk));
  dfs(S);
  sort(ans,ans+sum);
  printf("%d\n",sum);
  for(int i=0;i<sum;++i)
    printf("%d\n",ans[i]);

}  

int main(){
  
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  scanf("%d%d",&N,&M);
  memset(dv,0,sizeof(dv));
  for(int i=1;i<=M;++i){
    scanf("%d%d",x+i,y+i);
    dv[x[i]]++;dv[y[i]]++;
  }
  
  solve();
  
  return 0;

}
