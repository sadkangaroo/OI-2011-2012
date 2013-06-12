#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<iterator>
#include<vector>
#include<list>
#include<deque>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
#include<set>
#include<complex>

using namespace std;

const int Max_N=1000005;

long long sum,delta;
int a[Max_N];
int T,N;

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  scanf("%d",&T);
  while(T--){
    scanf("%d",&N);
    for(int i=0;i<N;++i){
      scanf("%d",a+i);
      if(i==0) sum=(long long)(a[0]);
        else sum+=(long long)(2*a[i]);
    }
    delta=0;
    for(int i=N-1;i>0;--i){
      sum+=delta;
      delta+=(long long)(a[i]);
      if(delta<0) delta=0;
    }
    printf("%lld\n",sum);
  } 

  return 0;

}
