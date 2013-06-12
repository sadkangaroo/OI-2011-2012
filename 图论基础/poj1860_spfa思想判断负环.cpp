/*
  2011/1/14
  利用spfa思想解决问题 
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

const int NEG=-1;
const int Max_N=105;

struct edge{
  int to;
  double rate,cms;
  edge(int _to,double _rate,double _cms):to(_to),rate(_rate),cms(_cms){}
};

double V,rab,rba,cab,cba;
double d[Max_N];
vector<edge> g[Max_N];
queue<int> q;
bool check[Max_N];
int p[Max_N];
int N,M,S,a,b; 

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  scanf("%d%d%d%lf",&N,&M,&S,&V);
  for(int i=1;i<=M;++i){
    scanf("%d%d%lf%lf%lf%lf",&a,&b,&rab,&cab,&rba,&cba);
    g[a].push_back(edge(b,rab,cab));
    g[b].push_back(edge(a,rba,cba));
  }
  
  for(int i=1;i<=N;++i)
    d[i]=(i==S?V:NEG);
  memset(check,false,sizeof(check));
  memset(p,0,sizeof(p));
  check[S]=true;p[S]=1;
  q.push(S);
  while(!q.empty()&&d[S]<=(V+0.000001)){
    int u=q.front();q.pop();check[u]=false;
    for(int i=0;i<g[u].size();++i){
      edge t=g[u][i];
      if((d[u]-t.cms)*t.rate>d[t.to]){
        d[t.to]=(d[u]-t.cms)*t.rate;
        if(check[t.to]==false){
          p[t.to]++;
          if(p[t.to]>N){d[S]=V+1;break;}
          check[t.to]=true;
          q.push(t.to);
        }
      }
    }
  }
  
  if(d[S]>V) printf("YES\n");
    else printf("NO\n");

  return 0;

}
