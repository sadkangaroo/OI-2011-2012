/*
考察二次剩余中的勒让德(legendre)符号与欧拉判别法 
*/
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

long long t,tot,a,p,ans;

long long get_power(long long x,long long y){
  long long ret=1;
  while(y){
    if(y&1) ret=(ret*x)%p;
    x=(x*x)%p;
    y>>=1;
  }
  return ret;
}

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  scanf("%I64d",&tot);
  t=tot;
  while(t--){
    scanf("%I64d%I64d",&a,&p);
    ans=get_power((a%p+p)%p,(p-1)/2);  
    if(ans==p-1) ans=-1;
    printf("Scenario #%I64d:\n%I64d\n\n",tot-t,ans);
  }
  
  return 0;

}
