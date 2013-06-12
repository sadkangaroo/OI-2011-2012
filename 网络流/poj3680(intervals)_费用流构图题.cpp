/*
  2011/1/23
  最小费用最大流 
  构图题 
*/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

const int oo=0x7fffffff,NEG=-oo-1;
const int Max_N=505,Max_num=100005;

typedef pair<int,int> pii;

struct node{
  int to,cap,cost,pair;
  node(){};
  node(int _to,int _cap,int _cost,int _pair):
       to(_to),cap(_cap),cost(_cost),pair(_pair){}
};

vector<int> p;
vector<node> g[Max_N];
bool chk[Max_N];
pii pre[Max_N];
queue<int> q;
int a[Max_N],b[Max_N],w[Max_N],hash[Max_num],d[Max_N];
int F,M,K,S,T,aug,cost;

void mke(int a,int b,int c,int d,int e,int f,int pos_a,int pos_b){
  g[a].push_back(node(b,c,e,pos_b));g[b].push_back(node(a,d,f,pos_a));
}

bool augment(){  
  
  aug=oo;
  q.push(S);
  for(int i=0;i<=T;++i)
    d[i]=(i==S?0:NEG);
  memset(chk,false,sizeof(chk));
  chk[S]=true;
  int u;node w;
  
  while(!q.empty()){
    u=q.front();q.pop();chk[u]=false;
    for(int i=0;i<g[u].size();++i){
      w=g[u][i];
      if(w.cap>0&&d[u]+w.cost>d[w.to]){                        
        d[w.to]=d[u]+w.cost;
        pre[w.to]=make_pair(u,i);
        if(chk[w.to]==false){
          chk[w.to]=true;
          q.push(w.to);
        }
      }
    }
  }
  if(d[T]==NEG) return false;
  
  int now=T,v,ui,vi;
  while(now!=S){
    u=pre[now].first;ui=pre[now].second;
    if(aug>g[u][ui].cap) aug=g[u][ui].cap;
    now=u;
  }
  now=T;
  while(now!=S){       
    u=pre[now].first;ui=pre[now].second;v=g[u][ui].to;vi=g[u][ui].pair;
    g[u][ui].cap-=aug;g[v][vi].cap+=aug;
    now=u;
  }
  cost+=d[T]*aug;
  return true;
}

int MCMF(){
  cost=0;
  while(augment()){}  
  return cost;
}

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  
  scanf("%d",&F);
  while(F--){
    p.clear();
    scanf("%d%d",&M,&K);
    memset(hash,0,sizeof(hash));
    for(int i=1;i<=M;++i){
      scanf("%d%d%d",a+i,b+i,w+i);
      if(!hash[a[i]]){p.push_back(a[i]);hash[a[i]]=1;}
      if(!hash[b[i]]){p.push_back(b[i]);hash[b[i]]=1;}
    }
    sort(p.begin(),p.end());
    for(int i=0;i<p.size();++i)
      hash[p[i]]=i;
    S=p.size();T=p.size()+1;
    int u,v;   
    for(int i=0;i<=T;++i)
      g[i].clear();  
    for(int i=1;i<=M;++i){
      u=hash[a[i]];v=hash[b[i]];
      mke(u,v,1,0,w[i],-w[i],g[u].size(),g[v].size());
    }
    for(int i=0;i<p.size()-1;++i)
      mke(i,i+1,K,0,0,0,g[i].size(),g[i+1].size());
    mke(S,0,K,0,0,0,g[S].size(),g[0].size());
    mke(p.size()-1,T,K,0,0,0,g[p.size()-1].size(),g[T].size()); 
    printf("%d\n",MCMF()); 
  }
  
  return 0;

}
