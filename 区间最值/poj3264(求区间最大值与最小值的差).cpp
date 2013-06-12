/*
RMQ_ST最基础的运用 
*/
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

long n,q,a,b;
long h[100005],dpmax[100005][35],dpmin[100005][35];

long get_max(long a,long b){
  if(a>b) return a;
  return b;
}

long get_min(long a,long b){
  if(a<b) return a;
  return b;
}

void inimax(){
  long i,j;
  for(long i=1;i<=n;++i)
   dpmax[i][0]=h[i];
  for(long j=1;j<=log((double)(n+1))/log(2.0);++j)
   for(long i=1;i+(1<<j)-1<=n;++i)
    dpmax[i][j]=get_max(dpmax[i][j-1],dpmax[i+(1<<(j-1))][j-1]);
}

void inimin(){
  long i,j;
  for(long i=1;i<=n;++i)
   dpmin[i][0]=h[i];
  for(long j=1;j<=log((double)(n+1))/log(2.0);++j)
   for(long i=1;i+(1<<j)-1<=n;++i)
    dpmin[i][j]=get_min(dpmin[i][j-1],dpmin[i+(1<<(j-1))][j-1]);
}

long rmaxq(long a,long b){
  long k=(long)(log((double)(b-a+1))/log(2.0));
  return get_max(dpmax[a][k],dpmax[b-(1<<k)+1][k]);
}

long rminq(long a,long b){
  long k=(long)(log((double)(b-a+1))/log(2.0));
  return get_min(dpmin[a][k],dpmin[b-(1<<k)+1][k]);
}

int main(){
    
freopen("a.in","r",stdin);
freopen("a.out","w",stdout);

  scanf("%ld%ld",&n,&q);
  for(long i=1;i<=n;++i)
   scanf("%ld",h+i);
  inimax();
  inimin();
  while(q--){
    scanf("%ld%ld",&a,&b);
    
    long tmp1=rmaxq(a,b);
    long tmp2=rminq(a,b);
    
    printf("%ld\n",rmaxq(a,b)-rminq(a,b));
  }

  return 0;
}
