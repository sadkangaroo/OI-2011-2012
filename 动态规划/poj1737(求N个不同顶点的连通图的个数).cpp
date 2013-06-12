/*
 求N个不同顶点的连通图的个数，考虑补集转化，只要求非联通图的个数G(N)，则所求F(N)=2^(N*(N-1)/2)-G[N]; 
 对于F(N），取出任意一点x，枚举其所在连通块的构成及连接情况，余下的点可以任意连边 
 则有G(N)=sigma{C(i-1,N-1)*F[i]*2^((N-i)*(N-i-1)/2),i=1…N-1}
 搭配上高精度，此题顺利解决 
*/ 
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

const long num_length=(1000)/4+5;
const long mod=10000;
const long largest=10000;
long bigger(long x,long y) { if(x>y) return x; return y; }

struct bignum{
  
 long a[num_length],l;
  
 bignum(long t=0){
   memset(a,0,sizeof(a));
   l=0;
   for(;t;t/=mod) 
     a[l++]=t%mod;
   if(!l) l=1;
 }
 
 void print(){
   printf("%ld",a[l-1]);
   for(long i=l-2;i>=0;--i)
    printf("%04ld",a[i]);
 }
 
 void carry(){
   for(long i=1;i<=l;++i)
    if(a[i-1]>=mod){
      a[i]+=a[i-1]/mod;
      a[i-1]%=mod;
    }
    while(l>1&&!a[l-1]) l--;
 }
 
 void operator = (long t){
    memset(a,0,sizeof(a));
    l=0;
    for(;t;t/=mod) 
      a[l++]=t%mod;
    if(!l) l=1;
 }
 
 bignum operator + (const bignum &t) const{
   bignum c;
   c.l=bigger(l,t.l)+1;
   for(long i=0;i<c.l;++i)
    c.a[i]=a[i]+t.a[i];
   c.carry();
   return c;
 }
 
 bignum operator + (const long &t) const{
   bignum c;
   c=*this;
   c.l+=2;
   c.a[0]+=t;
   c.carry();
   return c;
 }
 
 void operator += (const bignum &t) {
   *this=*this+t;
 }
 
 void operator += (const long &t){
   *this=*this+t;
 }
 
 bignum operator - (const bignum &t) const{
   bignum c;
   c=*this;
   for(long i=0;i<c.l;++i){
     if(c.a[i]>=t.a[i])
      c.a[i]=c.a[i]-t.a[i];
     else{
      c.a[i]=c.a[i]+mod-t.a[i];
      c.a[i+1]--;
     }
   }
   c.carry();
   return c;
 }
 
 bignum operator - (const long &t) const{
   bignum tmp=t;
   return *this-tmp;
 }
 
 void operator -=(const bignum &t) {
   *this=*this-t;
 }
 void operator -=(const long &t) {
   *this=*this-t;
 }
 bignum operator * (const bignum &t) const{
   bignum c;
   c.l=l+t.l;
   for(long i=0;i<l;++i)
    for(long j=0;j<t.l;++j){
     c.a[i+j]+=a[i]*t.a[j];
     c.a[i+j+1]+=c.a[i+j]/mod;
     c.a[i+j]%=mod;
    }
    c.carry();
    return c;
 }
 bignum operator * (const long &t) const{
   bignum c;
   c=*this;
   c.l+=1;
   for(long i=0;i<l;++i)
    c.a[i]=a[i]*t;
   c.carry();
   return c;
 }
 void operator *=(const bignum &t) {
   *this=*this*t;
 }
 void operator *=(const long &t) {
   *this=*this*t;
 }
 bignum operator / (const long &t) const{
   bignum c;
   c.l=l;
   long ret=0;
   for(long i=l-1;i>=0;--i){
     ret=ret*mod+a[i];
     c.a[i]=ret/t;
     ret%=t;
   }
   c.carry();
   return c;
 }
 void operator /=(const long &t) {
   *this=*this/t;
 }
 bignum operator ^ (const long &t) const{    
   long p=t;
   bignum tmp=*this,ans=1;
   while(p){
     if(p%2) ans*=tmp;
     tmp*=tmp;
     p/=2;
   }
   return ans;
 }
}; 

bignum C(long n,long m){
  bignum ans; ans=1;
  for(long i=n;i>=n-m+1;--i) ans*=i;
  for(long i=1;i<=m;++i) ans/=i;
  return ans;
}

bignum f[55];
long n;

int main(){
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  bignum tmp; tmp=2;
  for(long n=1;n<=50;++n){
   f[n]=0;
   for(long i=1;i<n;++i){
    f[n]+=(C(n-1,i-1)*f[i]*(tmp^((n-i)*(n-i-1)/2)));
   }
   f[n]=(tmp^(n*(n-1)/2))-f[n];
  }
  long t;
  while(scanf("%ld",&t)&&t!=0){
    f[t].print();
    printf("\n");
  }
  return 0;
}
