/*
拓展的中国剩余定理直接应用 
*/
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

int m[]={0,23,28,33};
int ans,a,c,d,m1,m2,r1,r2,s,x,y;

int extend_gcd(int a,int b){
  if(b==0){x=1;y=0;return a;}
  int r=extend_gcd(b,a%b);
  int t=x;x=y;y=t-a/b*y;
  return r; 
} 

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  s=0;
  while(scanf("%d",&r1)&&r1!=-1){
    s++;
    m1=m[1];
    for(int i=2;i<=3;++i){
      scanf("%d",&r2);
      m2=m[i];
      d=extend_gcd(m1,m2);
      c=r2-r1; 
      int t=m2/d;
      x=(c/d*x%t+t)%t;
      r1=m1*x+r1;
      m1=m1*m2/d;
    }
    scanf("%d",&d);
    ans=(r1+m1-d)%m1;
    if(ans==0) ans=m1;
    printf("Case %d: the next triple peak occurs in %d days.\n",s,ans);
  }

  return 0;

}
