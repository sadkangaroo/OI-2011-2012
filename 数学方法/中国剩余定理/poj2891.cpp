/*
拓展的中国剩余定理直接应用 
*/
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

bool flag;
long long n,m1,m2,r1,r2,c,d,x,y;

long long extend_gcd(long long a,long long b){
  if(b==0){x=1;y=0;return a;}
  long long r=extend_gcd(b,a%b);
  long long t=x;x=y;y=t-a/b*y;
  return r; 
} 

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  while(scanf("%I64d",&n)!=EOF){
    flag=true;
    scanf("%I64d%I64d",&m1,&r1);
    for(long long i=1;i<n;++i){
      scanf("%I64d%I64d",&m2,&r2);
       if(flag==false) continue;
      d=extend_gcd(m1,m2);
      c=r2-r1;
      if(c%d!=0){
        flag=false;
        continue;
      }
      long long t=m2/d;
      x=(c/d*x%t+t)%t;
      r1=m1*x+r1;
      m1=m1*m2/d;
    }
    if(flag) printf("%I64d\n",r1);
     else printf("-1\n");
  }

  return 0;

}
