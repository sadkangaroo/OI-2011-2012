/*
  2011/1/13
  要求两点间的一条路径使得最短边最长 
  <排序+并查集>
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

using namespace std;

const int oo=0x7fffffff;
const int Max_N=1005;

struct edge{
  int x,y,v;
  edge(int _x,int _y,int _v):x(_x),y(_y),v(_v){}
  bool operator > (const edge &t)const{
    return v>t.v;
  }
};

vector<edge> e;
int fa[Max_N],rank[Max_N];
int T,N,M,ai,bi,ci;

int grand(int x){
  if(fa[x]==x) return x;
  fa[x]=grand(fa[x]);
  return fa[x];
}

void unify(int x,int y){
  int fx=grand(x),fy=grand(y);
  if(fx==fy) return;
  if(rank[fx]<rank[fy]) fa[fx]=fy;
  else{
    fa[fy]=fx;
    if(rank[fx]==rank[fy]) rank[fx]++;
  }
}

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  
  scanf("%d",&T);
  for(int tt=1;tt<=T;++tt){
    scanf("%d%d",&N,&M);
    if(tt!=1) printf("\n");
    e.clear();
    for(int i=1;i<=M;++i){
      scanf("%d%d%d",&ai,&bi,&ci);
      e.push_back(edge(ai,bi,ci));
    }
    sort(e.begin(),e.end(),greater<edge>());
    for(int i=1;i<=N;++i){
      fa[i]=i;
      rank[i]=1;
    }
    for(int i=0;i<e.size();++i){
      unify(e[i].x,e[i].y);
      if(grand(1)==grand(N)){
        printf("Scenario #%d:\n%d\n",tt,e[i].v);
        break;
      }
    }
  }

  return 0;

}
