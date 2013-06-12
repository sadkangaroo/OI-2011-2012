#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<vector>
#include<iterator>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
#include<set>
#include<list>
#include<utility>
#include<complex>

using namespace std;

const int oo=0x7fffffff;
const int Max_N=1005,Max_M=1005;

int stretch[Max_N][Max_M],lef[Max_N][Max_M],rig[Max_N][Max_M];
bool G[Max_N][Max_M];
char o;
int K,N,M,ans;

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  
  scanf("%d",&K);
  while(K--){
    scanf("%d%d\n",&N,&M);
    memset(G,false,sizeof(G));
    for(int i=1;i<=N;++i)
      for(int j=1;j<=M;++j){
        while((o=getchar())&&(o!='F')&&(o!='R')){}
        if(o=='R') G[i][j]=false;
          else G[i][j]=true;
      }
    
    memset(stretch,0,sizeof(stretch));
    for(int i=1;i<=N;++i)
      for(int j=1;j<=M;++j)
        if(G[i][j]){
          if(G[i-1][j]) stretch[i][j]=stretch[i-1][j]+1;
            else stretch[i][j]=1;
        }
      
    memset(lef,0,sizeof(lef));
    memset(rig,0,sizeof(rig));
    for(int i=1;i<=N;++i)
      for(int j=1;j<=M;++j){
        if(j==1) { lef[i][j]=1;continue; }
        if(stretch[i][j]<=stretch[i][j-1]) lef[i][j]=lef[i][j-1];
          else lef[i][j]=j;
      }
    for(int i=1;i<=N;++i)
      for(int j=M;j>=1;--j){
        if(j==M) { rig[i][j]=M;continue; }
        if(stretch[i][j]<=stretch[i][j+1]) rig[i][j]=rig[i][j+1];
          else rig[i][j]=j;
      }
      
    ans=0;
    for(int i=1;i<=N;++i)
      for(int j=1;j<=M;++j)
        ans=max(ans,stretch[i][j]*(rig[i][j]-lef[i][j]+1));
    
    printf("%d\n",ans*3);      
    
  }

  return 0;

}
