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

using namespace std;

const int Max_N=100005,Max_K=25;
const int Mod=8388608;

int C[Max_N][Max_K];
int T,N,K,ans,tmp;

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  
  C[0][0]=1;
  for(int i=1;i<Max_N;++i){
    C[i][0]=1;if(i<Max_K) C[i][i]=1;
    tmp=min(i,Max_K);
    for(int j=1;j<tmp;++j)
      C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
  }
  scanf("%d",&T);
  while(T--){
    ans=0;
    scanf("%d%d",&N,&K);
    for(int t=1;t<=23&&t<=K;++t)
      ans=(ans+(int)((((long long)((C[N][t]*t)%Mod))*((long long)(1<<(t-1))))%Mod))%Mod;
    printf("%d\n",ans);
  }

  return 0;

}
