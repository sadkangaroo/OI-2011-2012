/*
利用米勒拉宾素性测试输出给定区间内的所有素数 
*/
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

int pri[]={2,3,5,7,11};
int t,l,r;

int get_power(long long a,int t,int p){
  long long ans=1;
  while(t){
    if(t&1) ans=(ans*a)%p;
    a=(a*a)%p;
    t>>=1;
  }
  return ans;
}

bool Miller_Rabin(int a,int p){
  int d=p-1;
  while(!(d&1)) d>>=1;
  long long t=get_power(a,d,p);
  while(d!=p-1){
    if(t==p-1) return true;
    if(t==1){
      if(d&1) return true;
      return false;
    }
    t=(t*t)%p;
    d<<=1;
  }
  return false;
}

bool check(int p){
    
  if(p<2) return false;
  if(p==2||p==3||p==5||p==7||p==11) return true;
  if(p%2==0||p%3==0||p%5==0||p%7==0||p%11==0) return false;
  bool ans=true;
  for(int i=0;i<5;++i)
    ans&=Miller_Rabin(pri[i],p);
  return ans; 
}

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  scanf("%d",&t);
  while(t--){
    scanf("%d%d",&l,&r);
    for(int i=l;i<=r;++i)
      if(check(i)) printf("%d\n",i);
    if(t) putchar('\n');
  }  

  return 0;

}
