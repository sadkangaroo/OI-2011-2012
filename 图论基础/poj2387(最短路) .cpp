/*
  2011/1/12
  ≤‚ ‘dijƒ£∞Â”√
  <vector|priority_queue> 
*/
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<vector>
#include<queue>

using namespace std;

typedef pair<int,int> pii;

const int oo=0x7fffffff;
const int Max_N=1003;

vector <pii> g[Max_N];
priority_queue< pii,vector<pii>,greater<pii> > q;
int d[Max_N];
int T,N,ai,bi,ci;

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  scanf("%d%d",&T,&N);
  for(int i=1;i<=T;++i){
    scanf("%d%d%d",&ai,&bi,&ci);
    g[ai].push_back(make_pair(bi,ci));
    g[bi].push_back(make_pair(ai,ci));
  }
  
  for(int i=1;i<=N;++i)
    d[i]=(i==1?0:oo);
  q.push(make_pair(d[1],1));
  
  while(!q.empty()){
    pii u=q.top();q.pop();
    int x=u.second;
    if(u.first!=d[x]) continue;
    for(int i=0;i<g[x].size();++i)
      if(d[x]+g[x][i].second<d[g[x][i].first]){
        d[g[x][i].first]=d[x]+g[x][i].second;
        q.push(make_pair(d[g[x][i].first],g[x][i].first));
      }
  }
  
  printf("%d\n",d[N]);

  return 0;

}
