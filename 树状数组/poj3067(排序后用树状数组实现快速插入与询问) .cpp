/*
题目大意：
左边有n个站点，右边有m个站点，左右站点间有高速公路相连，每两条高速公路的交点消耗以单位费用，
无三点共线，求消耗费用
算法思路:先将k条公路按左端点从大到小排序（相同则右端点从大到小），按顺序考虑，对于当前的高速公路，
若之前考虑的高速公路（左端点编号都大于当前公路）右端点编号小于当前公路则产生以单位费用，
由于两条线段产生一个交点只需要计算一次，所以每次只考虑之前的线段与其的交点，
且之前线段若左端点与其相同，右端点一定大于其右端点， 
所以只需要维护1~k的右端点目前连了几条公路，操作有
1）每次加入一条公路时其右端点所连公路树加一 
2）询问1~k的右端点目前连了几条公路
可以用树状数组实现每次操作log级别 
*/
#include<iostream>
#include<string>
#include<math.h>
#include<algorithm>

using namespace std;

struct road{
  long long x,y;
  bool operator < (road const &t)const{
    if(x!=t.x) return x<t.x;
    return y<t.y;
  }
}a[1000005];

long long n,m,k,x,y,c[1005],ans,t;

void modify(long long p,long long del){
  for(;p<=n;p+=(p&(-p)))
    c[p]+=del;         //修改A[p]的值 
}

long sum(long long p){
  long ret=0;
  for(;p>0;p-=(p&(-p)))        //求A数组前p项和 
    ret+=c[p];
  return ret;
}

int main(){
  scanf("%I64d",&t);
  for(long long tt=1;tt<=t;++tt){
   scanf("%I64d%I64d%I64d",&n,&m,&k);
   for(long long i=1;i<=k;++i){
     scanf("%I64d%I64d",&x,&y);
     a[i].x=x;
     a[i].y=y;
   }
   sort(a+1,a+k+1);
   ans=0;
   memset(c,0,sizeof(c));
   for(long long i=k;i>=1;--i){
     if(a[i].y>1) ans+=sum((a[i].y)-1);  
     modify(a[i].y,1);     
   }
   printf("Test case %I64d: %I64d\n",tt,ans);
  }
  return 0;
}
