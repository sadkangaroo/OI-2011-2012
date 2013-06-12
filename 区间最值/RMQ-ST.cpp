/*
ST算法可以在O(nlogn)的预处理之后实现O(1)的查询区间最值
预处理的 f[i][j]表示[i,i+2^j-1]内的最值，
初始时f[i][0]=h[i]，递推式为 f[i][j]=max/min{f[i][j-1],f[i+(1<<(j-1))][j-1]},
即把区间二分位两部分求玩后取最大（小）的
询问时有 max/min(a,b)=max{f[a][k],f[b-(1<<k)+1][k]} 
其中k为  log(b-a+1)/log(2); 既满足2^k小于区间长，2^(k+1)大于区间长 
*/

#include<iostream>
#include<string>
#include<math.h>
using namespace std;

long n,a,b;
long h[100005],f[100005][35]; 

void inimax(){
  long i,j;
  for(long i=1;i<=n;++i)
   f[i][0]=h[i];
  for(long j=1;j<=log((double)(n+1))/log(2.0);++j)
   for(long i=1;i+(1<<j)-1<=n;++i)
    f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}

long rmaxq(long a,long b){
  long k=(long)(log((double)(b-a+1))/log(2.0));
  return max(f[a][k],f[b-(1<<k)+1][k]);
}

int main(){
  return 0;
}
