/*
由二次剩余的相关理论可知，p为奇素数的必要条件为 
x^2=1(mod p)有且仅有两解x=+/- 1（mod p)
又由费马小定理得，若(p,a)=1,则p为素数的必要条件为 
a^(p-1)=1(mod p) 
由以上两点可以设计出米勒拉宾素性测试
对于 n < 2,152,302,898,747, 只要以2,3,5,7,11为底测试即可 
判断一个数p是否为素数，首先
int pri[]={2,3,5,7,11};
bool check(int p){ 
  if(p<2) return false;
  if(p==2||p==3||p==5||p==7||p==11) return true;
  if(p%2==0||p%3==0||p%5==0||p%7==0||p%11==0) return false;
  bool ans=true;
  for(int i=0;i<5;++i)
    ans&=Miller_Rabin(pri[i],p);
  return ans; 
} 
其次 
bool Miller_Rabin(int a,int p){
  int d=p-1;
  while(!(d&1)) d>>=1;
  long long t=get_power(a,d,p);
  while(d!=p-1){
    if(t==p-1) return true;  //若为-1,之前一定是乱七八糟的数，之后都是1， 停止判断返回true 
    if(t==1){                //若为1，之前一定没出现-1，假如是第一次返回true，否则返回false  
      if(d&1) return true;
      return false;
    }
    t=(t*t)%p;
    d<<=1;
  }
  return false;               //之前至少进行过一次，若之前都没有出现1或-1， 
}                             //则最后一次不管符不符合费马小定理，p都不可能为素数，返回false  
 
*/ 
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

int main(){
  return 0;
}
