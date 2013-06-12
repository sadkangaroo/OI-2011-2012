#include<iostream>

using namespace std;

const int Num_Length=1000;

char s[Num_Length];

struct bignum{
  
  int a[Num_Length],l;
  
  bignum() { memset(a,0,sizeof(a)); }
  
  void operator = (int t){
    memset(a,0,sizeof(a)); l=0;
    for(;t;t/=10) a[l++]=t%10;
    if(!l) l=1;
  }
  
  void read(){
    int t=0; char ch; memset(a,0,sizeof(a)); l=0;
    while((ch=getchar())&&ch!=' '&&ch!='\n'&&ch!=-1) s[t++]=ch;
    for(int i=t-1;i>=0;--i,++l) a[l]=s[i]-'0';
  }
  
  void print() { for(int i=l-1;i>=0;--i) printf("%d",a[i]); }
  
  void carry(){
    for(int i=1;i<=l;++i)
      if(a[i-1]>=10){
        a[i]+=(a[i-1]/10);
        a[i-1]%=10;
      }
    while(l>1&&!a[l-1]) l--;
  }
  
  bignum operator + (const bignum &t)const{
    bignum c;c.l=max(l,t.l)+1;
    for(int i=0;i<c.l;++i)
      c.a[i]=a[i]+t.a[i];
    c.carry();
    return c;
  }
  
  bignum operator - (const bignum &t)const{
    bignum c=*this;
    for(int i=0;i<c.l;++i)
      if(c.a[i]>=t.a[i]) c.a[i]-=t.a[i];
        else { c.a[i]+=(10-t.a[i]); c.a[i+1]--; }
    c.carry();
    return c;
  }
  
  bignum operator * (const bignum &t)const{
    bignum c;c.l=l+t.l;
    for(int i=0;i<l;++i)
      for(int j=0;j<t.l;++j)
        c.a[i+j]+=a[i]*t.a[j];
    c.carry();
    return c;    
  }
  
  bignum operator / (const int &t)const{
    bignum c;c.l=l;
    int ret=0;
    for(int i=l-1;i>=0;--i){
      ret=ret*10+a[i];
      c.a[i]=ret/t;
      ret%=t;
    }
    c.carry();
    return c;
  }
  
  int operator % (const int &t)const{    
    int ret=0;
    for(int i=l-1;i>=0;--i){
      ret=ret*10+a[i];
      ret%=t;
    }
    return ret;
  }
  
  bignum p(int t){
    bignum ans;ans=1;bignum tmp=*this;
    while(t){
      if(t%2) ans=ans*tmp;
      tmp=tmp*tmp;
      t/=2;
    }
    return ans;
  }
  
};

int main(){
  return 0;  
}
