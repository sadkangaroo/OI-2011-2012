/*
  2010/1/15
  判断图中是否存在负环
  需要初始时将所有d[i]设为0，并将所有节点入队 
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

const int oo=0x7fffffff;
const int Max_N=505;

struct edge{
  int to,v;
  edge(int _to,int _v):to(_to),v(_v){}
};

vector<edge> g[Max_N];
queue<int> q;
bool check[Max_N];
int d[Max_N],p[Max_N];
int F,N,M,W,ai,bi,ci;

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  scanf("%d",&F);
  while(F--){
    scanf("%d%d%d",&N,&M,&W);
    for(int i=1;i<=N;++i) g[i].clear();
    for(int i=1;i<=M;++i){
      scanf("%d%d%d",&ai,&bi,&ci);
      g[ai].push_back(edge(bi,ci));
      g[bi].push_back(edge(ai,ci));
    }
    for(int i=1;i<=W;++i){
      scanf("%d%d%d",&ai,&bi,&ci);
      g[ai].push_back(edge(bi,-ci));
    }
    while(!q.empty()) q.pop();
    for(int i=1;i<=N;++i){
      check[i]=true;p[i]=0;
      d[i]=0;q.push(i);
    }
  
    while(!q.empty()&&d[1]!=oo){
      int u=q.front();q.pop();
      check[u]=false;
      for(int i=0;i<g[u].size();++i){
        edge t=g[u][i];
        if(d[u]+t.v<d[t.to]){
          d[t.to]=d[u]+t.v;
          if(check[t.to]==false){
            q.push(t.to);
            check[t.to]=true;
            p[t.to]++;
            if(p[t.to]>N) d[1]=oo;
          }
        }
      }
    }
  
    if(d[1]==oo) printf("YES\n");
      else printf("NO\n");    
  }

  return 0;

}
