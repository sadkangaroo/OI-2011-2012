/*
  2011/1/18
  最大流构图题
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

const int oo=0x7fffffff;
const int Max_M=1005;
const int Max_N=105;

struct node{
  int to,cap,pair;
  node(int _to,int _cap,int _pair):to(_to),cap(_cap),pair(_pair){};
};

bool found;
vector<node> g[Max_N];vector<int> p[Max_M];
int pigs[Max_M],d[Max_N],v[Max_N];
int N,M,S,T,tot,flow,aug;

void mke(int a,int b,int c,int pos_a,int pos_b){
  g[a].push_back(node(b,c,pos_b));g[b].push_back(node(a,0,pos_a));
}

void augment(int now){
  int tmp=aug,min_d=tot-1;
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

int main(){
  
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  scanf("%d%d",&M,&N);
  for(int i=1;i<=M;++i)
    scanf("%d",pigs+i);
  S=0;T=N+1;
  for(int i=1;i<=N;++i){
    int x,r;
    scanf("%d",&x);
    for(int k=1;k<=x;++k){
      scanf("%d",&r);
      p[r].push_back(i);
    }
    scanf("%d",&x);
    mke(i,T,x,g[i].size(),g[T].size());
  }
  for(int i=1;i<=M;++i){
    for(int k=0;k<p[i].size();++k){
      if(k==0) mke(S,p[i][0],pigs[i],g[S].size(),g[p[i][0]].size());
        else mke(p[i][k-1],p[i][k],oo,g[p[i][k-1]].size(),g[p[i][k]].size());
    }
  }
  
  tot=N+2;
  memset(d,0,sizeof(d));
  memset(v,0,sizeof(v));
  v[0]=tot;
  flow=0;
  
  while(d[S]<tot){
    aug=oo;    
    found=false;
    augment(S);            
  }
  
  printf("%d\n",flow);
  
  return 0;

}
