/*
题目大意 有一n*n得格子图，每次可以修改一格中的数，也可以询问某个矩形里的数之和
算法：运用树状数组的二维形式 
*/

#include<iostream>
#include<string>
#include<math.h>
using namespace std;

long n,order,x,y,a,l,b,r,t;
long c[1205][1205];

void modify(long x,long y,long delta){
 for(long i=x;i<=n;i+=(i&(-i)))
  for(long j=y;j<=n;j+=(j&(-j)))
    c[i][j]+=delta;
}

long sum(long x,long y){
 long ret=0;
 for(long i=x;i>0;i-=(i&(-i)))
  for(long j=y;j>0;j-=(j&(-j)))
   ret+=c[i][j];
 return ret;
}

int main(){
  scanf("0 %ld\n",&n);
  memset(c,0,sizeof(c));
  while(scanf("%ld",&order)&&order!=3){
    if(order==1){
      scanf("%ld%ld%ld",&x,&y,&a);
      modify(x+1,y+1,a);
    }          
    else{
      scanf("%ld%ld%ld%ld",&l,&b,&r,&t);
      printf("%ld\n",sum(r+1,t+1)-sum(l,t+1)-sum(r+1,b)+sum(l,b));
    }                        
  }
  return 0;
}
