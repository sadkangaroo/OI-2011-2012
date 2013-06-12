/*
  2011/1/13
  要求两点间的一条路径使得最长边最短 
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

typedef pair<int,int> pii;

const int oo=0x7fffffff;
const int Max_N=205;

vector<pii> e; 
int n,s;
int xi[Max_N],yi[Max_N];
double dis[Max_N][Max_N];
int fa[Max_N],rank[Max_N];

bool cmp(const pii &a,const pii &b){
  return dis[a.first][a.second]<dis[b.first][b.second];
}

int grand(int x){
  if(fa[x]==x) return x;
  fa[x]=grand(fa[x]);
  return fa[x];
}

void unify(int x,int y){
  int fx=grand(x),fy=grand(y);
  if(fx==fy) return;
  if(rank[fx]<rank[fy])
    fa[fx]=fy;
  else{
    fa[fy]=fx;
    if(rank[fx]==rank[fy])
      rank[fx]++;
  }
}

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  s=0;
  while(scanf("%d",&n)&&n){
    s++;if(s!=1) printf("\n");
    for(int i=1;i<=n;++i)
      scanf("%d%d",xi+i,yi+i);
    e.clear();
    for(int i=1;i<n;++i)
      for(int j=i+1;j<=n;++j){
        dis[i][j]=sqrt(double((xi[i]-xi[j])*(xi[i]-xi[j])+(yi[i]-yi[j])*(yi[i]-yi[j])));
        e.push_back(make_pair(i,j));
      }
    sort(e.begin(),e.end(),cmp);
    for(int i=1;i<=n;++i){ 
      fa[i]=i;
      rank[i]=1;
    }
    for(int i=0;i<e.size();++i){
      unify(e[i].first,e[i].second);
      if(grand(1)==grand(2)){
        printf("Scenario #%d\nFrog Distance = %.3lf\n",s,dis[e[i].first][e[i].second]);
        break;
      }
    }
    
  }    

  return 0;

}
