#include<iostream>
#include<math.h>
#include<string>
using namespace std;

/*
矩阵是解决线性变换的强有力工具，
矩阵不满足交换律但满足结合律和分配律，因此可以用二分法，尤其是快速幂进行加速 
*/

struct matrix{
  long size_n,size_m;
  long a[103][103];
  matrix(long n=0,long m=0){
    if(n<0&&m<0){
      size_n=-n;
      size_m=-m;
      long t=-n;
      memset(a,0,sizeof(a));
      for(long i=1;i<=t;++i)
       a[i][i]=1;                //单位矩阵 
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
      ret.a[i][j]=a[i][j]+t.a[i][j];
    return ret;
  }
  matrix operator * (const matrix &t)const{
    matrix ret(size_n,t.size_m);
    memset(ret.a,0,sizeof(ret.a));
    for(long i=1;i<=size_n;++i)
     for(long j=1;j<=t.size_m;++j)
      for(long k=1;k<=size_m;++k)
       ret.a[i][j]+=(a[i][k]*t.a[k][j]);  //矩阵乘法的运算法则 
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

int main(){
  return 0;
}
