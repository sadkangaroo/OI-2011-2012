/*
��Ŀ���⣺��ͬ�෽��x^2=a(mod 4000000007)
�㷨˼·������4000000007����������Ϊ4k+3�͵ģ�
����x��������Ϊx=+/- a^[(4000000007+1)/4](mod 4000000007)
*/
#include<iostream>
#include<string>
#include<cmath>
#include<ctime>
using namespace std;

const unsigned long long Mod=4000000007uLL;

unsigned long long get_power(unsigned long long x,unsigned long long y){
  unsigned long long ret=1LL;
  while(y){
    if(y&1) ret=ret*x%Mod;
    x=x*x%Mod;
    y>>=1;
  }
  return ret;
}

unsigned long long a,x;

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  
  scanf("%ulld",&a);
  tm *ptm;    
  x=get_power(a,(Mod+1)/4);  
  time_t rawtime=x;
  ptm=gmtime(&rawtime);
  if(x<=0x7fffffff&&ptm->tm_year>=70&&ptm->tm_year<=130)
    puts(asctime(ptm));
  else{    
    long long tx=-x;
    while(tx<0) tx+=Mod;
    x=(unsigned long long)tx;    
    rawtime=x;    
    ptm=gmtime(&rawtime);
    printf("%s",asctime(ptm));  
  }  
  return 0;
}
