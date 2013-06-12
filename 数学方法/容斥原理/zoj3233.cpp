/*
题目大意：给定数列a和数列b
要求区间[low,high]内的所有数满足：
1.至少被a中一个数整除 2.至少不被b中一个数整除
解题思路：考虑补集转换-->至少被a中一个数整除且被b中所有数整除
即等价于：至少被a中一个数整除且被b中所有数的最小公倍数整除
运用容斥原理，利用位运算解决 
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

const int Max_Na=20,Max_Nb=510;
typedef long long LLD;

LLD low,high;
LLD a[Max_Na],b[Max_Nb];
LLD Na,Nb,lcm_b,lcm_tot,ans;

LLD gcd(LLD x,LLD y){return y?gcd(y,x%y):x;}

LLD lcm(LLD x,LLD y){
  LLD d=gcd(x,y);
  return high/(x/d)<y?high+1:x/d*y;
} 

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  while(scanf("%lld%lld%lld%lld",&Na,&Nb,&low,&high)&&Na){
    for(LLD i=0;i<Na;++i) 
      scanf("%lld",a+i);
    lcm_b=1;
    for(LLD i=0;i<Nb;++i){
      scanf("%lld",b+i);
      lcm_b=lcm(lcm_b,b[i]);
    }
    ans=0;
    for(LLD s=1;s<(1<<Na);++s){
      LLD sum=0,lcm_tot=1;
      for(LLD i=0;i<Na;++i)
        if(s&(1<<i)){sum++;lcm_tot=lcm(lcm_tot,a[i]);}
        if(sum&1){
          ans+=(high/lcm_tot-(low-1)/lcm_tot);
          ans-=(high/lcm(lcm_tot,lcm_b)-(low-1)/lcm(lcm_tot,lcm_b));
        }
        else{
          ans-=(high/lcm_tot-(low-1)/lcm_tot);
          ans+=(high/lcm(lcm_tot,lcm_b)-(low-1)/lcm(lcm_tot,lcm_b));
        }
    }
    printf("%lld\n",ans);
  }
  
  return 0;

}
