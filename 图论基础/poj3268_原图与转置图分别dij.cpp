/* 
  2011/1/14
  求所有点到一定点的最短往返路，
  对原图与转置图分别进行定点的单源最短路 
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

typedef pair<int,int> pii;

const int oo=0x7fffffff;
const int Max_N=1005;

priority_queue< pii,vector<pii>,greater<pii> > q;
vector<int> xi,yi,ti;
vector<pii> g[Max_N];
int d[Max_N],sum[Max_N],ans;
int N,M,X,ai,bi,ci;

void dij(){
  for(int i=1;i<=N;++i)
    d[i]=(i==X?0:oo);
  q.push(make_pair(d[X],X));
  while(!q.empty()){
    pii u=q.top();q.pop();
    int t=u.second;
    if(u.first!=d[t]) continue;
    for(int i=0;i<g[t].size();++i){
      if(d[t]+g[t][i].second<d[g[t][i].first]){
        d[g[t][i].first]=d[t]+g[t][i].second;
        q.push(make_pair(d[g[t][i].first],g[t][i].first));
      }
    }
  }
}

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  scanf("%d%d%d",&N,&M,&X);
  for(int i=1;i<=M;++i){
    scanf("%d%d%d",&ai,&bi,&ci);
    xi.push_back(ai);yi.push_back(bi);ti.push_back(ci);
  }
  
  memset(sum,0,sizeof(sum));
  for(int i=0;i<M;++i)
    g[xi[i]].push_back(make_pair(yi[i],ti[i]));
  dij();
  for(int i=1;i<=N;++i){
    g[i].clear();
    sum[i]+=d[i];
  }
  for(int i=0;i<M;++i)
    g[yi[i]].push_back(make_pair(xi[i],ti[i]));
  dij();
  ans=-1;
  for(int i=1;i<=N;++i){
    sum[i]+=d[i];
    if(sum[i]>ans) ans=sum[i];
  }
  printf("%d\n",ans);

  return 0;

}
