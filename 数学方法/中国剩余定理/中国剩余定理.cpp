/*
***中国剩余定理：
设m1~mk是两两互素正整数，对于任意整数a1~ak,一次同余方程组 x=ai(mod mi)必有解
且解可写为x=x0(mod m) 其中x0为一特解，m为所有mi的乘积
***拓展的中国剩余定理，求解线性同余方程组
对于线形同于方程组 x=ai(mod mi) （i属于1~k）（ai为整数，mi为正整数）的求解
可一次合并，c=a1(mod m1)与c=a2(mod m2)若有解，设x0为一特解，则所有解可表示为
c=x0(mod lcm(m1,m2))(*),因此可以用（*）式替换前前两个式子 ，重复做k-1次则可得解
对于求解特解x0：  可设x0=x*m1+a1=y*m2+a2  即 x*m1-y*m2=a2-a2,
注意到最后的m1即为初始时的lcm（m1,m2,...mk) 
可利用拓展欧几里得解不定方程 ，判断有无解，有解可求出一组特解，对应到特解x0； 
一般把特解转化为绝对值较小的数防止增长过快。 
*/

#include<iostream>
#include<string>
#include<math.h>
using namespace std;

bool flag;
long long n,m1,m2,r1,r2,c,d,x,y;

long long extend_gcd(long long a,long long b){
  if(b==0){x=1;y=0;return a;}
  long long r=extend_gcd(b,a%b);
  long long t=x;x=y;y=t-a/b*y;
  return r; 
} 

int main(){

  while(scanf("%I64d",&n)!=EOF){
    flag=true;
    scanf("%I64d%I64d",&m1,&r1);
    for(long long i=1;i<n;++i){
      scanf("%I64d%I64d",&m2,&r2);
       if(flag==false) continue;
      d=extend_gcd(m1,m2);
      c=r2-r1;
      if(c%d!=0){
        flag=false;
        continue;
      }
      long long t=m2/d;
      x=(c/d*x%t+t)%t;
      r1=m1*x+r1;
      m1=m1*m2/d;
    }
    if(flag) printf("%I64d\n",r1);
     else printf("-1\n");
  }

  return 0;

}
