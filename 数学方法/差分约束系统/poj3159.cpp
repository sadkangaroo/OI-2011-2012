/*
题目大意：小朋友分糖，有一些关系：b的糖的个数多于a的糖的个数不能大于c；
要求小朋友n的糖比小朋友1的糖最多多多少。
以1号小朋友为源点，dis值设为0，即就是求n号小朋友糖的最大值， 
从而建立差分约束图，用spfa+stack求最短路，可求的一组可行解dis[i]，
且此时每个变量取值达到最大值，所以答案为dis[n]； 
*/
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

const int Max_N=30005;
const int Max_E=150005;
const int oo=1<<30;

struct node{
  int to,cost,lnk;
  node(){};
  node(int _to,int _cost,int _lnk){ to=_to; cost=_cost; lnk=_lnk;}
}e[Max_E];
int point=-1;

int g[Max_N],s[Max_N];

int N,M,a,b,c,t,cost,to,f,r;
int dis[Max_N],vis[Max_N];

int main(){
  
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  
  scanf("%d%d",&N,&M);
  
  memset(g,-1,sizeof(g));
  
  for(int i=1;i<=M;++i){
    scanf("%d%d%d",&a,&b,&c);
    e[++point]=node(b,c,g[a]);
    g[a]=point;
  }
  
  
  for(int i=2;i<=N;++i)
    dis[i]=oo;
  memset(vis,0,sizeof(vis));
  dis[1]=0;
  vis[1]=1;
    
  s[0]=1;
  r=0;
  
  while(r!=-1){
    t=s[r];
    vis[t]=0;
    r--;
    for(int cur=g[t];cur!=-1;cur=e[cur].lnk){
      cost=e[cur].cost;to=e[cur].to;
      if(dis[t]+cost<dis[to]){
        dis[to]=dis[t]+cost;
        if(!vis[to]){
          vis[to]=1;
          r++;
          s[r]=to;
        }
      }
    }
  }
  
  printf("%d\n",dis[N]);
  
  return 0;

}

