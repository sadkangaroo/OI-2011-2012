/*
题目大意：
求一个矩阵的前k次幂之和
算法：
在计算矩阵幂次时使用快速幂
在计算前k次幂之和时进行2分 
即：sigmaA^(1-k)=sigmaA^(1-k/2)+A^(k/2)*sigmaA^(1-k/2) 
进行递归时注意每层不要产生分支，及一个量提前计算一次计算好再反复用
*/
 
#include<iostream>
#include<math.h>
#include<string>
using namespace std;

long n,k,m;

struct matrix{
  long size_n,size_m;
  long a[33][33];
  matrix(long n=0,long m=0){
    if(n<0&&m<0){
      size_n=-n;
      size_m=-m;
      long t=-n;
      memset(a,0,sizeof(a));
      for(long i=1;i<=t;++i)
       a[i][i]=1;                
    }
    else{
      size_n=n;
      size_m=m;
      memset(a,0,sizeof(a));
    }
  }
  matrix operator + (const matrix &t)const{
    matrix ret(size_n,size_m);
    for(long i=1;i<=size_n;++i)
     for(long j=1;j<=size_m;++j)
      ret.a[i][j]=(a[i][j]+t.a[i][j])%m;
    return ret;
  }
  matrix operator * (const matrix &t)const{
    matrix ret(size_n,t.size_m);
    memset(ret.a,0,sizeof(ret.a));
    for(long i=1;i<=size_n;++i)
     for(long j=1;j<=t.size_m;++j)
      for(long k=1;k<=size_m;++k)
       ret.a[i][j]=(ret.a[i][j]+(a[i][k]*t.a[k][j]))%m;  
    return ret;
  }
  void operator *= (const matrix &t){
    *this=(*this)*t;
  }
  matrix operator ^ (long p)const{
    matrix tmp=*this,ret(-size_n,-size_m);
    while(p){
      if(p%2) ret*=tmp;
      tmp*=tmp;
      p/=2;
    }
    return ret;
  }
}; 


matrix mat,ans;

matrix find(long now){
  if(now==1) return mat;
  if(now%2) return find(now-1)+(mat^now);
  matrix tmp=find(now/2);
  return tmp+((mat^(now/2))*tmp);
}

int main(){
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  scanf("%ld%ld%ld",&n,&k,&m);
  mat.size_n=mat.size_m=n;
  for(long i=1;i<=n;++i)
   for(long j=1;j<=n;++j){
    scanf("%ld",&mat.a[i][j]);
    mat.a[i][j]%=m;
   }
  ans=find(k);
  for(long i=1;i<=n;++i){
   for(long j=1;j<=n;++j)
    if(j==1) printf("%ld",ans.a[i][j]%m);
     else printf(" %ld",ans.a[i][j]%m);
   printf("\n");
  }
    
  return 0;
}
