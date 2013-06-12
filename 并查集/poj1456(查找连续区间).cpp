/*
题目大意：
给定n件商品，每件商品有价值和deadline,
必须在deadline之前卖掉，每一个单位时间只能卖一件商品，求可以卖出的最大价值 

*贪心策略：
每件商品都需要被考虑，那么先确定考虑顺序。
先排序，价值从大到小，价值相同则时间从晚到早 
1)若它可以被卖出而不卖出，则对于这件商品允许卖出的最晚时间点，
若被之后的商品占用，则可以替换使得总价值增加，若未被占用，则可以占用使总价值增加，
所以当前考虑的商品若可以被卖出一定被卖出 
2)若它可以卖出且被卖出了，显然在当前最晚允许时间点卖出不会产生比最优解劣的解 
3)若它不可以被卖出，它显然不能被卖出 
由此得到n^2算法

*数据结构优化
——>并查集 
连续的被占用时间点在同一颗树上，根节点为该区间左侧的空白时间点 
在查找最晚可卖出时间点时，只需直接访问deadline所在树的根节点
在占用时间点时，只需要将当前被占用的根节点的父节点设为其左侧节点所在树的根节点 
*/


#include<iostream>

using namespace std;

struct pro{
  long p,d;
  bool operator >(const pro &t)const{
    if(p==t.p) return d>t.d;
    return p>t.p;
  }
}a[10003];

long n,ans,t;
long father[10003];


void qs(long l,long r){
  long i=l,j=r;
  pro tmp,mid=a[(l+r)/2];
  do{
    while(a[i]>mid) i++;
    while(mid>a[j]) j--;
    if(i<=j){
      tmp=a[i];a[i]=a[j];a[j]=tmp;
      i++;j--;
    }
  }while(i<=j);
  if(l<j) qs(l,j);
  if(i<r) qs(i,r);
}

long grand(long x){
  if(father[x]==x) return x;
  father[x]=grand(father[x]);
  return father[x];
}

int main(){
    
  while(scanf("%ld",&n)!=EOF){
    for(long i=1;i<=n;++i)
     scanf("%ld%ld",&(a[i].p),&(a[i].d));
    ans=0;
    qs(1,n);
    for(long i=0;i<=10001;++i)
      father[i]=i;
    for(long i=1;i<=n;++i){
      t=grand(a[i].d);
      if(t>0){
        father[t]=grand(t-1);
        ans+=a[i].p;
      }
    }
    printf("%ld\n",ans);
  }

  return 0;
 
}
