/*
  2011/1/15
  ´«µÝ±Õ°ü 
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
const int Max_N=105;

bool g[103][103];
int N,M,ai,bi,t,sum;

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  scanf("%d%d",&N,&M);
  memset(g,false,sizeof(g));
  for(int i=1;i<=M;++i){
    scanf("%d%d",&ai,&bi);
    g[ai][bi]=true;    
  }

  for(int k=1;k<=N;++k)
    for(int i=1;i<=N;++i)
      for(int j=1;j<=N;++j){
        if(i!=j&&i!=k&&j!=k)
          g[i][j]=g[i][j]||g[i][k]&&g[k][j];
      }

  sum=0;
  for(int i=1;i<=N;++i){
    t=0;
    for(int j=1;j<=N;++j)
      if(g[i][j]||g[j][i]) 
        t++;
    if(t==N-1) sum++;
  }
      
  printf("%d\n",sum);

  return 0;

}
