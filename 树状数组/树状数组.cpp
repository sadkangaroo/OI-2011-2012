/*
树状数组可以维护一个允许不断修改元素值的数组的所有前缀和，进而也可以用部分和的知识转化为区间和
其修改与询问的复杂度都是log级别的
现有一数组C，C[i]=A[i-i&(-i)+1]+…+A[i];即终点为A[i]的一段长度为 i&(-i) 的区间 
而每次修改A数组一个元素的值时，同时要修改c数组，若当前修改下标为p，则下次修改的下标为 p+p&(-p)
每次询问A数组前p项和时，要进行C数组一些项的累加，若当前累加的下标为p，则下次累加的下标为 p-p&(-p)
*/
#include<iostream>
using namespace std;


long c[1005],c2[1005][1005],n;

//一维形式 
void modify(long long p,long long del){
  for(;p<=n;p+=(p&(-p)))
    c[p]+=del;         //修改A[p]的值 
}

long sum(long long p){
  long ret=0;
  for(;p>0;p-=(p&(-p)))        
    ret+=c[p];               //求A数组前p项和 
  return ret;
}

//二维形式——>可依法推广至高维形式 
void modify_2(long x,long y,long delta){
 for(long i=x;i<=n;i+=(i&(-i)))
  for(long j=y;j<=n;j+=(j&(-j)))                 
    c2[i][j]+=delta;                  //修改A[p]的值 
}

long sum_2(long x,long y){
 long ret=0;
 for(long i=x;i>0;i-=(i&(-i)))
  for(long j=y;j>0;j-=(j&(-j)))
   ret+=c2[i][j];                   //求A数组前p项和 
 return ret;
}

int main(){
  return 0;
}
